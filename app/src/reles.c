#include "app.h"
#include "reles.h"

void initReles(){
   gpioInit(GPIO0,GPIO_OUTPUT);
   gpioInit(GPIO5,GPIO_OUTPUT);
   }

void encenderRele(int rele){
   if (rele == 1){
      gpioWrite(GPIO0,OFF);
   }else{
      gpioWrite(GPIO5,OFF);
   }
}

void apagarRele(int rele){
   if (rele == 1){
      gpioWrite(GPIO0,ON);
   }else{
      gpioWrite(GPIO5,ON);
   }
}