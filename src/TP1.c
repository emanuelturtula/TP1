/* Copyright 2016, Eric Pernia.
 * All rights reserved.
 *
 * This file is part sAPI library for microcontrollers.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include "TP1.h"


#ifdef TP1_1
/*
 * Date: 2016-04-26
 */

/*==================[inclusions]=============================================*/

//#include "blinky.h"   // <= own header (optional)
#include "sapi.h"       // <= sAPI header

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/


/* FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE RESET. */
int main(void){

   /* ------------- INICIALIZACIONES ------------- */

   /* Inicializar la placa */
   boardConfig();

   /* ------------- REPETIR POR SIEMPRE ------------- */
   while(1) {

      /* Prendo el led azul */
      gpioWrite( LED3, ON );

      delay(500);

      /* Apago el led azul */
      gpioWrite( LED3, OFF );

      delay(500);

   }

   /* NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa no es llamado
      por ningun S.O. */
   return 0 ;
}


/*==================[end of file]============================================*/
#endif

#ifdef TP1_2
/*
 * Date: 2016-04-26
 */

/*==================[inclusions]=============================================*/

//#include "switches_leds.h"   // <= own header (optional)
#include "sapi.h"              // <= sAPI header

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

/* FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE RESET. */
int main(void)
{

   /* ------------- INICIALIZACIONES ------------- */

   /* Inicializar la placa */
   boardConfig();

   gpioConfig( GPIO0, GPIO_INPUT );

   gpioConfig( GPIO1, GPIO_OUTPUT );

   /* Variable para almacenar el valor de tecla leido */
   bool_t valor;

   /* ------------- REPETIR POR SIEMPRE ------------- */
   while(1) {

      valor = !gpioRead( TEC1 );
      gpioWrite( LEDB, valor );

      valor = !gpioRead( TEC2 );
      gpioWrite( LED1, valor );

      valor = !gpioRead( TEC3 );
      gpioWrite( LED2, valor );

      valor = !gpioRead( TEC4 );
      gpioWrite( LED3, valor );

      valor = !gpioRead( GPIO0 );
      gpioWrite( GPIO1, valor );

   }

   /* NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa no es llamado
      por ningun S.O. */
   return 0 ;
}

/*==================[end of file]============================================*/

#endif

#ifdef TP1_3
/*
 * Date: 2016-04-26
 */

/*==================[inclusions]=============================================*/

//#include "tickHook.h"   // <= own header (optional)
#include "sapi.h"         // <= sAPI header
#define TICKRATE_MS 100		// TICKRATE EN ms
#define LED_TOGGLE_MS 500	// LED TOGGLE EN ms

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

/* FUNCION que se ejecuta cada vez que ocurre un Tick. */
void myTickHook( void *ptr ){

   static bool_t ledState = OFF;

   gpioMap_t led = (gpioMap_t)ptr;

   if( ledState ){
      ledState = OFF;
   }
   else{
      ledState = ON;
   }
   gpioWrite( led, ledState );
}


/* FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE RESET. */
int main(void){

   /* ------------- INICIALIZACIONES ------------- */

   /* Inicializar la placa */
   boardConfig();

   /* Inicializar el conteo de Ticks con resolucion de 50ms (se ejecuta
      periodicamente una interrupcion cada 50ms que incrementa un contador de
      Ticks obteniendose una base de tiempos). */
   tickConfig( TICKRATE_MS );

   /* Se agrega ademas un "tick hook" nombrado myTickHook. El tick hook es
      simplemente una funcion que se ejecutara peri�odicamente con cada
      interrupcion de Tick, este nombre se refiere a una funcion "enganchada"
      a una interrupcion.
      El segundo parametro es el parametro que recibe la funcion myTickHook
      al ejecutarse. En este ejemplo se utiliza para pasarle el led a titilar.
   */
   tickCallbackSet( myTickHook, (void*)LEDR );
   delay(LED_TOGGLE_MS);

   /* ------------- REPETIR POR SIEMPRE ------------- */
   while(1) {
      tickCallbackSet( myTickHook, (void*)LEDG );
      delay(LED_TOGGLE_MS);
      tickCallbackSet( myTickHook, (void*)LEDB );
      delay(LED_TOGGLE_MS);
      tickCallbackSet( myTickHook, (void*)LED1 );
      delay(LED_TOGGLE_MS);
      tickCallbackSet( myTickHook, (void*)LED2 );
      delay(LED_TOGGLE_MS);
      tickCallbackSet( myTickHook, (void*)LED3 );
      delay(LED_TOGGLE_MS);
      tickCallbackSet( myTickHook, (void*)LEDR );
      delay(LED_TOGGLE_MS);
   }

   /* NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa no es llamado
      por ningun S.O. */
   return 0 ;
}

