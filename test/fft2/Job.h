#ifndef __JOB
#define __JOB
#include <Arduino.h>


class Job{
  public:
    Job();
    bool now(int cycleCounter);
    void stop();
    void start();
    void init(int cycleConfigPattern, int divider,void (*exe)());
    void (*exe)();
  
  private:
    int cycleConfigPattern;
    bool jobEnabled;
    int divider;
    int dividerCounter;
};

#endif
