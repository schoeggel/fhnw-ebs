#include <LiquidCrystal_I2C.h>
#include "update_LCD.h"
LiquidCrystal_I2C lcd(0x20,16,2);

void LCD_setup(){
lcd.init();// initialize the lcd 
lcd.init();
lcd.backlight();
}

void LCD_clear(){
  lcd.clear();
  }

void update_LCD(char * eingabe) {
static int Lage = 0;
if(0==Lage){
  lcd.setCursor(0,0);
  //Beim 1. Zeichen wird der Cursor auf 
  //erste Position von Zeile 1 gesetzt
  }      
else if(16==Lage){
  lcd.setCursor(0,1);
  //Beim 18. Zeichen wird der Cursor auf 
  //erste Position von Zeile 2 gesetzt
  }
else{
  lcd.print(eingabe[Lage]);
  //Gibt ein Zeichen aufs LCD aus
      }
Lage++;
if(34<=Lage){
  Lage = 0;
}
}



