#ifndef __FLANK1
#define __FLANK1
#include <Arduino.h>
#define LBUFFERSIZE 64
#define LHYSTERESIS 20

void printArray(int8_t * v, char * title, uint8_t len);
  

class Flank {
	public:
		Flank(double samplefrequency);
		double frequency(void);
		void calculate(int8_t * vdat);
		void printArray(int8_t * v, char * title, uint8_t len);
    void printTn();
    
  private:
    void findFlanks(int8_t * vdat);
    void findExtrema(int8_t * vdat);
    void findMedian();
    void clearTn(void);
    void PrintVector(double *vData, uint16_t bufferSize, uint8_t scaleType);
    uint16_t tn[LBUFFERSIZE/2];
    double fs;
    double freq;
};

 
 #endif
