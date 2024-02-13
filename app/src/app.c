#include <stdio.h>
#include <stdint.h>
#include "sapi.h"        // <= Biblioteca sAPI
#include "sapi_lcd.h"
#include <stdio.h>
#include <stdint.h>
#include <time.h>


#define BUTTON0 TEC1
   #define BUTTON1 TEC2
   #define BUTTON2 TEC3
   #define BUTTON3 TEC4

#define BUTTON_LOGIC BUTTON_ONE_IS_UP
// Callbacks for Button 0 events

void myButton1PressedCallback(void* param)
{
   printf("Boton 0 presionado\r\n");
}
void myButton1ReleasedCallback(void* param)
{
   printf("Boton 0 liberado\r\n");
}
void myButton1HoldPressedCallback(void* param)
{
   printf("Boton 0 presionado durante mas de 3 segundos\r\n");
}


// Definición de los estados
typedef enum {
    STAND_BY,
    RELOJ,
   MENU,
    MENU_MODIFICAR_FECHA_HORA_ACTUAL,
   MENU_MODIFICAR_FECHA_HORA_PROGRAMA,
   MENU_SELECCIONAR_MODO,
   REGANDO
} State;



typedef enum {
    NOP,
    MODIFICAR_FECHA_HORA,
   MODIFICAR_FECHA_HORA_PROGRAMA
} SubState;


// Definición de la estructura de la máquina de estados
typedef struct {
    State current_state;
} StateMachine;          

typedef struct {
    SubState current_state;
} SubStateMachine;   

int diasDeRiego[7] = {0};
static char buff[10];//Buffer para almacenar cadena. Utilizado por la función imprimirHora();
 static int contadorModoInteligente=0;
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
   //--------------------
    printf("antes de convertir es %d \n /n",rtc.mday);  
   itoa( (int) (rtc.mday), (char*)buff, 10 ); /* 10 significa decimal */
   /* Envio el dia */
   if( (rtc.mday)<10 )
      lcdSendStringRaw( "0" );
   printf("le mandas el valor %c \n /n",*buff);
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
   lcdGoToXY( 11, 0 );
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
  // itoa( (int) (rtc.sec), (char*)buff, 10 ); /* 10 significa decimal */
   /* Envio el año */
  // if( (rtc.sec)<10 )
    //  lcdSendStringRaw( "0" );
  // lcdSendStringRaw(buff);
   //-----------------------------------------------------------   
}


void imprimirMenuHora(rtc_t rtc){
   lcdClear();
   lcdGoToXY( 3, 1 );
   //--------------------
    printf("antes de convertir es %d \n /n",rtc.mday);  
   itoa( (int) (rtc.mday), (char*)buff, 10 ); /* 10 significa decimal */
   /* Envio el dia */
   if( (rtc.mday)<10 )
      lcdSendStringRaw( "0" );
   printf("le mandas el valor %c \n /n",*buff);
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
   
   
   lcdGoToXY( 4, 0 );
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
   
   if(rtc.hour < 12)
    lcdSendStringRaw( " AM" );
   if(rtc.hour >= 12)
    lcdSendStringRaw( " PM" );
   //-----------------------------------------------------------
  // itoa( (int) (rtc.sec), (char*)buff, 10 ); /* 10 significa decimal */
   /* Envio el año */
  // if( (rtc.sec)<10 )
    //  lcdSendStringRaw( "0" );
  // lcdSendStringRaw(buff);
   //-----------------------------------------------------------   
}

int getDayOfWeek(const rtc_t* rtc) {
      struct tm timeStruct;

    // Configurar la estructura tm con los valores proporcionados
    timeStruct.tm_year = rtc->year - 1900;  // Año desde 1900
    timeStruct.tm_mon = rtc->month - 1;     // Mes (0-11)
    timeStruct.tm_mday = rtc->mday;         // Día del mes
    timeStruct.tm_hour = 0;                 // Hora (opcional)
    timeStruct.tm_min = 0;                  // Minuto (opcional)
    timeStruct.tm_sec = 0;                  // Segundo (opcional)

    // Obtener el día de la semana (0-6, donde 0 es domingo)
    mktime(&timeStruct);

    return timeStruct.tm_wday;
}

int es_momento_de_regar(rtc_t* rtc, const rtc_t* rtc_hora_regar){
   int aux = getDayOfWeek(rtc);
   printf("getDayOfWeek = %d \n", aux);
   int dia = (getDayOfWeek(rtc) + 6) % 7;
   printf("hoy es dia numero %d , y el estado de regar es %d \n",dia,diasDeRiego[dia]);
   if (diasDeRiego[dia]){
      if (rtc->hour == rtc_hora_regar->hour){
         if (rtc->min == rtc_hora_regar->min){
            return 1;
         }
      }
   }
   return 0;
}

