// (C) joel koch 2017
// jobcontroller kontrolliert verschiedene jobs.
// die jobs können zeiltich in einem ablaufraster (bitmaske) mit divider konfiguriert werden
// die eigentliche auszuführende funktion wird über einen funciton pointer übergeben.
// der JobController besitzt eine check-methode, die zyklisch aufgerufen werden muss.
// aufrufintervall der check() methode zusammen mit den bitmasken und dividern ergeben die 
// effektive job-aufruf-intervalle. Ein neuer Controller ist immer inaktiv. Neue Jobs immer aktiv.
// Wenn alle Jobs initialisiert sind, muss der Kontroller aktiviert werden mit .enable(); und danach
// über einen TimerInterrupt zyklisch aufgerufen werden über die .check() methode.


#include <Arduino.h>
#include "JobController.h"


void safeDeadMode(void){
  // stoppt alle Vorgänge, meldet über Serial den safe mode
  noInterrupts();

  while (true) {
    Serial.println("Safe dead mode entered.");
    for (volatile int i  = 0; i < 65000; i++) {;}
  }
}



JobController::JobController()
{
  // Neu erstellter Scheduler/JobController ist immer inaktiv!
  active = false;
  cycleCounter = 16;
  instances = 0;
}


void JobController::init(int jobnr, int cycleConfigPattern, int divider, void (*exe)()){
    jobs[jobnr].init(cycleConfigPattern, divider, exe);
}

void JobController::startjob(int jobnr)
{
  jobs[jobnr].start();
}

void JobController::stopjob(int jobnr)
{
  jobs[jobnr].stop();
}


void JobController::enable(){
  active = true;
}

void JobController::disable(){
  active = false;
}

void JobController::check(){
  if (active == false) {return;} 
  if (cycleCounter < 1) {
    cycleCounter = 15;
  }else {
    --cycleCounter;
  }
  
  ++instances;
  if (instances > 1) {
    Serial.println("More than one instance running!");
    safeDeadMode();
  } else{
  //  Serial.print("Jobcontroller::check() called ");
  //  Serial.print(callcounter);
  //  Serial.print(" times. \n");
  }

  for (int jobnr = 0; jobnr < 4; jobnr++){
    if (jobs[jobnr].now(cycleCounter)) {
      jobs[jobnr].exe();
    }
  }
  
  --instances;
}


