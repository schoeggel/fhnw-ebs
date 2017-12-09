char text[10] = "1234567890";

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  printone(text, 1);
  printone(text, 2);
  printone(text, 5);
  printone(text, 5);
}


char printone(char * s,int pos){
  Serial.println(s[pos]);
}

