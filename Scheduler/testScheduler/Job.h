#ifndef __SCHEDULER
#define __SCHEDULER
#include <Arduino.h>


class Job{

public:
  Job();
  bool now(uint8_t thisCycle);
  void stop();
  void start();

  int cycleConfigPattern;
  int cylceCounter;
  bool jobEnabled;
  int divider;
  int dividerCounter;

};



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
