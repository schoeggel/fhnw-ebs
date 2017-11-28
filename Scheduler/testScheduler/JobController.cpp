#include <Arduino.h>
#include "JobController.h"


void safeDeadMode(void){
  // stoppt alle Vorgänge, meldet über Serial den safe mode
  noInterrupts();

  while (true) {
    Serial.println("Safe dead mode entered.");
    delay(1000);
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
  static int callcounter = 0;
  if (active == false) {return;}
  
  if (cycleCounter < 1) {
    cycleCounter = 15;
  }else {
    --cycleCounter;
  }
 
  callcounter++;
  Serial.print("Instances: ");
  Serial.print(instances);
  Serial.print(" --> ");
  ++instances;
  Serial.println(instances); 
  
  if (instances > 1) {
    Serial.println("More than one instance running!");
    safeDeadMode();
  } else{
    Serial.print("Jobcontroller::check() called ");
    Serial.print(callcounter);
    Serial.print(" times. \n");
  }

  
  for (int jobnr = 0; jobnr < 4; jobnr++){
    if (jobs[jobnr].now(cycleCounter)) {
      jobs[jobnr].exe();
    }
  }
  
  
  
  --instances;
}


