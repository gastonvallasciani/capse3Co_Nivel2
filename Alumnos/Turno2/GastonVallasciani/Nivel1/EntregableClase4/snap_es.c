/* Copyright (c) 2017, Eric Pernia.
 * All rights reserved.
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
 * =============================================================================
 *
 * Copyright (c) 2017, Eric Pernia.
 * Todos los derechos reservados.
 * 
 * La redistribuci?n y el uso en las formas de c?digo fuente y binario, con o 
 * sin modificaciones, est?n permitidos siempre que se cumplan las siguientes 
 * condiciones:
 * 
 * 1. Las redistribuciones del c?digo fuente deben conservar el aviso de
 *    copyright anterior, esta lista de condiciones y el siguiente descargo de
 *    responsabilidad.
 * 
 * 2. Las redistribuciones en formato binario deben reproducir el aviso de
 *    copyright anterior, esta lista de condiciones y el siguiente descargo de
 *    responsabilidad en la documentaci?n y/u otros materiales suministrados 
 *    con la distribuci?n.
 * 
 * 3. Ni el nombre de los titulares de derechos de autor ni los nombres de sus
 *    colaboradores pueden usarse para apoyar o promocionar productos 
 *    derivados de este software sin permiso espec?fico previo y por escrito.
 * 
 * ESTE SOFTWARE SE SUMINISTRA POR LOS PROPIETARIOS DEL COPYRIGHT Y
 * COLABORADORES ''COMO EST?'' Y CUALQUIER GARANT?AS EXPRESA O IMPL?CITA,
 * INCLUYENDO, PERO NO LIMITADO A, LAS GARANT?AS IMPL?CITAS DE COMERCIALIZACI?N
 * Y APTITUD PARA UN PROP?SITO PARTICULAR SON RECHAZADAS. EN NING?N CASO LOS
 * PROPIETARIOS DEL COPYRIGHT Y COLABORADORES SER?N RESPONSABLES POR NING?N
 * DA?O DIRECTO, INDIRECTO, INCIDENTAL, ESPECIAL, EJEMPLAR O COSECUENCIAL
 * (INCLUYENDO, PERO NO LIMITADO A, LA ADQUISICI?N O SUSTITUCI?N DE BIENES O
 * SERVICIOS; LA P?RDIDA DE USO, DE DATOS O DE BENEFICIOS; O INTERRUPCI?N DE LA
 * ACTIVIDAD EMPRESARIAL) O POR CUALQUIER TEOR?A DE RESPONSABILIDAD, YA SEA POR
 * CONTRATO, RESPONSABILIDAD ESTRICTA O AGRAVIO (INCLUYENDO NEGLIGENCIA O
 * CUALQUIER OTRA CAUSA) QUE SURJA DE CUALQUIER MANERA DEL USO DE ESTE SOFTWARE,
 * INCLUSO SI SE HA ADVERTIDO DE LA POSIBILIDAD DE TALES DA?OS.
 *
 * =============================================================================
 * Fecha de creacion: 2017-03-18
 * =============================================================================
 */


/*
   NOTA: 

   A diferencia de snap4Arduino que los pines de leds estan en:

      LEDR - Pin 0
      LEDG - Pin 1
      LEDB - Pin 2
      LED1 - Pin 3
      LED2 - Pin 4
      LED3 - Pin 5

   En C tenemos los pines en este orden:

      LED1
      LED2
      LED3
      LEDR
      LEDG
      LEDB

   Por eso se usa para este programa los Leds 1 a 3 y el R ya que son nu?meros
   de pines consecutivos. Entonces en este caso al sumar 1 a LED3 se obtiene el 
   numero de indice de LEDR.

   Los numeros concretos se pueden ver en la biblioteca sAPI en el archivo 
   "sapi_peripheral_map.h".
*/


/*==================[bibliotecas]============================================*/

#include "snap_es.h"

/*==================[macros]=================================================*/

#define DERECHA   1
#define IZQUIERDA 0


/*==================[programa principal]=====================================*/
 
