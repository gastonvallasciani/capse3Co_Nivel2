/*============================================================================
 * Autor: Gaston Vallasciani
 * Fecha: 06/05/2017
 *===========================================================================*/

/*==================[inlcusiones]============================================*/

#include "programa.h"   // <= su propio archivo de cabecera
#include "sapi.h"       // <= Biblioteca sAPI

/*==================[definiciones de datos internos]=========================*/

uint8_t flag_LEDB,flag_LED1,flag_LED2,flag_LED3,dato_recibido,flag_TEC1,flag_TEC2,flag_TEC3,flag_TEC4;
uint16_t TiempoDeEspera=50;

/*==================[funcion principal]======================================*/

// FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE ENCENDIDO O RESET.

int main( void ){

   // ---------- CONFIGURACIONES ------------------------------
   // Inicializar y configurar la plataforma
   boardConfig();   
   uartConfig( UART_USB , 9600 ); 
   
   flag_LEDB=0; flag_LED1=0; flag_LED2=0; flag_LED3=0, flag_TEC1=0, flag_TEC2=0 ,flag_TEC3=0, flag_TEC4=0;
   gpioWrite( LEDB, 0 );
   gpioWrite( LED1, 0 );
   gpioWrite( LED2, 0 );
   gpioWrite( LED3, 0 );
   
   // ---------- REPETIR POR SIEMPRE --------------------------
   while( TRUE )
   {      
       if ( uartReadByte( UART_USB , &dato_recibido) )
      {
      	switch ( dato_recibido )
      	{
      	     case 'a': 
      	      {
                  flag_LEDB = 1;flag_LED1=0; flag_LED2=0; flag_LED3=0;
                  gpioWrite( LED1, 0 );
                  gpioWrite( LED2, 0 );
                  gpioWrite( LED3, 0 );
      	     	break;
      	      }
      	     case '1': 
      	      {
                  flag_LEDB = 0;flag_LED1=1; flag_LED2=0; flag_LED3=0;
                  gpioWrite( LEDB, 0 );
                  gpioWrite( LED2, 0 );
                  gpioWrite( LED3, 0 );
      	     	break;
      	      }	
      	     case '2': 
      	      {
                  flag_LEDB = 0;flag_LED1=0; flag_LED2=1; flag_LED3=0;
                  gpioWrite( LEDB, 0 );
                  gpioWrite( LED1, 0 );
                  gpioWrite( LED3, 0 );
      	     	break;
      	      }	
      	     case '3': 
      	      {
                  flag_LEDB = 0;flag_LED1=0; flag_LED2=0; flag_LED3=1;
                  gpioWrite( LEDB, 0 );
                  gpioWrite( LED1, 0 );
                  gpioWrite( LED2, 0 );
      	     	break;
      	      }		
      	}
      }
      
     flag_TEC1 = gpioRead( TEC1 );
     flag_TEC2 = gpioRead( TEC2 );
     flag_TEC3 = gpioRead( TEC3 );
     flag_TEC4 = gpioRead( TEC4 );
         
      if (!flag_TEC1)
      {
         TiempoDeEspera=50;
      }
      else
         if (!flag_TEC2)
         {
            TiempoDeEspera=100;
         }
         else
            if (!flag_TEC3)
            {
               TiempoDeEspera=200;
            }
            else
               if (!flag_TEC4)
               {
                  TiempoDeEspera=500;
               }
      if (flag_LEDB==1)
      {
         delay(TiempoDeEspera);
         gpioToggle(LEDB);
      }
      else
         if (flag_LED1==1)
         {
            delay(TiempoDeEspera);
            gpioToggle(LED1);
         }
         else
            if (flag_LED2==1)
            {
               delay(TiempoDeEspera);
               gpioToggle(LED2);
            }
            else
               if (flag_LED3==1)
               {
                  delay(TiempoDeEspera);
                  gpioToggle(LED3);
               }
   } 
   
      

   // NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa se ejecuta 
   // directamenteno sobre un microcontroladore y no es llamado/ por ningun
   // Sistema Operativo, como en el caso de un programa para PC.
   return 0;
}

/*==================[fin del archivo]========================================*/
