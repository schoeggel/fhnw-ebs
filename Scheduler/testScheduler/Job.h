#ifndef __JOB
#define __JOB
#include <Arduino.h>


class Job{
   //friend class JobController;

public:
  Job();
  bool now();
  void stop();
  void start();
  void init(int cycleConfigPattern, int divider,void (*exe)());

  int cycleConfigPattern;
  int cylceCounter;
  bool jobEnabled;
  int divider;
  int dividerCounter;
  void (*exe)();

};

#endif
