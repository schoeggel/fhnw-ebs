#include <Arduino.h>
#include "JobController.h"


JobController::JobController()
{
  // Neu erstellter Scheduler/JobController ist immer inaktiv!
  active = false;
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
  if (~active) {return;}
  
  ++instances;
  if (instances > 1) {
    Serial.println("More than one instance running!");
  }
  
  
  
  --instances;
}


//TODO 'int exe' --> type noch ändern auf function pointer!
void JobController::init(int jobnr, int cycleConfigPattern, int divider, int exe){
    // Die Jobs können nicht hardcodiert werden, weil von hier aus die auszuführenden Funktionen nicht sichtbar sind.
    // Es muss mit den im Unterricht gezeigten Function pointer gearbeitet werden ! Der init reicht die argumente an den 
    // über jobnr angepsrochenen job.init() weiter
    jobs[jobnr].init(cycleConfigPattern, divider, exe);
}