programa()
{
   // ---------- CONFIGURACIONES ------------------------------

   // Inicializar y configurar la plataforma
   configurarPlataforma();  
   configurarConversorAD( ADC_ENABLE );
   
   // Crear 2 variables e inicializarlas
  
   crearVariable iterador = LED1;    // Guarda el indice del LED a encender
   crearVariable sentido  = DERECHA; // Guarda el sentido de giro actual
   crearVariable tiempoDeRetardo;
   crearVariable flag_tec1 = 0;
   crearVariable flag_tec4 = 0;

   // Inicializar todos los pines apagados
   fijarPinDigitalEn( LED1, APAGAR );
   fijarPinDigitalEn( LED2, APAGAR );
   fijarPinDigitalEn( LED3, APAGAR );
   fijarPinDigitalEn( LEDR, APAGAR );
   
   fijarPinDigitalEn( LEDG, APAGAR );
   fijarPinDigitalEn( LEDB, APAGAR );

   // ---------- REPETIR POR SIEMPRE --------------------------

   porSiempre()
   {
      if (lecturaDigital( TEC1 ) == 0)
      { 
        flag_tec1=1;
        flag_tec4=0;
      }
      if (lecturaDigital( TEC4 ) == 0)
      { 
        flag_tec1=0;
        flag_tec4=1;
      }
      if (flag_tec4 == 1)
      {
       // Si el sentido de giro es a la derecha incrementa la variable iterador   
       si( sentido == DERECHA ){
          // Esto se puede escribir tambien en C como "iterador++;"
          iterador = iterador + 1;
        }
        // Si no, entonces es a la izquierda y decrementa la variable iterador
        siNo{
           // Esto se puede escribir tambien en C como "iterador--;"
           iterador = iterador - 1;
        }
      
        // Si la variable iterador vale menor al indice LED1 entonces lo cambia a
        // LEDR que es el indice del otro extremo
        si( iterador < LED1 ){
           iterador = LEDR;
        }
      
        // Si la variable iterador vale mayor al indice LEDR entonces lo cambia a
        // LED1 que es el indice del otro extremo
        si( iterador > LEDR ){
           iterador = LED1;
        }
      
        // Enciende el Led en la posicion guardada en la variable iterador
        fijarPinDigitalEn( iterador, ENCENDER );
      
        // Espera tiempo fijado por l lectura del conversor anal?gico digital del channel 1
        tiempoDeRetardo = (lecturaAnalogica( CH3 ));
      
        for( int16_t i=0; i<(tiempoDeRetardo); i++ )
        {delay(1);}
      
        // Apaga el Led en la posicion guardada en la variable iterador   
        fijarPinDigitalEn( iterador, APAGAR );

        // Si se esta presionada la TEC2, entonces cambia el sentido de giro a
        // la izquierda
        si( no(lecturaDigital(TEC2)) ){
           sentido = IZQUIERDA;
        }
        // Si se esta presionada la TEC3, entonces cambia el sentido de giro a
        // la derecha
        si( no(lecturaDigital(TEC3)) ){
           sentido = DERECHA;
       }
      }
      if (flag_tec1 == 1 )
      {
      	
      	fijarPinDigitalEn( LEDR, ON );
      	fijarPinDigitalEn( LED1, ON );
      	fijarPinDigitalEn( LED2, ON );
      	fijarPinDigitalEn( LED3, ON );
      	
	tiempoDeRetardo = (lecturaAnalogica( CH3 ));
      
         for( int16_t i=0; i<(tiempoDeRetardo); i++ )
         {delay(1);}
         //esperarSegs( 1 );
         
	fijarPinDigitalEn( LEDR, OFF );
      	fijarPinDigitalEn( LED1, OFF );
      	fijarPinDigitalEn( LED2, OFF );
      	fijarPinDigitalEn( LED3, OFF );
      	
	for( int16_t i=0; i<(tiempoDeRetardo); i++ )
         {delay(1);}
      	
      }
   }   
}

/*==================[fin del archivo]========================================*/
