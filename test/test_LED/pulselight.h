#ifndef __PULSELIGHT
#define __PULSELIGHT
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
void pulselight();
void LED_setup();
float LED_setfq(float fq);
void LED_update(float m);
#endif