int main()
{
   
   
   gpioInit(GPIO0,GPIO_OUTPUT);
   gpioInit(GPIO5,GPIO_OUTPUT);
   gpioWrite(GPIO0,OFF);
   gpioWrite(GPIO5,OFF);
   
   StateMachine machine;
   machine.current_state = RELOJ;
   
   SubStateMachine submachine;
   submachine.current_state = NOP;
   
   int subMachineIsActive = 0;
   boardInit();
   boardConfig();
   i2cInit( I2C0, 100000 );
   
   int modoInteligente = 0;
   int auxModoInteligente = 0;
   adcInit(ADC_ENABLE);
   //Variables del sensor
   int16_t humedad_maxima = 65;
   int16_t humedad_minima = 50;
   
   
   
   
   
    /* Retardo bloqueante durante 100ms */
   delay( LCD_STARTUP_WAIT_MS );   // Wait for stable power (some LCD need that)

   lcdCursorSet( LCD_CURSOR_ON ); // Prende el cursor
   lcdClear();
   lcdInit( 16, 2, 5, 8 );
   lcdGoToXY( 0, 0 );
   lcdSendStringRaw("INICIANDO");
   lcdGoToXY( 0, 1 );
   lcdSendStringRaw("REGADOR");

   rtcInit();
   
   //RTC -- Hace falta hacerlo dinámico para obtener la fecha y hora actual
   rtc_t rtc;// Crear estructura RTC
   rtc.year = 2023;
   rtc.month = 12;
   rtc.mday = 2;
   rtc.wday = 0;
   rtc.hour = 17;
   rtc.min = 01;
   rtc.sec= 55;
   delay(4000);
   rtcRead(&rtc);
   delay(4000);
   if(rtc.year == 0){
      rtc.year = 2024;
      rtc.month = 2;
      rtc.mday=15;
      rtc.hour = 11;
      rtc.min = 32;
      rtc.sec= 55;
      rtcWrite(&rtc);
   }
   
   
   
   rtc_t rtc_hora_regar;
   rtc_hora_regar.year = 2024;
   rtc_hora_regar.month = 1;
   rtc_hora_regar.mday = 1;
   rtc_hora_regar.wday = 0;
   rtc_hora_regar.hour = 17;
   rtc_hora_regar.min = 01;
   
   int tiempoRiego = 10;
   // Inicializar RTC 
   //rtcInit();
   //rtcWrite( &rtc );
   delay(2000);
   imprimirMenuHora(rtc);
   
    // Temporization
   delay_t refreshButton;
   delay_t refreshButtonEvents;
   delayInit( &refreshButton, 50 );
   delayInit( &refreshButtonEvents, 10 );

   // Button objects
   button_t myButton0;
   button_t myButton1;
   button_t myButton2;
   button_t myButton3;

   // Button 0 is handled with callbacks
   buttonInit( &myButton0,                  // Button structure (object)
               BUTTON0, BUTTON_LOGIC,       // Pin and electrical connection
               50,                          // Button scan time [ms]
               TRUE,                        // checkPressedEvent
               TRUE,                        // checkReleasedEvent
               TRUE,                        // checkHoldPressedEvent
               3000,                        // holdPressedTime [ms]
               myButton1PressedCallback,    // pressedCallback
               myButton1ReleasedCallback,   // releasedCallback
               myButton1HoldPressedCallback // holdPressedCallback
             );

   // Rest of buttons handled by pooling
   
   // Buttton 1 not check released event
   buttonInit( &myButton1,                  // Button structure (object)
               BUTTON1, BUTTON_LOGIC,       // Pin and electrical connection
               50,                          // Button scan time [ms]
               TRUE,                        // checkPressedEvent
               FALSE,                       // checkReleasedEvent
               TRUE,                        // checkHoldPressedEvent
               5000,                        // holdPressedTime [ms]
               0,                           // pressedCallback
               0,                           // releasedCallback
               0                            // holdPressedCallback
             );


   buttonInit( &myButton2,                  // Button structure (object)
               BUTTON2, BUTTON_LOGIC,       // Pin and electrical connection
               50,                          // Button scan time [ms]
               TRUE,                        // checkPressedEvent
               TRUE,                        // checkReleasedEvent
               TRUE,                        // checkHoldPressedEvent
               2000,                        // holdPressedTime [ms]
               0,                           // pressedCallback
               0,                           // releasedCallback
               0                            // holdPressedCallback
             );
   buttonInit( &myButton3,                  // Button structure (object)
               BUTTON3, BUTTON_LOGIC,       // Pin and electrical connection
               50,                          // Button scan time [ms]
               TRUE,                        // checkPressedEvent
               TRUE,                        // checkReleasedEvent
               TRUE,                        // checkHoldPressedEvent
               2000,                        // holdPressedTime [ms]
               0,                           // pressedCallback
               0,                           // releasedCallback
               0                            // holdPressedCallback
             );
   
   
   

   // LOOP INFINITO
   int delayTime = 0;
   int t = 0;
   while(1){
      delayTime++;
      // 4 segundos = 5000000
      //printf("subMAchineIsActive = %d",subMachineIsActive);
      if(delayTime % 500000 == 0)
         printf("inteligente = %d  isSubMachineActive %d  delayTime= %d \n",modoInteligente,subMachineIsActive,delayTime);
      if(delayTime == 5000000){
         float a = (float)adcRead(CH1);
         int16_t humedad_sensor= 100 - ((adcRead(CH1)*100)/1024);
         printf( "humedad_sensor1 = %d \%  \n", humedad_sensor);
      }

      if(subMachineIsActive == 0 && delayTime > 5000000){
                     
         rtcRead( &rtc );
         //printf("leí %d minutos y %d segundos \n /n",rtc.min, rtc.sec);
         
         if (modoInteligente == 0){
            
            //hay que preguntar si estoy en alguna de todas las fechas posibles de riego y regar
            if(es_momento_de_regar(&rtc, &rtc_hora_regar)){
               printf("comienzo a regar \n /n");
               printf("comienzo a regar \n /n");
               printf("comienzo a regar \n /n");
               printf("comienzo a regar \n /n");
               printf("comienzo a regar \n /n");
               printf("comienzo a regar \n /n");
               printf("comienzo a regar \n /n");
               printf("comienzo a regar \n /n");
               printf("comienzo a regar \n /n");
               
               machine.current_state=REGANDO;
               
               lcdClear();
               lcdGoToXY( 0, 0 );
               lcdSendStringRaw("REGANDO ...");
               delay(1000);
            }
         }else {
            // Reviso el sensor de humedad para el riego automatico
            float a = (float)adcRead(CH1);
            int16_t humedad_sensor= 100 - ((adcRead(CH1)*100)/1024);
            printf( "humedad_sensor = %d \%  \n", humedad_sensor);
            if (humedad_sensor<humedad_minima){
               lcdClear();
               lcdGoToXY( 0, 0 );
               lcdSendStringRaw("REGANDO ...");
               delay(1000);
               machine.current_state=REGANDO;
               gpioWrite(GPIO0,ON);
               gpioWrite(GPIO5,ON);
            }
         }
         
         
         
         delayTime=0;
      }
     
         // Refrehs button FSMs every 50 ms
      if( delayRead(&refreshButton) ) {
         buttonFsmUpdate( &myButton0 );
         buttonFsmUpdate( &myButton1 );
         buttonFsmUpdate( &myButton2 );
         buttonFsmUpdate( &myButton3 );
      }
      
   
      /*if(current_state == STAND_BY){
         
      }*/
      
      
      if(machine.current_state == RELOJ){
         static int z=0;
         static int minutos;
         z++;
         if((z == 5000000) || (z ==0)){
            rtcRead(&rtc);
            delay(100);
            imprimirMenuHora(rtc);
            if(z != 0){
               z=0;
            }
         }
         
         if( (buttonEventGet( &myButton3 ) == BUTTON_PRESSED) ) {
            printf("Se presiono boton 3\r\n");
            buttonEventHandled( &myButton3 );
            machine.current_state = MENU_MODIFICAR_FECHA_HORA_ACTUAL;
            lcdGoToXY( 0, 0 );
            lcdSendStringRaw("MODIFICAR FECHA");
            lcdGoToXY( 0, 1 );
            lcdSendStringRaw("Y HORA ACTUAL");
         }

         
         
      }
      
      
      if(machine.current_state == REGANDO){
         
         if (modoInteligente == 0){
              
            int aux=0;
            int tiempoMax=20000000 * tiempoRiego; //13 segundos por relé
            
            gpioWrite(GPIO0,ON);
            int condicion=1;
            while((aux < tiempoMax)  && condicion == 1) {
               aux++;
               if(aux == tiempoMax/2){
                  gpioWrite(GPIO0,OFF);
                  gpioWrite(GPIO5,ON);
               }
               if(aux == tiempoMax){
                   gpioWrite(GPIO5,OFF);
               }
               
               
                                 // Refrehs button FSMs every 50 ms
               if( delayRead(&refreshButton) ) {
                  buttonFsmUpdate( &myButton0 );
               }
               if( (buttonEventGet( &myButton0 ) == BUTTON_PRESSED) ){
                  buttonEventHandled( &myButton0 );
                  condicion=0;
                  
                  lcdClear();
                  lcdGoToXY( 3, 0 );
                  lcdSendStringRaw("CERRANDO ");
                  lcdGoToXY( 3, 1 );
                  lcdSendStringRaw("CANILLAS ... ");
                  delay(3000);
                  
                  lcdClear();
                  lcdGoToXY( 0, 0 );
                  lcdSendStringRaw(" RIEGO CANCELADO");
                  
                  delay(3000);
                  
                  gpioWrite(GPIO0,OFF);
                  gpioWrite(GPIO5,OFF);
                  
                  machine.current_state = MENU_MODIFICAR_FECHA_HORA_ACTUAL;
                  lcdClear();
                  lcdGoToXY( 0, 0 );
                  lcdSendStringRaw("MODIFICAR FECHA");
                  lcdGoToXY( 0, 1 );
                  lcdSendStringRaw("Y HORA PROGRAMA");
                  
                  
                  //aumentamos la hora un minuto para evitar problemas?
                  //aumentamos la hora un minuto para evitar problemas.
                  //si es momento de regar aumentamos 1 minuto a la hora
                  rtcRead( &rtc );
                  if(es_momento_de_regar(&rtc, &rtc_hora_regar)){
                     if(rtc.min != 59){
                        rtc.min= rtc.min+1;
                        rtcWrite(&rtc);
                     }
                  }
               }
               
               
            }
            
                  machine.current_state = MENU_MODIFICAR_FECHA_HORA_ACTUAL;
                  lcdClear();
                  lcdGoToXY( 0, 0 );
                  lcdSendStringRaw("MODIFICAR FECHA");
                  lcdGoToXY( 0, 1 );
                  lcdSendStringRaw("Y HORA PROGRAMA");
            
            //Riego en modo normal
         /*   printf("switcheando relé \n /n");
            //delay(30000);
            gpioWrite(GPIO0,ON);
           
            
            delay((tiempoRiego/2)*6*1000);
            
            gpioWrite(GPIO0,OFF);
            gpioWrite(GPIO5,ON);
            
            delay((tiempoRiego/2)*6*1000);
            
            gpioWrite(GPIO5,OFF);
            
            
            machine.current_state = MENU_MODIFICAR_FECHA_HORA_ACTUAL;
            lcdGoToXY( 0, 0 );
            lcdSendStringRaw("MODIFICAR FECHA");
            lcdGoToXY( 0, 1 );
            lcdSendStringRaw("Y HORA PROGRAMA");*/

         }else{
            //Riego inteligente
            //Mido la humedad para ver si tengo que parar
            //Si apreto el boton 3 desactivo el riego automatico
            if( (buttonEventGet( &myButton3 ) == BUTTON_PRESSED) ){
               
               lcdClear();
               lcdGoToXY( 3, 0 );
               lcdSendStringRaw("CERRANDO ");
               lcdGoToXY( 3, 1 );
               lcdSendStringRaw("CANILLAS ... ");
               delay(3000);
               
               lcdClear();
               lcdGoToXY( 0, 0 );
               lcdSendStringRaw("RIEGO FINALIZADO");
               delay(3000);
               modoInteligente=0;
               gpioWrite(GPIO0,OFF);
               gpioWrite(GPIO5,OFF);
               machine.current_state = MENU_MODIFICAR_FECHA_HORA_ACTUAL;
               lcdClear();
               lcdGoToXY( 0, 0 );
               lcdSendStringRaw("MODIFICAR FECHA");
               lcdGoToXY( 0, 1 );
               lcdSendStringRaw("Y HORA PROGRAMA");
            } else{
               //Mido la humedad para ver si tengo que parar
               float a = (float)adcRead(CH1);
               int16_t humedad_sensor= 100 - ((adcRead(CH1)*100)/1024);
               printf( "humedad_sensor = %d \%  \n", humedad_sensor);
               if (humedad_sensor>humedad_maxima){
                  
                  lcdClear();
                  lcdGoToXY( 3, 0 );
                  lcdSendStringRaw("CERRANDO ");
                  lcdGoToXY( 3, 1 );
                  lcdSendStringRaw("CANILLAS ... ");
                  delay(3000);
                  
                  lcdClear();
                  lcdGoToXY( 0, 0 );
                  lcdSendStringRaw("RIEGO FINALIZADO");
                  
                  delay(3000);
                  gpioWrite(GPIO0,OFF);
                  gpioWrite(GPIO5,OFF);
                  machine.current_state = MENU_MODIFICAR_FECHA_HORA_ACTUAL;
                  lcdClear();
                  lcdGoToXY( 0, 0 );
                  lcdSendStringRaw("MODIFICAR FECHA");
                  lcdGoToXY( 0, 1 );
                  lcdSendStringRaw("Y HORA PROGRAMA");
               }
            }
         }
      }
      
      //---------------------------------------------------------------------------------------
      if(machine.current_state == MENU){
         
         //este está al pedo
         if( (buttonEventGet( &myButton3 ) == BUTTON_PRESSED) ) {
            printf("Se presiono boton 3\r\n");
            buttonEventHandled( &myButton3 );
            machine.current_state = MENU_MODIFICAR_FECHA_HORA_ACTUAL;
            lcdGoToXY( 0, 0 );
            lcdSendStringRaw("MODIFICAR FECHA");
            lcdGoToXY( 0, 1 );
            lcdSendStringRaw("Y HORA ACTUAL");
         }

      }
      if(machine.current_state == MENU_MODIFICAR_FECHA_HORA_ACTUAL){
         
         if(subMachineIsActive == 0 && (buttonEventGet( &myButton3 ) == BUTTON_PRESSED) ) {
            printf("Se presiono boton 3\r\n");
            buttonEventHandled( &myButton3 );
            machine.current_state = MENU_MODIFICAR_FECHA_HORA_PROGRAMA;
            lcdClear();
            lcdGoToXY( 0, 0 );
            lcdSendStringRaw("MODIFICAR FECHA");
            lcdGoToXY( 0, 1 );
            lcdSendStringRaw("Y HORA PROGRAMA");
         }
         
         if(subMachineIsActive == 0 && (buttonEventGet( &myButton2 ) == BUTTON_PRESSED) ) {
            printf("Se presiono boton 2\r\n");
            buttonEventHandled( &myButton2 );
            submachine.current_state = MODIFICAR_FECHA_HORA;
            lcdClear();
            lcdGoToXY( 0, 0 );
            rtcRead( &rtc );
            imprimirHora(rtc);
            subMachineIsActive=1;
         }
         
         if(submachine.current_state == MODIFICAR_FECHA_HORA){
            static int a=0;
            static int count=0;
            count++;
            if(count == 1000000){
               if(a == 0){
                  lcdGoToXY( 0, 0 );
                  lcdSendStringRaw("  ");
               }
               if(a == 1){
                  lcdGoToXY( 3, 0 );
                  lcdSendStringRaw("  ");
               }
               if(a == 2){
                  lcdGoToXY( 6, 0 );
                  lcdSendStringRaw("  ");
               }
               if(a == 3){
                  lcdGoToXY( 11, 0 );
                  lcdSendStringRaw("  ");
               }
               if(a == 4){
                  lcdGoToXY( 14, 0 );
                  lcdSendStringRaw("  ");
               }
               
            }
            if(count == 1200000){
               imprimirHora(rtc);
               count=0;
            }
            if( (buttonEventGet( &myButton0 ) == BUTTON_PRESSED) ) {
               printf("Se presiono boton 0\r\n");
               buttonEventHandled( &myButton0 );
               a++;
               

               if(a == 5){
                  a=0;
                  machine.current_state = MENU_MODIFICAR_FECHA_HORA_PROGRAMA;
                  submachine.current_state = NOP;
                  lcdClear();
                  rtcWrite( &rtc );
                  lcdGoToXY( 0, 0 );
                  lcdSendStringRaw("MODIFICAR FECHA");
                  lcdGoToXY( 0, 1 );
                  lcdSendStringRaw("Y HORA PROGRAMA");
                  subMachineIsActive=0;
               }
            }
            if( (buttonEventGet( &myButton1 ) == BUTTON_PRESSED) ) {
               printf("Se presiono boton 1\r\n");
               buttonEventHandled( &myButton1 );
               static int first = 0;
               if(first == 0){
                  rtcRead( &rtc );
                  first++;
               }
               
      
               if(a == 0) {
                  if(rtc.mday == 1) {
                     rtc.mday = 31;
                  }
                  else
                  {
                     rtc.mday--;
                  }
               };
               if(a == 1) {
                  if(rtc.month == 1){
                     rtc.month=12;
                  }
                  else
                  {
                     rtc.month--;
                  }
               }
               if(a == 2) rtc.year--;
               if(a == 3){
                  if(rtc.hour == 0){
                     rtc.hour = 23;
                  }
                  else
                  {
                     rtc.hour--;
                  }
               }
               if(a == 4) {
                  if(rtc.min == 0){
                     rtc.min = 59;
                  }
                  else
                  {
                     rtc.min--;
                  }
                  
               }

               delay(100);
               printf("rtc.day = %d \r\n",rtc.wday);
               imprimirHora(rtc);
              
            }
            if( (buttonEventGet( &myButton2 ) == BUTTON_PRESSED) ) {
               printf("Se presiono boton 2\r\n");
               buttonEventHandled( &myButton2 );
               static int first = 0;
               if(first == 0){
                  rtcRead( &rtc );
                  first++;
               }
               
      
               if(a == 0) {
                  if(rtc.mday == 31) {
                     rtc.mday = 1;
                  }
                  else
                  {
                     rtc.mday++;
                  }
               };
               if(a == 1) {
                  if(rtc.month == 12){
                     rtc.month=1;
                  }
                  else
                  {
                     rtc.month++;
                  }
               }
               if(a == 2) rtc.year++;
               if(a == 3){
                  if(rtc.hour == 23){
                     rtc.hour = 0;
                  }
                  else
                  {
                     rtc.hour++;
                  }
               }
               if(a == 4) {
                  if(rtc.min == 59){
                     rtc.min = 0;
                  }
                  else
                  {
                     rtc.min++;
                  }
                  
               }


               delay(100);
               printf("rtc.day = %d \r\n",rtc.wday);
               imprimirHora(rtc);
              
            }
            
         }

      }

      if(machine.current_state == MENU_MODIFICAR_FECHA_HORA_PROGRAMA){

         if(subMachineIsActive == 0 && (buttonEventGet( &myButton3 ) == BUTTON_PRESSED) ) {
            printf("Se presiono boton 3\r\n");
            buttonEventHandled( &myButton3 );
            machine.current_state = MENU_SELECCIONAR_MODO;
            lcdClear();
            lcdGoToXY( 0, 0 );
            lcdSendStringRaw("MODIFICAR");
            lcdGoToXY( 0, 1 );
            lcdSendStringRaw("MODO DE RIEGO");
         }
         
         if(subMachineIsActive == 0 && (buttonEventGet( &myButton2 ) == BUTTON_PRESSED) ) {
            printf("Se presiono boton 2\r\n");
            buttonEventHandled( &myButton2 );
            submachine.current_state = MODIFICAR_FECHA_HORA_PROGRAMA;
            lcdClear();
            lcdGoToXY( 0, 0 );
            lcdSendStringRaw("LUNES");
            lcdGoToXY( 12, 0 );
            if(diasDeRiego[0] == 0){
               lcdSendStringRaw("OFF");
            }
            else
            {
               lcdSendStringRaw("ON");
            }
            subMachineIsActive=1;
         }
         
         static int a=0;
         static int step = 0;
         if(subMachineIsActive == 1 && (buttonEventGet( &myButton2 ) == BUTTON_PRESSED) && step ==0 ) {
            printf("Se presiono boton 2\r\n");
            buttonEventHandled( &myButton2 );
            
            
            if(diasDeRiego[a] == 0){
               diasDeRiego[a]=1;
            }
            else
            {
               diasDeRiego[a]=0;
            }
            lcdGoToXY( 12, 0 );
            if(diasDeRiego[a] == 0){
               lcdSendStringRaw("OFF");
            }
            else
            {
               lcdSendStringRaw("ON ");
            }
            
         }
         
         
         if(subMachineIsActive == 1 && (buttonEventGet( &myButton0 ) == BUTTON_PRESSED) && step == 0) {
            printf("Se presiono boton 0\r\n");
            buttonEventHandled( &myButton0 );
            a++;
            
            if(a < 7){
               lcdClear();
               lcdGoToXY( 0, 0 );
               if(a==1) lcdSendStringRaw("MARTES");
               if(a==2) lcdSendStringRaw("MIERCOLES");
               if(a==3) lcdSendStringRaw("JUEVES");
               if(a==4) lcdSendStringRaw("VIERNES");
               if(a==5) lcdSendStringRaw("SABADO");
               if(a==6) lcdSendStringRaw("DOMINGO");

               
               lcdGoToXY( 12, 0 );
               if(diasDeRiego[a] == 0){
                  lcdSendStringRaw("OFF");
               }
               else
               {
                  lcdSendStringRaw("ON");
               }
            }
            else
            {
               a=0;
               step++;
               lcdClear();
               lcdGoToXY( 0, 0 );
               lcdSendStringRaw("HORA:");
               lcdGoToXY( 6, 0 );
               itoa( (int) (rtc_hora_regar.hour), (char*)buff, 10 ); 
               if( (rtc_hora_regar.hour)<10 )
                  lcdSendStringRaw( "0" );
               lcdSendStringRaw(buff);
               lcdSendStringRaw( ":" );
               lcdGoToXY( 9, 0 );
               itoa( (int) (rtc_hora_regar.min), (char*)buff, 10 ); 
               if( (rtc_hora_regar.min)<10 )
                  lcdSendStringRaw( "0" );
               lcdSendStringRaw(buff);
            }
         }
         if(subMachineIsActive == 1 && step == 1){
            static int count=0;
            count++;
            if(count == 1000000){
               if(a == 0){
                  lcdGoToXY( 6, 0 );
                  lcdSendStringRaw("  ");
               }
               if(a == 1){
                  lcdGoToXY( 9, 0 );
                  lcdSendStringRaw("  ");
               }
            }
            if(count == 1200000){
               lcdClear();
               lcdGoToXY( 0, 0 );
               lcdSendStringRaw("HORA:");
               lcdGoToXY( 6, 0 );
               itoa( (int) (rtc_hora_regar.hour), (char*)buff, 10 ); 
               if( (rtc_hora_regar.hour)<10 )
                  lcdSendStringRaw( "0" );
               lcdSendStringRaw(buff);
               lcdSendStringRaw( ":" );
               lcdGoToXY( 9, 0 );
               itoa( (int) (rtc_hora_regar.min), (char*)buff, 10 ); 
               if( (rtc_hora_regar.min)<10 )
                  lcdSendStringRaw( "0" );
               lcdSendStringRaw(buff);
               count=0;
            }
            if( (buttonEventGet( &myButton0 ) == BUTTON_PRESSED) ) {
               printf("Se presiono boton 0\r\n");
               buttonEventHandled( &myButton0 );
               a++;
               

               if(a == 2){
                  a=0;
                  step++;
                  lcdClear();
                  lcdGoToXY( 0, 0 );
                  lcdSendStringRaw("TIEMPO RIEGO: ");
                  itoa( (int) (tiempoRiego), (char*)buff, 10 ); 
                  lcdSendStringRaw(buff);
               }
            }
            if( (buttonEventGet( &myButton1 ) == BUTTON_PRESSED) ) {
               printf("Se presiono boton 1\r\n");
               buttonEventHandled( &myButton1 );
               if(a == 0){
                  if(rtc_hora_regar.hour == 0){
                     rtc_hora_regar.hour = 23;
                  }
                  else
                  {
                     rtc_hora_regar.hour--;
                  }
               }
               if(a == 1) {
                  if(rtc_hora_regar.min == 0){
                     rtc_hora_regar.min = 59;
                  }
                  else
                  {
                     rtc_hora_regar.min--;
                  }
                  
               }
               delay(100);
               printf("rtc_hora_regar.day = %d \r\n",rtc_hora_regar.wday);
               lcdClear();
               lcdGoToXY( 0, 0 );
               lcdSendStringRaw("HORA:");
               lcdGoToXY( 6, 0 );
               itoa( (int) (rtc_hora_regar.hour), (char*)buff, 10 ); 
               if( (rtc_hora_regar.hour)<10 )
                  lcdSendStringRaw( "0" );
               lcdSendStringRaw(buff);
               lcdSendStringRaw( ":" );
               lcdGoToXY( 9, 0 );
               itoa( (int) (rtc_hora_regar.min), (char*)buff, 10 ); 
               if( (rtc_hora_regar.min)<10 )
                  lcdSendStringRaw( "0" );
               lcdSendStringRaw(buff);
            }
            if( (buttonEventGet( &myButton2 ) == BUTTON_PRESSED) ) {
               printf("Se presiono boton 2\r\n");
               buttonEventHandled( &myButton2 );
      
               if(a == 0){
                  if(rtc_hora_regar.hour == 23){
                     rtc_hora_regar.hour = 0;
                  }
                  else
                  {
                     rtc_hora_regar.hour++;
                  }
               }
               if(a == 1) {
                  if(rtc_hora_regar.min == 59){
                     rtc_hora_regar.min = 0;
                  }
                  else
                  {
                     rtc_hora_regar.min++;
                  }
                  
               }
               delay(100);
               printf("rtc_hora_regar.day = %d \r\n",rtc_hora_regar.wday);
               lcdClear();
               lcdGoToXY( 0, 0 );
               lcdSendStringRaw("HORA:");
               lcdGoToXY( 6, 0 );
               itoa( (int) (rtc_hora_regar.hour), (char*)buff, 10 ); 
               if( (rtc_hora_regar.hour)<10 )
                  lcdSendStringRaw( "0" );
               lcdSendStringRaw(buff);
               lcdSendStringRaw( ":" );
               lcdGoToXY( 9, 0 );
               itoa( (int) (rtc_hora_regar.min), (char*)buff, 10 ); 
               if( (rtc_hora_regar.min)<10 )
                  lcdSendStringRaw( "0" );
               lcdSendStringRaw(buff);
            }
         }
         if(subMachineIsActive == 1 && step == 2){
            if( (buttonEventGet( &myButton0 ) == BUTTON_PRESSED) ) {
               buttonEventHandled( &myButton0 );
               a=0;
               step = 0;
               subMachineIsActive = 0;
               machine.current_state = MENU_MODIFICAR_FECHA_HORA_ACTUAL;
               lcdClear();
               lcdGoToXY( 0, 0 );
               lcdSendStringRaw("MODIFICAR FECHA");
               lcdGoToXY( 0, 1 );
               lcdSendStringRaw("Y HORA ACTUAL");
            }
            
            if( (buttonEventGet( &myButton2 ) == BUTTON_PRESSED) ) {
               buttonEventHandled( &myButton2 );
               if (a==0){
                  a=1;
               }
               if (a>=6){
                  a = 1;
               }else{
                  a++;
               }
               tiempoRiego=10*a;
               lcdClear();
               lcdGoToXY( 0, 0 );
               lcdSendStringRaw("TIEMPO RIEGO: ");
               itoa( (int) (tiempoRiego), (char*)buff, 10 ); 
               lcdSendStringRaw(buff);
               
            }
         }
         
         

      }

      if(machine.current_state == MENU_SELECCIONAR_MODO){

            if(subMachineIsActive == 0 && (buttonEventGet( &myButton3 ) == BUTTON_PRESSED) ) {
               printf("Se presiono boton 3 en MENU_SELECCIONAR_MODO\r\n");
               buttonEventHandled( &myButton3 );
               machine.current_state = RELOJ;
               rtcRead(&rtc);
               imprimirMenuHora(rtc);

            }
            
            if(subMachineIsActive == 0 && (buttonEventGet( &myButton2 ) == BUTTON_PRESSED) ) {
               printf("Se presiono boton 2 en MENU_SELECCIONAR_MODO\r\n");
               buttonEventHandled( &myButton2 );
               lcdClear();
               lcdGoToXY( 0, 0 );
               subMachineIsActive=1;
               if (modoInteligente){
                  lcdGoToXY( 0, 0 );
                  lcdSendStringRaw("MODO INTELIGENTE");
                  lcdGoToXY( 0, 1 );
                  lcdSendStringRaw("ON");
               }else{
                  lcdGoToXY( 0, 0 );
                  lcdSendStringRaw("MODO INTELIGENTE");
                  lcdGoToXY( 0, 1 );
                  lcdSendStringRaw("OFF");
               }   
            }
            
            
           
            if (subMachineIsActive == 1 && ((buttonEventGet( &myButton2 ) == BUTTON_PRESSED) || (buttonEventGet( &myButton1 ) == BUTTON_PRESSED))){
               printf("Se presiono boton 1 o 2 en MENU_SELECCIONAR_MODO\r\n");
               buttonEventHandled( &myButton2 );
               buttonEventHandled( &myButton1 );
              
               if(contadorModoInteligente==0){
                  auxModoInteligente=modoInteligente;
                  contadorModoInteligente++;
               }
               
               if (auxModoInteligente){
                  auxModoInteligente=0;
                  lcdClear();
                  lcdGoToXY( 0, 0 );
                  lcdSendStringRaw("MODO INTELIGENTE");
                  lcdGoToXY( 0, 1 );
                  lcdSendStringRaw("OFF");
               }else{
                  auxModoInteligente=1;
                  lcdClear();
                  lcdGoToXY( 0, 0 );
                  lcdSendStringRaw("MODO INTELIGENTE");
                  lcdGoToXY( 0, 1 );
                  lcdSendStringRaw("ON");
               } 
            }
            
            if (buttonEventGet( &myButton0 ) == BUTTON_PRESSED){
               printf("Se presiono boton 0 en MENU_SELECCIONAR_MODO\r\n");
               buttonEventHandled( &myButton0 );
               machine.current_state = MENU_SELECCIONAR_MODO;
               submachine.current_state = NOP;
               subMachineIsActive=0;
               lcdClear();
               lcdGoToXY( 0, 0 );
               lcdSendStringRaw("MODIFICAR");
               lcdGoToXY( 0, 1 );
               lcdSendStringRaw("MODO DE RIEGO");
               modoInteligente = auxModoInteligente;
               contadorModoInteligente=0;
            }

         }


   
   }
  
    return 0;
}
