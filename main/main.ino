#include <TimerOne.h>
#include "JobController.h"
#include "Lightsensor.h"
#include "flank.h"
#include "keypoll.h"
#include "update_LCD.h"
#include "pulselight.h"
#include "audiotone.h"


char displaytext[34]  = "*Test 7890123456*BratWurst01234567";
const String txtp1    = "   Programm 1    f=               ";
const String txtp2    = "   Programm 2    f=               ";
const String txtmain  = "  * Hauptmenu *   Prog 1 oder 2 ? ";

JobController scheduler;
Lightsensor light;
Flank flank = Flank(30.0);
Pulselight pulselight;
Audiotone buzzer; 
int m = 0;
bool runLedUpdater = false;


// Die auszuführenden Aktionen. Werden vom Scheduler immer ohne Argumente aufgerufen!
void exe1(){   
  light.update();
  flank.calculate(light.data);
  Serial.print(flank.frequencyraw());
  Serial.print(",");
  Serial.println(flank.frequency());
  freqToDispText();
}

void exe2(){
    runLedUpdater = true;
}

void exe3(){
  // Tone
  buzzer.update(flank.frequency());
 // Serial.println(millis());
  }


void ISR_scheduler(void){   
  scheduler.check();
}



void setup() {
  LCD_setup();
  txtmain.toCharArray(displaytext,34);
  pulselight.LED_setup();
  Timer1.initialize(1000);
  Timer1.attachInterrupt(ISR_scheduler); // 
}

void p1(){
  // Setup
  txtp1.toCharArray(displaytext,34);
  
  // Jobs initialisieren: jobnr, cycleConfigPattern, Divider, dummie):
  // jobs sind nach init() automatisch aktiv, scheduler läuft aber noch nicht.
  // länger dauernde Jobs sollten eine höhere Nummer haben. Dann können sie im 
  // gleichen pattern gestartet werden (nach den kurzen jobs), im nächsten Pattern
  // wird leer gelassen, kein Job läuft = Kontrollierte Überlappung.
  scheduler.init(0, 0b1000000000000000, 2, exe1);  // ca 30 Hz
  scheduler.init(1, 0b0000000010000000, 2, exe2);  // LED update
  scheduler.init(2, 0b0000000000000000, 99, exe3);
  Serial.println("Starting Program 1...");
  scheduler.enable();

// Loop
  bool runprog = true;
  while (runprog){
    update_LCD(displaytext);
    if (runLedUpdater) {
      runLedUpdater = false;
      m = pulselight.LED_setfq(flank.frequency());
      pulselight.LED_update(m);
      Serial.println(millis());
    }

    if (keypoll() == 3){
      wait(15); 
      if (keypoll() == 3){
        runprog = false;
      }
    }
  }
  
 // Exit
  scheduler.disable();
  Serial.println("Mainmenu.");
  txtmain.toCharArray(displaytext,34); 
  pulselight.LED_end(); 
  oneBeep();
}




void p2(){
  // Setup
  bool runprog = true;
  txtp2.toCharArray(displaytext,34);
  scheduler.init(0, 0b1000000000000000, 2, exe1);  // ca 30 Hz
  scheduler.init(1, 0b0000000000000000, 99, exe2);
  scheduler.init(2, 0b0100000000000000,  2, exe3);
  Serial.println("Starting Program 2...");
  scheduler.enable();

// Loop
  while (runprog){
    update_LCD(displaytext);

    if (keypoll() == 3){
      wait(15); 
      if (keypoll() == 3){
        runprog = false;
      }
    }
  }

 // Exit
  scheduler.disable();
  Serial.println("Mainmenu.");
  txtmain.toCharArray(displaytext,34);
  buzzer.stop();
  oneBeep();
}

void oneBeep(){
  noTone(16);
  tone(16,1000,150);
}

void freqToDispText(){
  // setzt die Frequenz mit 2 Nachkommastellen in den Text ein
  double f = flank.frequency();
  String s = String(f, 2);
  s += " Hz ";
  for (int i = 0; i < s.length(); i++){
    displaytext[20+i] = s[i];
  }
}


void loop() {
  // put your main code here, to run repeatedly:
  switch (keypoll()){
    case 1:
      oneBeep();
      Serial.println("KEY 1");
      p1();
      break;
     case 2:
      oneBeep();
      Serial.println("KEY 2");
      p2();
      break;
     case 3:
      oneBeep();
  }
      update_LCD(displaytext);
}

void wait(int t){ //  "delay()" funktioniert innerhalb des ISR nicht.
  // dauert ca 1 ms:
  for (volatile int u = 0; u < 10; u++){
    for (volatile int v = 0; v < 100; v++){
      for (volatile int w = 0; w < t; w++){
          ;
      } 
    }
  }
}

