#ifndef __JOBCONTROLLER
#define __JOBCONTROLLER
#include <Arduino.h>
#include "Job.h"

class JobController {

 public:
  JobController();
  void check();  
  void stop(int jobnr);
  void start(int jobnr);
  void init();
 
 private:
  Job Jobs[4];
  int test;
};


#endif
