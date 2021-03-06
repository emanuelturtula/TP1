
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

# 1 IDE
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

## 1.3 Migrar blinky a TP1
Se copiaron los archivos del ejemplo blinky a la carpeta *projects/TP1* y se le cambió el nombre de los archivos .c y .h a *TP1*.       
        
![blinky1](IMAGENES/blinky1.PNG)        

![blinky2](IMAGENES/blinky2.PNG)        


Previamente a la compilación del proyecto se cambió la ruta dentros del   *project.mk*  por: *PROJECT = projects/TP1*. También se recomienda hacer un *clean* antes de compilar. 

![blinky3](IMAGENES/blinky3.PNG)        

Para hacer un debug primero se cambió, en la ventana de *debug configurations*, la opción *GBD OpenOCD Debugging*

![blinky4](IMAGENES/blinky4.PNG)        

# 1.3.a Acceso a los GPIO


Haciendo *Step Into* en las funciones *boardConfig()* y *gpioWrite()* se abren los archivos *sapi_board.c* y *sapi_gpio.c*.


En el cuerpo de la función *boardConfig()* se llama a una serie de funciones de inicalización, en particular para GPIO, se llama a la función *gpioConfig()*, la misma llama a las funciones de bajo nivel *Chip_GPIO_Init* *Chip_SCU_PinMux* y *Chip_GPIO_SetDir*, las mismas permiten respectivamente, habilitar el pin del puerto, seleccionar la función del mismo y el tipo de GPIO (entrada, salida, con o sin PULLUPS o PULLDOWNS en varias combinaciones).



En el cuerpo de la función *gpioWrite(gpioMap\_t,bool\_t)*, que se transcribe a continuación:


```c
bool_t gpioWrite(gpioMap_t pin, bool_t value){ // La función recibe el pin y el estado
    
    bool_t ret_val     = 1;   // Valor de retorno

   int8_t pinNamePort = 0;    // Inicializa todas las variables en cero
   int8_t pinNamePin  = 0;

   int8_t func        = 0;

   int8_t gpioPort    = 0;
   int8_t gpioPin     = 0;

   gpioObtainPinConfig( pin, &pinNamePort, &pinNamePin, &func, &gpioPort, &gpioPin );

   Chip_GPIO_SetPinState( LPC_GPIO_PORT, gpioPort, gpioPin, value);

   return ret_val;
}
```


Se puede ver que la misma llama a la función *gpioObtainPinConfig()*, esta función convierte el pin del tipo enumerado que la **SAPI** define para hacerlo mas user-friendly, a las designaciones que internamente usa el código de bajo nivel para acceder a los registros del pin. La conversión es realizada mediante la definición de un array de estructuras que es constante y que está indexado por el tipo enumerado de los pines, el contenido de estas estructuras es ***{ {PinNamePortN ,PinNamePinN}, PinFUNC, {GpioPortN, GpioPinN} }*** de esta forma toda la información es obtenida en forma de una estructura de la cual se extrae la información requerida, nombre del puerto, pin, función, puerto GPIO y pin GPIO, particularmente para GPIO genérico la función es **FUNC4**. Como ejemplo completo, el **LEDB** queda definido por ***{ {2 ,2}, FUNC4, {5, 2} }*** .

Luego se puede ver que se llama a la función *Chip_GPIO_SetPinState()*, la misma una función de bajo nivel proveída por el fabricante, que finalmente accede a las posiciones de memoria de lo registros a modificar. Esta última función utiliza un puntero de una matriz en memoria que corresponde a los registros, **LPC\_GPIO_PORT**,  este puntero es definido como una constante que apunta ala base de los registros, dependiente del particular microcontrolador para el cual se esté compilando, que se resuelve mediante los include que se seleccionan al definir la constante que identifica al procesador.

## 1.4 Repositorio
Se creó un repositorio en GitHub, y se sincronizó en el directorio *projects* del proyecto *firmware_v2*. 

Mas precisamente, se creo un único repositorio para todos los TPS, con subdirectorios para cada TP. 

# 2 Switches leds

## 2.1 compilacion condicional

Para realizar la compilacion condicional de los codigos fuentes de TP_1, TP_2 y TP_3 se declarararon previamente las etiquetas TEST(asignando la etiqueta correspondinte al codigo a compilar) TP_1, TP_2 y TP_3.Luego se utilizaron las directivas del preprocesador #if(TEST == TP1_1) #endif para el codigo de blinky y #if(TEST == TP1_2) #endif para el codigo de blinkyswitches_leds.
En la figura se puede ver como se sombrea la estructura que no va a ser compilada(TP_1 y TP_2).

![](Imagenes/compilacion_condicional.png)

## 2.2.a Funciones

Para identificar las funciones de librería sAPI útiles para el sensado de un pulsador, se plasmó en esta tabla sus características:

