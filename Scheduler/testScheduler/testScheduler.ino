#include "JobController.h"
 
JobController scheduler;

void setup() {
  // put your setup code here, to run once:
scheduler.start(1);
}

void loop() {
  // put your main code here, to run repeatedly:
scheduler.check();
}
