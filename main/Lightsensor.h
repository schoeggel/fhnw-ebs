#ifndef __LIGHTSENSOR1
#define __LIGHTSENSOR1
#include <Arduino.h>
#define BUFFERSIZE 60
#define FILTER_K 0.25

class Lightsensor {
	public:
		Lightsensor();
		void update();
		const int size = BUFFERSIZE;
		int data[BUFFERSIZE];

   private:
   void shiftdata();
};

 
 #endif