| Nombre | Descripción |
| ------ | ----------- |
| boardConfig(); | configura los pines de entrada y salida de placa |
| gpioConfig( GPIO0, GPIO_INPUT ); | configura el pin del primer parametro(GPIO0) en el modo ingresado como segundo parametro(GPIO_INPUT entrada) |
| valor = !gpioRead( TEC1 ); | lee el valor actual del pin introducido como parametro(TEC1) y retorna FALSE el estado es 1. |
| gpioWrite( LEDB, valor ); | asigna el estado valor al pin introducido en el primer parametro(LEDB) |

## 2.2.b Constantes y variables

Tmabién dentro de TP1_2 se encuentran las siguientes constantes y variables:

| Nombre | Descripción |
| ------ | ----------- |
| GPIO0 | pin correspondiente a GPIO0 |
| GPIO_INPUT | estado de entrada de un pin GPIO |
| GPIO1 | pin correspondiente a GPIO0 |
| GPIO_OUTPUT | estado de salida de un pin GPIO |
| TEC1 | primer pulsador |
| LEDB | pin correspondiente a LED azul |
| valor | variable booleana que se utiliza para el valor de estado de cada pulsador |
| TEC2 | segundo pulsador |
| LED1 | pin correspondiente a LED amarillo|
| TEC3 | tercer pulsador |
| LED2 | pin correspondiente a LED rojo |
| TEC4 | cuarto pulsador |
| LED3 | pin correspondiente a LED verde |
---
# 3 Uso de tickHooks
A continuación se analiza la función tick_01_tickHook, para eso se muestra la primera imagen que tiene la definición de myTickHook:
![stepb1](DOCUMENTACION3/b1.png) 
Esta función se ejecuta cada vez que ocurre un tick( o interrupción). Y lo unico que hace es prender o apagar el LED pasado por argumento dependiendo de como estaba anteriormente (si estaba prendido se apaga y viceversa).
Por otro lado, se observa el main del programa que presenta dos funciones importante tickConfig(50) que me setea el conteo de las interrupciones a 50 mSeg, es decir, que se genera una interrupción cada 50mSeg y por otro lado se tiene la función tickCallbackSet que esta definida en la siguiente figura:
![stepb7](DOCUMENTACION3/b7.png) 
Esta función lo que hace es setear dos variables globales que en conjunto me define la función de interrupción, en este caso lo que hace me setea la función de myTickHook (la que me prende el LED) con un argumento que es un puntero al LED que quiero prender. El primer argumento de tickCallbackSet me setea la variable global correspondiente a la función mientras el segundo parametro defino los argumentos que le paso a la función de interrupción. En este caso, se tiene que myTickHook recibe un argumento que es un punturo al LED que quiero prender o apagar por eso cuando quiero prender un LED con la interrupción uso mi función de tickCallbackSet.
![stepb2](DOCUMENTACION3/b2.png) 
Cuando se llama a tickConfig() una macro lleva a la funcion tickInit():
![stepb3](DOCUMENTACION3/b3.png) 
En SysTick_Config() se configura los tick por segundo de la interrupcion:
![stepb4](DOCUMENTACION3/b4.png)  
Finalmente la funcion NVIC_SetPriority() es la encargada de configurar los registro del microcontrolador correspoiendes a la prioridad de interrupcion:
![stepb5](DOCUMENTACION3/b5.png)  

---

# 4 Uso de tickHooks &amp; LEDs c/sAPI

## 4.b Utilidad de la constante "_TICKRATE_MS_"

Al inicio del código se configura la interrupción mediante la "_tickConfig()_" cuya funcionalidad fue descrita anteriormente. _ TICKRATE_MS_ es una macro, se la puede hacer valer 1, 10 o 100. Se le pasa esta macro a la función _tickConfig()_ como argumento. La utilidad de esto es que dentro de la función "_main()_" se ejecute un condicional dado por un "_if()_" a intervalos regulares según el valor de _ TICKRATE_MS_.

![step4a](IMAGENES/4_def.png)   


## 4.c Utilidad de la constante "_LED_TOGGLE_MS_"

LED_TOGGLE_MS es otra macro que va a determinar el período de parpadeo del LED. Si _ TICKRATE_MS_ vale 1, el led va a prenderse y apagarse cada 100 ms, 500 ms o 1000 ms, según sea que LED_TOGGLE_MS valga 100, 500 o 1000 respectivamente.

![step4b](IMAGENES/4_main.png)   

---

# 5 Uso de la UART

EL codigo es similar al punto 4, pero agrega el envio de mensajes por puerto serie. Para realizar esto se utilizó la funcion debugPrintString(), la cual llama a la funcion printString(). Esta última a su vez llama a la función uartWriteString(), la cual llama a una función que escribe byte a byte mediante UART.

![step5a](DOCUMENTACION5/b1.png)  

![step5b](DOCUMENTACION5/b2.png)

![step5c](DOCUMENTACION5/b3.png)

En la siguiente imagen se puede ver se puede ver el resultado a través de Putty.

![step5d](DOCUMENTACION5/c1.png)

![step5e](DOCUMENTACION5/c2.png)
