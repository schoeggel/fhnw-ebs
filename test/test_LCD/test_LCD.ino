#include "update_LCD.h"
#include <Arduino.h>
char eingabe[34]="*Test 7890123456*BratWurst01234567";
int Lage = 0;
int a = 0;

void setup() {
  Serial.begin(9600);
LCD_setup();
}

void loop() {
  while(a<=33){
    update_LCD(eingabe);
    delay(0);
    a++;
  }
Serial.println(millis());
    a=0;
  delay(500);
  LCD_clear();
}




