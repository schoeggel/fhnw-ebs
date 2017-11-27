#ifndef __JOB
#define __JOB
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

#endif
