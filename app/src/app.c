/*============================================================================
 * Autor:
 * Licencia:
 * Fecha:
 *===========================================================================*/

// Inlcusiones

#include "app.h"         // <= Su propia cabecera
#include "sapi.h"        // <= Biblioteca sAPI
#include "sapi_lcd.h"
#include <stdio.h>
#include <stdint.h>

//--------------------display.h------------------------------------------HACER

static char buff[10];//Buffer para almacenar cadena. Utilizado por la función imprimirHora();
//Función para conversión de integer a ASCII
char* itoa(int value, char* result, int base) {
   // check that the base if valid
   if (base < 2 || base > 36) { *result = '\0'; return result; }

   char* ptr = result, *ptr1 = result, tmp_char;
   int tmp_value;

   do {
      tmp_value = value;
      value /= base;
      *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
   } while ( value );

   // Apply negative sign
   if (tmp_value < 0) *ptr++ = '-';
   *ptr-- = '\0';
   while(ptr1 < ptr) {
      tmp_char = *ptr;
      *ptr--= *ptr1;
      *ptr1++ = tmp_char;
   }
   return result;
}
void imprimirHora(rtc_t rtc){
   lcdClear();
   lcdGoToXY( 0, 0 );
   rtcRead( &rtc ); // en la variable de estructura rtc te queda la fecha/hora actual
   //--------------------
   itoa( (int) (rtc.mday), (char*)buff, 10 ); /* 10 significa decimal */
   /* Envio el dia */
   if( (rtc.mday)<10 )
      lcdSendStringRaw( "0" );
   lcdSendStringRaw(buff);
   lcdSendStringRaw( "/" );
   //-----------------------------------------------------------
   itoa( (int) (rtc.month), (char*)buff, 10 ); /* 10 significa decimal */
   /* Envio el mes */
   if( (rtc.month)<10 )
      lcdSendStringRaw( "0" );
   lcdSendStringRaw(buff);
   lcdSendStringRaw( "/" );
   //-----------------------------------------------------------
   itoa( (int) (rtc.year), (char*)buff, 10 ); /* 10 significa decimal */
   /* Envio el año */
   if( (rtc.year)<10 )
      lcdSendStringRaw( "0" );
   lcdSendStringRaw(buff);
   lcdSendStringRaw( " " );
   //-----------------------------------------------------------
   itoa( (int) (rtc.hour), (char*)buff, 10 ); /* 10 significa decimal */
   /* Envio el año */
   if( (rtc.hour)<10 )
      lcdSendStringRaw( "0" );
   lcdSendStringRaw(buff);
   lcdSendStringRaw( ":" );
   //-----------------------------------------------------------
   itoa( (int) (rtc.min), (char*)buff, 10 ); /* 10 significa decimal */
   /* Envio el año */
   if( (rtc.min)<10 )
      lcdSendStringRaw( "0" );
   lcdSendStringRaw(buff);
   lcdSendStringRaw( ":" );
   //-----------------------------------------------------------
   itoa( (int) (rtc.sec), (char*)buff, 10 ); /* 10 significa decimal */
   /* Envio el año */
   if( (rtc.sec)<10 )
      lcdSendStringRaw( "0" );
   lcdSendStringRaw(buff);
   //-----------------------------------------------------------   
}

//--------------------------------------------------------------------------------
// FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE ENCENDIDO O RESET.
int main( void )
{
   // ---------- CONFIGURACIONES ------------------------------

   // Inicializar y configurar la plataforma
   boardConfig();
   i2cInit( I2C0, 100000 );
   //mefInit(); -- IMPLEMENTAR
   
   /* Retardo bloqueante durante 100ms */
   delay( LCD_STARTUP_WAIT_MS );   // Wait for stable power (some LCD need that)
   
   lcdCursorSet( LCD_CURSOR_ON ); // Prende el cursor
   lcdClear();
   lcdInit( 16, 2, 5, 8 );
   lcdGoToXY( 0, 0 ); // Poner cursor en 0, 0
   lcdSendStringRaw( "Sexo B)" );
   delay(5000);
   
   //RTC -- Hace falta hacerlo dinámico para obtener la fecha y hora actual
   rtc_t rtc;// Crear estructura RTC
   rtc.year = 2023;
   rtc.month = 12;
   rtc.mday = 8;
   rtc.wday = 8;
   rtc.hour = 17;
   rtc.min = 00;
   rtc.sec= 0;
   // Inicializar RTC 
   rtcInit();
   rtcWrite( &rtc );
   
   // LOOP INFINITO
   while(1){
      imprimirHora(rtc);
      //mef(); -- Realizar
      printf("TEST/r/n");
      delay(10000);
      }
   return 0;
}
