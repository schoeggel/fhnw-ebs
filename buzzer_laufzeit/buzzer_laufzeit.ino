#define BUZZER 16//Buzzer is connected to D16 with Arduino
#include <Wire.h>
unsigned long time ;
#define PIN 10
void setup()   //initialization
{
  pinMode(BUZZER,OUTPUT);//set D16 to output module
  Serial.begin(9600);
  Serial.println("Hallo");
  time = millis();
}
void loop() //main function,it will looping execution
{
  int i=0;
  //Give a sound
  time = millis();
  for(i=0;i<10000;i++)
  {
    digitalWrite(BUZZER,HIGH);//turn on power supply
    delay(3);                 // delay for 1ms
    digitalWrite(BUZZER,LOW);//Turn off power supply
    delay(3);               //delay for 1ms
  }
  time = millis()- time;
  Serial.println(time);
 }


