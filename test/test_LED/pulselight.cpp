#include <Adafruit_NeoPixel.h>
#include "pulselight.h"

#define PIN 10
Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, PIN, NEO_GRB + NEO_KHZ800);

void LED_setup(){
strip.begin();
strip.show(); // Initialize all pixels to 'off'
}

float LED_setfq(float fq){
  float m =127.5/(1/fq);
  return m;
  }

void LED_update(float m) {
static int richtung = 1;
static int count = 0;
static int intervall = 0.008;
int light = 127.5+(m*count*intervall);
strip.setPixelColor(1,light,0,0);
count++;
if (light>=255){
richtung=richtung*(-1);  
}

}



