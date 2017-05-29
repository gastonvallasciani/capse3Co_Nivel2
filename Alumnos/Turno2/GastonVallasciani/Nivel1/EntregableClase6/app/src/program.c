/* Author: Gaston Vallasciani
 * ============================================================================
 * Date: 2017-03-27
 * ============================================================================
 */

/*==================[inclusions]=============================================*/

#include "program.h"   // <= Own header
#include "sapi.h"      // <= sAPI library

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

 uint8_t dato_recibido,flag_LEDB,flag_LEDG,flag_LEDR,flag_LED1,flag_LED2,flag_LED3,flag_TEC1,flag_TEC2,flag_TEC3,flag_TEC4;

/*==================[external data definition]===============================*/

/*==================[main function]==========================================*/

// MAIN FUNCTION, ENTRY PINT TO THE PROGRAM AFTER POR OR RESET.
int main( void ){

   // ---------- SETUP ----------------------------------------
   // Initialize an configurate the board
   boardConfig();
   uartConfig( UART_USB , 9600 );   
   
   flag_LEDB=0; flag_LEDG=0;flag_LEDR=0; flag_LED1=0;flag_LED2=0; flag_LED3=0,flag_TEC1=0,flag_TEC2=0,flag_TEC3=0,flag_TEC4=0;
   
   uartWriteString( UART_USB ,"LEDB = OFF, ");
   uartWriteString( UART_USB ,"LEDG = OFF, ");
   uartWriteString( UART_USB ,"LEDR = OFF, ");
   uartWriteString( UART_USB ,"LED1 = OFF, ");
   uartWriteString( UART_USB ,"LED2 = OFF, ");
   uartWriteString( UART_USB ,"LED3 = OFF, ");
   
   uartWriteString( UART_USB ,"TECLA1 = ON, ");
   uartWriteString( UART_USB ,"TECLA2 = ON, ");
   uartWriteString( UART_USB ,"TECLA3 = ON, ");
   uartWriteString( UART_USB ,"TECLA4 = ON \r\n");
     

   // ---------- REPEAT FOR EVER ------------------------------
   while( 1 )
   {
      if ( uartReadByte( UART_USB , &dato_recibido) )
      {
      	switch ( dato_recibido )
      	{
      	     case 'a': 
      	      {
      	     	if (flag_LEDB == 1)
      	     	 {
      	     	   flag_LEDB = 0;
      	     	   gpioWrite( LEDB, 0 );
      	     	 }
      	     	 else
      	     	  {
      	     	    flag_LEDB = 1;
      	     	    gpioWrite( LEDB, 1 );
      	     	  }
      	     	break;
      	      }	
      	     case 'v': 
      	      {
      	     	if (flag_LEDG == 1)
      	     	 {
      	     	   flag_LEDG = 0;
      	     	   gpioWrite( LEDG, 0 );
      	     	 }
      	     	 else
      	     	  {
      	     	    flag_LEDG = 1;
      	     	    gpioWrite( LEDG, 1 );
      	     	  }
      	     	break;
      	      }	
      	      
      	     case 'r': 
      	      {
      	     	if (flag_LEDR == 1)
      	     	 {
      	     	   flag_LEDR = 0;
      	     	   gpioWrite( LEDR, 0 );
      	     	 }
      	     	 else
      	     	  {
      	     	    flag_LEDR = 1;
      	     	    gpioWrite( LEDR, 1 );
      	     	  }
      	     	break;
      	      }	
      	     case '1': 
      	      {
      	     	if (flag_LED1 == 1)
      	     	 {
      	     	   flag_LED1 = 0;
      	     	   gpioWrite( LED1, 0 );
      	     	 }
      	     	 else
      	     	  {
      	     	    flag_LED1 = 1;
      	     	    gpioWrite( LED1, 1 );
      	     	  }
      	     	break;
      	      }	
      	     case '2': 
      	      {
      	     	if (flag_LED2 == 1)
      	     	 {
      	     	   flag_LED2 = 0;
      	     	   gpioWrite( LED2, 0 );
      	     	 }
      	     	 else
      	     	  {
      	     	    flag_LED2 = 1;
      	     	    gpioWrite( LED2, 1 );
      	     	  }
      	     	break;
      	      }	
      	     case '3': 
      	      {
      	     	if (flag_LED3 == 1)
      	     	 {
      	     	   flag_LED3 = 0;
      	     	   gpioWrite( LED3, 0 );
      	     	 }
      	     	 else
      	     	  {
      	     	    flag_LED3 = 1;
      	     	    gpioWrite( LED3, 1 );
      	     	  }
      	     	break;
      	      }		
      	}
      }
      
     flag_TEC1 = gpioRead( TEC1 );
     flag_TEC2 = gpioRead( TEC2 );
     flag_TEC3 = gpioRead( TEC3 );
     flag_TEC4 = gpioRead( TEC4 );
      
     delay(1000);
      
     if (flag_LEDB == 1)
      {uartWriteString( UART_USB ,"LEDB = ON, ");}
      else
       {uartWriteString( UART_USB ,"LEDB = OFF, ");}	
        
     if (flag_LEDG == 1)
      {uartWriteString( UART_USB ,"LEDG = ON, ");}
      else
       {uartWriteString( UART_USB ,"LEDG = OFF, ");}	
      
     if (flag_LEDR == 1)
      {uartWriteString( UART_USB ,"LEDR = ON, ");}
      else
       {uartWriteString( UART_USB ,"LEDR = OFF, ");}	
        
     if (flag_LED1 == 1)
      {uartWriteString( UART_USB ,"LED1 = ON, ");}
      else
       {uartWriteString( UART_USB ,"LED1 = OFF, ");}
        
     if (flag_LED2 == 1)
      {uartWriteString( UART_USB ,"LED2 = ON, ");}
      else
       {uartWriteString( UART_USB ,"LED2 = OFF, ");}
      
     if (flag_LED3 == 1)
      {uartWriteString( UART_USB ,"LED3 = ON, ");}
      else
       {uartWriteString( UART_USB ,"LED3 = OFF, ");}	
       
     if (flag_TEC1 == 1)
      {uartWriteString( UART_USB ,"TEC1 = ON, ");}
      else
       {uartWriteString( UART_USB ,"TEC1 = OFF, ");}	
       
     if (flag_TEC2 == 1)
      {uartWriteString( UART_USB ,"TEC2 = ON, ");}
      else
       {uartWriteString( UART_USB ,"TEC2 = OFF, ");}	
       
    if (flag_TEC3 == 1)
      {uartWriteString( UART_USB ,"TEC3 = ON, ");}
      else
       {uartWriteString( UART_USB ,"TEC3 = OFF, ");}		
       
    if (flag_TEC4 == 1)
      {uartWriteString( UART_USB ,"TEC4 = ON\r\n");}
      else
       {uartWriteString( UART_USB ,"TEC4 = OFF\r\n");}	
   } 

}

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

/*==================[end of file]============================================*/
