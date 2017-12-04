#include "Lightsensor.h"


Lightsensor light;
long t0;
long t1;


void setup() {
}

void loop() {
  // put your main code here, to run repeatedly:


t0 = millis();
  for(int i = 0; i< 1000; i++){
    light.update();
  }

t1 = millis();
Serial.print("Gemessene Zeit [ms]: ");
Serial.println(t1-t0);

}

void wait(int t){ // aus irgendeinem Grund funktioniert die "delay()" Funktion innerhalb des ISR nicht mehr.
  // dauert ca 1 ms:
  for (volatile int u = 0; u < 10; u++){
    for (volatile int v = 0; v < 100; v++){
      for (volatile int w = 0; w < t; w++){
          ;
      } 
    }
  }
}

