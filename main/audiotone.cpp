// macht den ton 

#include <Arduino.h>
#include "Audiotone.h"
#define BUZZER 16//Buzzer is connected to D16 with Arduino


Audiotone::Audiotone(void){      
	f=10000;
}
  
 Audiotone::~Audiotone(void){      
	noTone(BUZZER);
}


void Audiotone::update(double lowfreq){
  double const stretch = 500;
  f = map(stretch*lowfreq, 0.5*stretch, 10*stretch, 200, 8000);
	tone(BUZZER, f);
 }



  
  
void Audiotone::stop(){
  noTone(BUZZER);
}



