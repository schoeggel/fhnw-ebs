#ifndef __JOBCONTROLLER
#define __JOBCONTROLLER
#include <Arduino.h>
#include "Job.h"

class JobController {

 public:
  JobController();
  void check();  
  void stopjob(int jobnr);
  void startjob(int jobnr);
  void enable();
  void disable();
  void init(int jobnr, int cycleConfigPattern, int divider, int exe);
 
 private:
  Job jobs[4];
  int test;
  int instances;
  bool active;

};


#endif
