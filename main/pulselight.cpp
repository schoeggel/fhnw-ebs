#include <Adafruit_NeoPixel.h>
#include "pulselight.h"
#include <Arduino.h>
#include <math.h>


#define PIN 10
Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, PIN, NEO_GRB + NEO_KHZ800);

void Pulselight::LED_setup(){
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void Pulselight::LED_end(){
  strip.setPixelColor(0,0,0,0);
  strip.show();
}

double Pulselight::LED_setfq(double fq){
  double m =255/(1/fq);
  return m;
  }

void Pulselight::LED_update(double m) {
static int richtung = 1;
static int count = 1;
static double intervall = 0.066;
double light = (m*count*intervall);
/*Serial.print("m*count*intervall= ");
Serial.print(m);
Serial.print(", ");
Serial.print(count);
Serial.print(", ");
Serial.print(intervall);
Serial.print(", ");
Serial.println(light);
*/

  light = 255*pow((light/255),3);  // Gammakorrektur 
  count = count+richtung;
  if (light>=255) {
    richtung=-1;
    count = count-1;
    light = 255;
  }
  if (light<=0){
    richtung=1;
    count = count+1;
  }
  strip.setPixelColor(0,light,0,0);
  strip.show();
}



