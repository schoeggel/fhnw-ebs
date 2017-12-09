#ifndef __FFT1
#define __FFT1
#include <Arduino.h>
#include <arduinoFFT.h>
#define LBUFFERSIZE 64   // unter anderem für lightsensor und fft verwendet.


class FFT {
	public:
		FFT(uint16_t nsamples, double samplefrequency);
		double fftdataReal[LBUFFERSIZE];
		double fftdataImag[LBUFFERSIZE];
		double frequency(void);
		void calculate(void);
    void clear(void);
    
  private:
  void PrintVector(double *vData, uint16_t bufferSize, uint8_t scaleType);
  uint16_t samples;
  double fs;
  arduinoFFT afft;
  double freq;
};

 
 #endif
