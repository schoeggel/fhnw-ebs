#include <TimerThree.h>
#include "JobController.h"
#include "Lightsensor.h"
#include "flank.h"

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
// Jobs initialisieren: jobnr, cycleConfigPattern, Divider, dummie):
// jobs sind nach init() automatisch aktiv, scheduler läuft aber noch nicht.
// länger dauernde Jobs sollten eine höhere Nummer haben. Dann können sie im 
// gleichen pattern gestartet werden (nach den kurzen jobs), im nächsten Pattern
// wird leer gelassen, kein Job läuft = Kontrollierte Überlappung.

  scheduler.init(0, 0b1000000000000000, 2, exe1);  // ca 30 Hz
  scheduler.init(1, 0b0000000000000000,  1, exe2);
  scheduler.init(2, 0b0100000000000000,  1, exe3);

  Timer3.initialize(1000);
  Timer3.attachInterrupt(ISR_scheduler); // 
  
  Serial.println("Initialisazion ok.");
  wait(1000);
  Serial.println("Starting scheduler in 3...");
  wait(1000);
  Serial.println("Starting scheduler in 2...");
  wait(1000);
  Serial.println("Starting scheduler in 1...");
  wait(1000);
  scheduler.enable();
}

void loop() {
  // put your main code here, to run repeatedly:
  ;
}

void wait(int t){ // aus irgendeinem Grund funktioniert die "delay()" Funktion innerhalb des ISR nicht mehr.
  // dauert ca 1 ms:
  for (volatile int u = 0; u < 10; u++){
    for (volatile int v = 0; v < 100; v++){
      for (volatile int w = 0; w < t; w++){
          ;
      } 
    }
  }
}