/*==================[end of file]============================================*/

#endif


#ifdef TP1_4
//#include "led_sequences.h"   // <= own header (optional)
#include "sapi.h"              // <= sAPI header
/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

/* FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE RESET. */
int main(void){

   /* ------------- INICIALIZACIONES ------------- */

   /* Inicializar la placa */
   boardConfig();

   /* Variable de Retardo no bloqueante */
   delay_t delay;

   /* Inicializar Retardo no bloqueante con tiempo en milisegundos
      (500ms = 0,5s) */
   delayConfig( &delay, 500 );

   int8_t i = 3;
   uint8_t sequence = 0;

   /* ------------- REPETIR POR SIEMPRE ------------- */
   while(1) {

      if ( !gpioRead( TEC1 ) ){
         sequence = 0;
      }
      if ( !gpioRead( TEC2 ) ){
         /* Velocidad Rapida */
         delayWrite( &delay, 150 );
      }
      if ( !gpioRead( TEC3 ) ){
         /* Velocidad Lenta */
         delayWrite( &delay, 750 );
      }
      if ( !gpioRead( TEC4 ) ){
         sequence = 1;
      }

      /* delayRead retorna TRUE cuando se cumple el tiempo de retardo */
      if ( delayRead( &delay ) ){
         if ( !sequence ){
            i--;
         }
         else{
            i++;
         }
      }

      if ( i == 0 ){
         gpioWrite( LEDB, ON );
         gpioWrite( LED1, OFF );
         gpioWrite( LED2, OFF );
         gpioWrite( LED3, OFF );
		 gpioWrite( LEDR, OFF );
		 gpioWrite( LEDG, OFF );
      }
      if ( i == 1 ){
         gpioWrite( LEDB, OFF );
         gpioWrite( LED1, ON );
         gpioWrite( LED2, OFF );
         gpioWrite( LED3, OFF );
		 gpioWrite( LEDR, OFF );
		 gpioWrite( LEDG, OFF );
      }
      if ( i == 2 ){
         gpioWrite( LEDB, OFF );
         gpioWrite( LED1, OFF );
         gpioWrite( LED2, ON );
         gpioWrite( LED3, OFF );
		 gpioWrite( LEDR, OFF );
		 gpioWrite( LEDG, OFF );
      }
      if ( i == 3 ){
         gpioWrite( LEDB, OFF );
         gpioWrite( LED1, OFF );
         gpioWrite( LED2, OFF );
         gpioWrite( LED3, ON );
		 gpioWrite( LEDR, OFF );
		 gpioWrite( LEDG, OFF );
      }
      if ( i == 4 ){
		 gpioWrite( LEDB, OFF );
		 gpioWrite( LED1, OFF );
		 gpioWrite( LED2, OFF );
		 gpioWrite( LED3, OFF );
		 gpioWrite( LEDR, ON );
		 gpioWrite( LEDG, OFF );
      }
      if ( i == 5 ){
		 gpioWrite( LEDB, OFF );
		 gpioWrite( LED1, OFF );
		 gpioWrite( LED2, OFF );
		 gpioWrite( LED3, OFF );
		 gpioWrite( LEDR, OFF );
		 gpioWrite( LEDG, ON  );
      }

      if ( i < 0 ){
         i = 5;
      }
      if ( i > 5 ){
         i = 0;
      }

   }

   /* NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa no es llamado
      por ningun S.O. */
   return 0 ;
}

