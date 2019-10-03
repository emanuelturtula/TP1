# Sistemas Embebidos
Repositorio para el seminario de sistemas embebidos 86.65

- Ruiz Santiago
- Ciafardini Juan
- Molina Segundo
- Turtula Emanuel

# Documentación del TP1
**Objetivo**
- **Uso del IDE** edición, compilación y depuración de programas.
- **Uso de GPIO** manejo de Salidas y Entradas Digitales.
- **Documentar lo que se solicita en c/ítems** 

# 1 DESCARGA DEL IDE
Se descargó MCUXpresso v11.0.0 para Windows y se instalaron los complementos de OpenOCD, eGit y Yakindu StateChart Tools según la [hoja de ayuda](https://campus.fi.uba.ar/pluginfile.php/307047/mod_resource/content/5/Sistemas_Embebidos-2019_2doC-Instalacion_de_Herramientas-Cruz.pdf) de la materia.

## 1.1 Firmware
Utilizando git se descargó el repositorio *firmware_v2* y se copió el archivo *project.mk.template* a *project.mk* utilizando los siguientes comandos:
```sh
$ git clone https://github.com/ciaa/firmware_v2.git
$ cd firmware_v2
$ git status -s
$ git checkout master
$ cp project.mk.template project.mk
```
Luego se abrió el IDE, creando un workspace con el nombre Workspace_TPs_SE_2019 y se agregó el firmware_v2. Luego en File--New--Other--C/C++--Makefile Project with Existing Code...

- En **Existing Code Location Browse** se colocó la ubicación de la carpeta *firmware_v2*.
- Se destildó el casillero **C++**.
- Se seleccionó la opción **Cross GCC ó ARM Cross GCC**.

El archivo project.mk se configuró de la siguiente forma:

- PROJECT = sapi_examples/edu-ciaa-nxp/bare_metal/gpio/gpio_02_blinky
- TARGET = lpc4337_m4
- BOARD = edu_ciaa_nxp

## 1.2 Debug
Se hizo click derecho sobre la carpeta *firmware_v2* y en el menú se seleccionó la opción **Build**. Luego, para realizar el **Debug** se hizo click derecho sobre la carpeta *firmware_v2* y en el menú se seleccionó *Debug As--Debug Configurations...*.
