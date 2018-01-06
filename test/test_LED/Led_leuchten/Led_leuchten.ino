#include <Adafruit_NeoPixel.h>
#include <Arduino.h>


#define PIN 10
Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, PIN, NEO_GRB + NEO_KHZ800);


void setup() {
  // put your setup code here, to run once:
strip.begin();
strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  // put your main code here, to run repeatedly:
  strip.setPixelColor(0,255,0,0);

}
