// sensor_drv.c — versión sin punto flotante y compatible con kernels ≥ 6.6
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/timer.h>
#include <linux/jiffies.h>

#define DEVICE_NAME "sensor_drv"
#define CLASS_NAME  "sensor"

static dev_t dev_number;
static struct class *sensor_class;
static struct device *sensor_device;
static struct cdev sensor_cdev;

static int selected_signal;   /* 0 = senoidal, 1 = cuadrada */
static int current_value;
static struct timer_list signal_timer;

/* Tabla sencilla (12 muestras) de una senoidal normalizada −100 … 100 */
static const int8_t sine_table[12] =
        {   0,  50,  87, 100,  87,  50,
            0, -50, -87,-100, -87, -50 };

static int generate_sine_wave(void)
{
    static int idx;                     /* avanza 1 muestra/segundo */
    int v = sine_table[idx];
    idx = (idx + 1) % ARRAY_SIZE(sine_table);
    return v;
}

static int generate_square_wave(void)
{
    static bool high;
    high = !high;                      /* alterna cada segundo */
    return high ? 100 : -100;
}

static void timer_callback(struct timer_list *t)
{
    current_value = (selected_signal == 0) ?
                    generate_sine_wave() : generate_square_wave();
    mod_timer(&signal_timer, jiffies + HZ); /* re‑programar a 1 s */
}

/* ----- file_operations ----- */
static ssize_t sensor_read(struct file *file, char __user *buf,
                           size_t len, loff_t *offset)
{
    char kbuf[16];
    int n;

    if (*offset != 0)
        return 0;                      /* EOF para lecturas repetidas */

    n = scnprintf(kbuf, sizeof(kbuf), "%d\n", current_value);

    if (copy_to_user(buf, kbuf, n))
        return -EFAULT;

    *offset = n;
    return n;
}

static ssize_t sensor_write(struct file *file, const char __user *buf,
                            size_t len, loff_t *offset)
{
    char ch;
    if (copy_from_user(&ch, buf, 1))
        return -EFAULT;

    switch (ch) {
    case '0': selected_signal = 0; break;
    case '1': selected_signal = 1; break;
    default:  return -EINVAL;          /* carácter inválido */
    }
    return len;
}

static int sensor_open(struct inode *inode, struct file *file)  { return 0; }
static int sensor_release(struct inode *inode, struct file *f) { return 0; }

static const struct file_operations sensor_fops = {
    .owner   = THIS_MODULE,
    .open    = sensor_open,
    .read    = sensor_read,
    .write   = sensor_write,
    .release = sensor_release,
};

/* ----- init / exit ----- */
static int __init sensor_init(void)
{
    int ret;

    ret = alloc_chrdev_region(&dev_number, 0, 1, DEVICE_NAME);
    if (ret) return ret;

    cdev_init(&sensor_cdev, &sensor_fops);
    ret = cdev_add(&sensor_cdev, dev_number, 1);
    if (ret) goto err_unregister;

    sensor_class = class_create(CLASS_NAME); /* API nueva: solo nombre */
    if (IS_ERR(sensor_class)) {
        ret = PTR_ERR(sensor_class);
        goto err_cdev;
    }

    sensor_device = device_create(sensor_class, NULL, dev_number,
                                  NULL, DEVICE_NAME);
    if (IS_ERR(sensor_device)) {
        ret = PTR_ERR(sensor_device);
        goto err_class;
    }

    timer_setup(&signal_timer, timer_callback, 0);
    mod_timer(&signal_timer, jiffies + HZ);

    pr_info("[sensor_drv] cargado: major=%d minor=0\n", MAJOR(dev_number));
    return 0;

err_class:
    class_destroy(sensor_class);
err_cdev:
    cdev_del(&sensor_cdev);
err_unregister:
    unregister_chrdev_region(dev_number, 1);
    return ret;
}

static void __exit sensor_exit(void)
{
    del_timer_sync(&signal_timer);
    device_destroy(sensor_class, dev_number);
    class_destroy(sensor_class);
    cdev_del(&sensor_cdev);
    unregister_chrdev_region(dev_number, 1);
    pr_info("[sensor_drv] descargado\n");
}

module_init(sensor_init);
module_exit(sensor_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SegFault");
MODULE_DESCRIPTION("Simulated two‑signal character driver (no FP)");
