#include <LiquidCrystal_I2C.h>
#include <Wire.h> 
LiquidCrystal_I2C lcd(0x20,16,2);

#include <Adafruit_NeoPixel.h>

#define PIN 10
Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, PIN, NEO_GRB + NEO_KHZ800);
unsigned long time ;
boolean ledon = false;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
Serial.println("Hallo");
strip.begin();
strip.show(); // Initialize all pixels to 'off'
time = millis()+1000;
lcd.init();// initialize the lcd 
lcd.init();
lcd.backlight();
}

void loop() {
  // put your main code here, to run repeatedly:
if(time<=millis()){
  time = millis()+1000;
  if(ledon){
    colorWipe(strip.Color(0, 0, 0), 50);
    ledon = false;
    lcd.clear();
    lcd.setCursor(4,1);
    lcd.print("LED aus");
  }
  else{
   colorWipe(strip.Color(0, 20, 0), 50); // Green
   ledon = true;
   lcd.clear();
   lcd.setCursor(4,0);
   lcd.print("LED an"); 
  }
}

}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}
