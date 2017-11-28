#ifndef __LIGHTSENSOR1
#define __LIGHTSENSOR1
#include <Arduino.h>
#include "Job.h"
#define BUFFERSIZE 64
#define FILTER_K 0.2

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
