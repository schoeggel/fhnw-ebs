#include "pulselight.h"
float fq = 10;
float m = 0;
Pulselight pulselight;

void setup() {
pulselight.LED_setup();
}

void loop() {
m = pulselight.LED_setfq(fq);
pulselight.LED_update(m);
delay(8);
}




