#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x20,16,2);
unsigned long time ;
const char *eingabe[34]={"*","F","r","e","q","u","e","n","z"," ","2","0","H","z"," "," ","*","A","m","p","l","i","t","u","d","e"," ","2","A"," "," "," "," "," "};
int position = 0;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
Serial.println("Hallo");
time = millis()+1000;
lcd.init();// initialize the lcd 
lcd.init();
lcd.backlight();
}

void loop() {
  // put your main code here, to run repeatedly:
  ;
 if(0==position){
  lcd.setCursor(0,0);
      }      
else if(16==position){
  lcd.setCursor(0,1);
  }
else{
  lcd.print(eingabe[position]);
      }
position++;
delay(200);
if(position==34){
  position=0;
  lcd.clear();
}
}



