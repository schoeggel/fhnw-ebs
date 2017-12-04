// (C) joel koch 2017
// jobcontroller kontrolliert verschiedene jobs.
// die jobs können zeiltich in einem ablaufraster (bitmaske) mit divider konfiguriert werden
// die eigentliche auszuführende funktion wird über einen funciton pointer übergeben.
// der JobController besitzt eine check-methode, die zyklisch aufgerufen werden muss.
// aufrufintervall der check() methode zusammen mit den bitmasken und dividern ergeben die 
// effektive job-aufruf-intervalle. Ein neuer Controller ist immer inaktiv. Neue Jobs immer aktiv.
// Wenn alle Jobs initialisiert sind, muss der Kontroller aktiviert werden mit .enable(); und danach
// über einen TimerInterrupt zyklisch aufgerufen werden über die .check() methode.

#include <TimerThree.h>
#include "JobController.h"


JobController scheduler;


// Die auszuführenden Aktionen. Werden vom Scheduler immer ohne Argumente aufgerufen!
void exe1(){
  Serial.println("exe 1__ called.");
}

void exe2(){
  Serial.print("exe _2_ called... ");
  // Mit dem Wait() kann das Beenden der scheduler.check() verhindert werden, bevor .check() das nächste mal aufgerufen wird.
  // scheduler sollte den nicht erlaubten Zustand erkennen und in den safe mode wechseln.
  // wait(3000);
  Serial.println("ok");
}

void exe3(){
  Serial.println("exe __3 called.");
}


void ISR_scheduler(void){
  // standardmässig werden die interrupts deaktiviert während der ISR. Es soll aber ein Mehrfachauftruf möglich sein, damit der
  // Fehler erkannt werden kann (safemode mit meldung über Serielle Schnittstelle)
  interrupts();     
  scheduler.check();
}



void setup() {
// Jobs initialisieren: jobnr, cycleConfigPattern, Divider, dummie):
// jobs sind nach init() automatisch aktiv, scheduler läuft aber noch nicht.
  scheduler.init(0, 0b1111111111111111, 2, exe1);
  scheduler.init(1, 0b0000000000000001, 1, exe2);
  scheduler.init(2, 0b0100000000000001, 1, exe3);

  Timer3.initialize(600000);
  Timer3.attachInterrupt(ISR_scheduler); // 
 
  wait(2000);
  Serial.println("Starting scheduler test...");
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

