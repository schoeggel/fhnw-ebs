#ifndef __FLANK1
#define __FLANK1
#include <Arduino.h>
#include <QuickStats.h>
#define LBUFFERSIZE 64


class Flank {
	public:
		Flank(double samplefrequency);
		double frequency(void);
		void calculate(int8_t * vdat);
		
  private:
    void findFlanks(int8_t * vdat);
    void findExtrema(int8_t * vdat);
    void findMedian(void);
    void clearTn(void);
    void PrintVector(double *vData, uint16_t bufferSize, uint8_t scaleType);
    uint16_t tn[LBUFFERSIZE/2];
    double fs;
    double freq;
};

 
 #endif
