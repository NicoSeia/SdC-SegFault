# Nombre del (los) objeto(s) del módulo
obj-m += sensor_drv.o

# Ruta al árbol de compilación del kernel
KDIR := /lib/modules/$(shell uname -r)/build

# Directorio actual
PWD  := $(shell pwd)

# Regla por defecto: compilar el módulo
all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

# Limpieza de archivos generados
clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
