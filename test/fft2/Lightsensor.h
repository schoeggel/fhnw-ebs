#ifndef __LIGHTSENSOR1
#define __LIGHTSENSOR1
#include <Arduino.h>
#define FILTER_K 0.4
#define LBUFFERSIZE 64   // unter anderem für lightsensor und fft verwendet.

class Lightsensor {
	public:
		Lightsensor();
		void update();
		uint8_t data[LBUFFERSIZE];
    void removeDC(uint8_t * src, double * dst);
    void removeDC(uint8_t * src, int8_t * dst);

   private:
   void shiftdata();
};

 
 #endif