#endif

#ifdef TP1_5
//#include "led_sequences.h"   // <= own header (optional)
#include "sapi.h"              // <= sAPI header
/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

/* FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE RESET. */
int main(void){

   /* ------------- INICIALIZACIONES ------------- */

   /* Inicializar la placa */
   boardConfig();

   /* Variable de Retardo no bloqueante */
   delay_t delay;

   /* Inicializar Retardo no bloqueante con tiempo en milisegundos
      (500ms = 0,5s) */
   delayConfig( &delay, 500 );

   int8_t i = 3;
   uint8_t sequence = 0;

   /* HABILITO UART */
   DEBUG_PRINT_ENABLE;

   debugPrintConfigUart( UART_USB, 115200 );
   debugPrintString( "DEBUG c/SAPI\n" );


   /* ------------- REPETIR POR SIEMPRE ------------- */
   while(1) {
      if ( !gpioRead( TEC1 ) ){
         sequence = 0;
      }
      if ( !gpioRead( TEC2 ) ){
         /* Velocidad Rapida */
         delayWrite( &delay, 150 );
      }
      if ( !gpioRead( TEC3 ) ){
         /* Velocidad Lenta */
         delayWrite( &delay, 750 );
      }
      if ( !gpioRead( TEC4 ) ){
         sequence = 1;
      }

      /* delayRead retorna TRUE cuando se cumple el tiempo de retardo */
      if ( delayRead( &delay ) ){
         if ( !sequence ){
            i--;
         }
         else{
            i++;
         }
         debugPrintString( "LED TOGGLE\r\n" );
      }

      if ( i == 0 ){
         gpioWrite( LEDB, ON );
         gpioWrite( LED1, OFF );
         gpioWrite( LED2, OFF );
         gpioWrite( LED3, OFF );
		 gpioWrite( LEDR, OFF );
		 gpioWrite( LEDG, OFF );
      }
      if ( i == 1 ){
         gpioWrite( LEDB, OFF );
         gpioWrite( LED1, ON );
         gpioWrite( LED2, OFF );
         gpioWrite( LED3, OFF );
		 gpioWrite( LEDR, OFF );
		 gpioWrite( LEDG, OFF );
      }
      if ( i == 2 ){
         gpioWrite( LEDB, OFF );
         gpioWrite( LED1, OFF );
         gpioWrite( LED2, ON );
         gpioWrite( LED3, OFF );
		 gpioWrite( LEDR, OFF );
		 gpioWrite( LEDG, OFF );
      }
      if ( i == 3 ){
         gpioWrite( LEDB, OFF );
         gpioWrite( LED1, OFF );
         gpioWrite( LED2, OFF );
         gpioWrite( LED3, ON );
		 gpioWrite( LEDR, OFF );
		 gpioWrite( LEDG, OFF );
      }
      if ( i == 4 ){
		 gpioWrite( LEDB, OFF );
		 gpioWrite( LED1, OFF );
		 gpioWrite( LED2, OFF );
		 gpioWrite( LED3, OFF );
		 gpioWrite( LEDR, ON );
		 gpioWrite( LEDG, OFF );

      }
      if ( i == 5 ){
		 gpioWrite( LEDB, OFF );
		 gpioWrite( LED1, OFF );
		 gpioWrite( LED2, OFF );
		 gpioWrite( LED3, OFF );
		 gpioWrite( LEDR, OFF );
		 gpioWrite( LEDG, ON  );
      }

      if ( i < 0 ){
         i = 5;
      }
      if ( i > 5 ){
         i = 0;
      }

   }

   /* NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa no es llamado
      por ningun S.O. */
   return 0 ;
}

