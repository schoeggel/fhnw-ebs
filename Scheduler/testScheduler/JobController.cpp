#include <Arduino.h>
#include "JobController.h"


JobController::JobController()
{
  // Neu erstellter Scheduler/JobController ist immer inaktiv!
  active = false;
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
  callcounter++;
  if (active == false) {return;}
  ++instances;
  if (instances > 1) {
    Serial.println("More than one instance running!");
  } else{
    Serial.print("Jobcontroller::check() called ");
    Serial.print(callcounter);
    Serial.print(" times. \n");
  }

  
  for (int jobnr = 0; jobnr < 4; jobnr++){
    if (jobs[jobnr].now()) {
      jobs[jobnr].exe();
    }
  }
  
  
  
  --instances;
}


