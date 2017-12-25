#include "pulselight.h"
float fq = 10;

void setup() {
LED_setup();
}

void loop() {
pulselight.LED_setfq(fq);
pulselight.LED_update();
delay(8);
}




