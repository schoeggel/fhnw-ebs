// Phasen Informationen definieren:

typedef enum {
  RotGelb,
  Gruen,
  Gelb,
  Rot,  
  Weiss
}  Ampelfarben ;

typedef struct {
   int R;
   int G;
   int B;
} RGBcolor;

// Farbkombinationen erstellen, Farbwerte zuordnen
RGBcolor farbe[5] = {  
  {255, 128,  0   },
  {0,   128,  0   },
  {128, 128,  0   },
  {255, 0,    0   },
  {255, 255,  255 }
};


typedef struct  {
   char text[16];
   int seconds;
   RGBcolor rgb1;   // Farbe der aktiven Seite
   RGBcolor rgb2;   // Farbe der passiven Seite  --> weglassen ist immer ROT!
} Phase;



Phase p[6] = {
  {"Rot-Gelb",  2,  farbe[RotGelb]},
  {"Grün",      15, farbe[Gruen]  },
  {"Gelb",      5,  farbe[Gelb]   },
  {"Rot-Sperr", 2,  farbe[Rot]    },
  {"Rot",       -1, farbe[Rot]    },
  {"TEST",      2,  farbe[Weiss]  }
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
