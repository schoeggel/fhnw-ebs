#include "update_LCD.h"
char eingabe[34]="*Test 7890123456*BratWurst01234567";
int Lage = 0;
int a = 0;

void setup() {
LCD_setup();
}

void loop() {
  while(a<=33){
    update_LCD(eingabe);
    delay(100);
    a++;
  }
  LCD_clear();
  a=0;
  delay(500);
}




