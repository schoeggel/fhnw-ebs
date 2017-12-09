// Ein Job ist ein Teil des JobControllers. 

#include <Arduino.h>
#include "Job.h"

Job::Job()
  {      
    cycleConfigPattern = 0;
    jobEnabled = false;
    divider = 1;
    dividerCounter = 0;
  }


void Job::init(int cycleConfigPattern, int divider, void (*exe)()){
  this->cycleConfigPattern = cycleConfigPattern;
  this->divider = divider;
  this->exe = exe;
  jobEnabled = true;
}



void Job::stop(){
  jobEnabled = false;
}


void Job::start(){
  jobEnabled = true;
}

  
bool Job::now(int cycleCounter){
  // checken, ob bit an der Stelle "cylceCounter" gesetzt ist
  
  if (cycleCounter > 15) {return false;}
  uint8_t bit = (cycleConfigPattern >> cycleCounter) & 1;
  if ((bit == 1) && (jobEnabled == true)) {

    // Divider noch berücksichtigen:
    dividerCounter++;
    if (dividerCounter >= divider){
      dividerCounter = 0;
      return true;
    } else {
      return false;
    }
  
  } else {
    return false;
  }
}


