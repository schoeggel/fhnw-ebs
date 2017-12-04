int key = 0;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
unsigned keyvalue = analogRead(6);
if(100<keyvalue&&keyvalue<150){
  key=1;}
if(550<keyvalue&&keyvalue<600){
  key=2;}
if(700<keyvalue&&keyvalue<750){
  key=3;}
if(1000<keyvalue){
  key=0;}
Serial.println(key);
}

