#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x20,16,2);

void setup() {
  // put your setup code here, to run once:
lcd.init();// initialize the lcd 
lcd.init();
lcd.backlight();
}

void loop() {
  // put your main code here, to run repeatedly:
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Programm1  Key1");
lcd.setCursor(0,1);
lcd.print("Programm2  Key2");
delay(100);
if(getkey()==1){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Programm1  Start");
  delay(5000);
}
if(getkey()==2){
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("Programm2  Start");
  delay(5000);
}
}

int getkey() {
  // put your main code here, to run repeatedly:
int key = 0;
unsigned keyvalue = analogRead(6);
if(100<keyvalue&&keyvalue<150){
  key=1;}
if(550<keyvalue&&keyvalue<600){
  key=2;}
if(700<keyvalue&&keyvalue<750){
  key=3;}
if(1000<keyvalue){
  key=0;}
return key;
}


