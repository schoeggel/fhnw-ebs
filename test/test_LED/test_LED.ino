#include "pulselight.h"
#include <Arduino.h>
float fq = 5;
int m = 0;
Pulselight pulselight;


void setup() {
pulselight.LED_setup();
Serial.begin(9600);
}

void loop() {
m = pulselight.LED_setfq(fq);
m = pulselight.LED_update(m);
delay(0);
m=millis();
Serial.println(m);
}




