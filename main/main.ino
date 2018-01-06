#include <TimerOne.h>
#include "JobController.h"
#include "Lightsensor.h"
#include "flank.h"
#include "keypoll.h"
#include "update_LCD.h"


char displaytext[34]  = "*Test 7890123456*BratWurst01234567";
const String txtp1    = "   Programm 1    f=               ";
const String txtp2    = "   Programm 2    f=               ";
const String txtmain  = "  * Hauptmenu *   Prog 1 oder 2 ? ";

JobController scheduler;
Lightsensor light;
Flank flank = Flank(30.0);

// Die auszuführenden Aktionen. Werden vom Scheduler immer ohne Argumente aufgerufen!
void exe1(){   
  //Serial.print("data[0] = ");
  //Serial.println(light.data[0]);
  light.update();
  flank.calculate(light.data);
  Serial.print(flank.frequencyraw());
  Serial.print(",");
  Serial.println(flank.frequency());
  
}

void exe2(){
}

void exe3(){
}


void ISR_scheduler(void){   
  scheduler.check();
}



void setup() {
  LCD_setup();
  txtmain.toCharArray(displaytext,34);
  
// Jobs initialisieren: jobnr, cycleConfigPattern, Divider, dummie):
// jobs sind nach init() automatisch aktiv, scheduler läuft aber noch nicht.
// länger dauernde Jobs sollten eine höhere Nummer haben. Dann können sie im 
// gleichen pattern gestartet werden (nach den kurzen jobs), im nächsten Pattern
// wird leer gelassen, kein Job läuft = Kontrollierte Überlappung.

  scheduler.init(0, 0b1000000000000000, 2, exe1);  // ca 30 Hz
  scheduler.init(1, 0b0000000000000000,  1, exe2);
  scheduler.init(2, 0b0100000000000000,  1, exe3);

  Timer1.initialize(1000);
  Timer1.attachInterrupt(ISR_scheduler); // 
  
 /* Serial.println("Initialisazion ok.");
  wait(1000);
  Serial.println("Starting scheduler in 3...");
  wait(1000);
  Serial.println("Starting scheduler in 2...");
  wait(1000);
  Serial.println("Starting scheduler in 1...");
  wait(1000);
  scheduler.enable();
*/

}

void p1(){
  // Setup
  txtp1.toCharArray(displaytext,34);
  scheduler.init(0, 0b1000000000000000, 2, exe1);  // ca 30 Hz
  scheduler.init(1, 0b0000000000000000,  1, exe2);
  scheduler.init(2, 0b0100000000000000,  1, exe3);
  Serial.println("Starting Program 1...");
  scheduler.enable();

// Loop
  while (keypoll() != 3){
    update_LCD(displaytext);
    }

 // Exit
  scheduler.disable();
  Serial.println("Mainmenu.");
  txtmain.toCharArray(displaytext,34);  
}



void p2(){
  // Setup
  
  txtp2.toCharArray(displaytext,34);
  scheduler.init(0, 0b1000000000000000, 2, exe1);  // ca 30 Hz
  scheduler.init(1, 0b0000000000000000,  1, exe2);
  scheduler.init(2, 0b0100000000000000,  1, exe3);
  Serial.println("Starting Program 2...");
  scheduler.enable();

// Loop
  while (keypoll() != 3){
    update_LCD(displaytext);
  }

 // Exit
  scheduler.disable();
  Serial.println("Mainmenu.");
  txtmain.toCharArray(displaytext,34);
}



void loop() {
  // put your main code here, to run repeatedly:
  switch (keypoll()){
    case 1:
      Serial.println("KEY 1");
      p1();
      break;
     case 2:
      Serial.println("KEY 2");
      p2();
      break;
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

