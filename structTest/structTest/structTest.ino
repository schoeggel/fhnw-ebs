// Phasen Informationen definieren:

typedef struct  {
   char text[16];
   int seconds;
   int cR;
   int cG;
   int cB;
} Phase;

Phase p[6] = {
  {"Rot-Gelb",  2,  255,  128,  0   },
  {"Grün",      15, 0,    128,  0   },
  {"Gelb",      5,  128,  128,  0   },
  {"Rot-Sperr", 2,  255,  0,    0   },
  {"Rot",       -1, 255,  0,    0   },
  {"TEST",      2,  255,  255,  255 },
};






void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
   Serial.println("Serial ready");
 
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(p[1].text);
  
}
