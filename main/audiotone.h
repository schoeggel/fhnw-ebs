#ifndef __AUDIOTONE1
#define __AUDIOTONE1
#include <Arduino.h>


class Audiotone{
  public:
    Audiotone(void);
    ~Audiotone(void);
    void update(double lowfreq);
    void stop(void);
	  int f;
    
  private:

};

#endif
