#ifndef __LIGHTSENSOR1
#define __LIGHTSENSOR1
#include <Arduino.h>
#define LBUFFERSIZE 64
#define FILTER_K 0.4

class Lightsensor {
	public:
		Lightsensor();
		void update();
		uint8_t data[LBUFFERSIZE];

   private:
   void shiftdata();
};

 
 #endif
