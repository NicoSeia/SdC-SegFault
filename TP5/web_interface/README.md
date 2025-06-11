# Signal Viewer Web Interface

Una interfaz web simple para visualizar las señales del módulo de kernel `sensor_drv`.

## Estructura del proyecto

```
web_interface/
├── app.py              # Aplicación Flask
├── requirements.txt    # Dependencias
└── templates/
    └── index.html     # Interfaz web
```

## Requisitos

- Python 3.6+
- Flask
- Acceso al dispositivo `/dev/sensor_drv`

## Instalación

1. Instalar las dependencias:
```bash
pip install -r requirements.txt
```

2. Asegurarse de que el módulo del kernel esté cargado y el dispositivo tenga los permisos correctos:
```bash
# Como root
sudo chmod 666 /dev/sensor_drv
```

## Uso

1. Iniciar la aplicación:
```bash
python3 app.py
```

2. Abrir un navegador web y visitar:
```
http://localhost:5000
```

3. Usar los botones para alternar entre señal senoidal y cuadrada.

## Características

- Visualización en tiempo real de las señales
- Gráfico con auto-escalado
- Ventana móvil de 30 segundos
- Cambio dinámico entre señales
- Interfaz limpia y responsiva 