#endif

#ifdef TP1_6
//#include "led_sequences.h"   // <= own header (optional)
#include "sapi.h"              // <= sAPI header
/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

/* FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE RESET. */
int main(void){

   /* ------------- INICIALIZACIONES ------------- */

   /* Inicializar la placa */
   boardConfig();

   /* Variable de Retardo no bloqueante */
   delay_t delay;

   /* Inicializar Retardo no bloqueante con tiempo en milisegundos
      (500ms = 0,5s) */
   delayConfig( &delay, 500 );

   int8_t i = 3;
   uint8_t sequence = 0;

   /* HABILITO UART */
   DEBUG_PRINT_ENABLE;

   debugPrintConfigUart( UART_USB, 115200 );
   debugPrintString( "DEBUG c/SAPI\n" );


   /* ------------- REPETIR POR SIEMPRE ------------- */
   while(1) {
      if ( !gpioRead( TEC1 ) ){
         sequence = 0;
         debugPrintString( "LED SEQUENCE TO LEFT\r\n" );
      }
      if ( !gpioRead( TEC2 ) ){
         /* Velocidad Rapida */
         delayWrite( &delay, 150 );
         debugPrintString( "LED FAST SPEED\r\n" );
      }
      if ( !gpioRead( TEC3 ) ){
         /* Velocidad Lenta */
         delayWrite( &delay, 750 );
         debugPrintString( "LED SLOW SPEED\r\n" );
      }
      if ( !gpioRead( TEC4 ) ){
         sequence = 1;
         debugPrintString( "LED SEQUENCE TO RIGHT\r\n" );
      }

      /* delayRead retorna TRUE cuando se cumple el tiempo de retardo */
      if ( delayRead( &delay ) ){
         if ( !sequence ){
            i--;
         }
         else{
            i++;
         }
         //debugPrintString( "LED TOGGLE\r\n" );
      }

      if ( i == 0 ){
         gpioWrite( LEDB, ON );
         gpioWrite( LED1, OFF );
         gpioWrite( LED2, OFF );
         gpioWrite( LED3, OFF );
		 gpioWrite( LEDR, OFF );
		 gpioWrite( LEDG, OFF );
      }
      if ( i == 1 ){
         gpioWrite( LEDB, OFF );
         gpioWrite( LED1, ON );
         gpioWrite( LED2, OFF );
         gpioWrite( LED3, OFF );
		 gpioWrite( LEDR, OFF );
		 gpioWrite( LEDG, OFF );
      }
      if ( i == 2 ){
         gpioWrite( LEDB, OFF );
         gpioWrite( LED1, OFF );
         gpioWrite( LED2, ON );
         gpioWrite( LED3, OFF );
		 gpioWrite( LEDR, OFF );
		 gpioWrite( LEDG, OFF );
      }
      if ( i == 3 ){
         gpioWrite( LEDB, OFF );
         gpioWrite( LED1, OFF );
         gpioWrite( LED2, OFF );
         gpioWrite( LED3, ON );
		 gpioWrite( LEDR, OFF );
		 gpioWrite( LEDG, OFF );
      }
      if ( i == 4 ){
		 gpioWrite( LEDB, OFF );
		 gpioWrite( LED1, OFF );
		 gpioWrite( LED2, OFF );
		 gpioWrite( LED3, OFF );
		 gpioWrite( LEDR, ON );
		 gpioWrite( LEDG, OFF );

      }
      if ( i == 5 ){
		 gpioWrite( LEDB, OFF );
		 gpioWrite( LED1, OFF );
		 gpioWrite( LED2, OFF );
		 gpioWrite( LED3, OFF );
		 gpioWrite( LEDR, OFF );
		 gpioWrite( LEDG, ON  );
      }

      if ( i < 0 ){
         i = 5;
      }
      if ( i > 5 ){
         i = 0;
      }

   }

   /* NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa no es llamado
      por ningun S.O. */
   return 0 ;
}

#endif
