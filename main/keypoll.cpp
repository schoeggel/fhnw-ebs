#include <Arduino.h>
#include "keypoll.h"
// Keypoll erfasst welche Taste gedrückt ist:
int keypoll() {
  int key=0;
  unsigned keyvalue = analogRead(6);
if(100<keyvalue&&keyvalue<150){
  key=1;}
if(550<keyvalue&&keyvalue<600){
  key=2;}
if(700<keyvalue&&keyvalue<750){
  key=3;}
if(1000<keyvalue){
  key=0;}
return (key);
}

