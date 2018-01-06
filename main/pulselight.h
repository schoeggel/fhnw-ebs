#ifndef __PULSELIGHT
#define __PULSELIGHT
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

class Pulselight {
  public:
    void LED_setup();
    void LED_end();
    double LED_setfq(double fq);
    void LED_update(double m);
};

#endif
