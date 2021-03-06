#ifndef __PULSELIGHT
#define __PULSELIGHT
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

class Pulselight {
  public:
    void LED_setup();
    void LED_end();
    float LED_setfq(float fq);
    double LED_update(float m);
};

#endif
