#include "update_LCD.h"
char eingabe[34]="*Test 234923049249242804820934820";
int Lage = 0;
int a = 0;

void setup() {
LCD_setup();
}

void loop() {
  while(a<=34){
    update_LCD(eingabe);
    delay(100);
    a++;
  }
  LCD_clear();
  a=0;
  delay(500);
}




