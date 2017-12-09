#include "fft.h"
#include <Arduino.h>
#include <arduinoFFT.h>

#define SCL_INDEX 0x00
#define SCL_TIME 0x01
#define SCL_FREQUENCY 0x02


FFT::FFT(uint16_t nsamples, double samplefrequency){ 
	for (int i = 0; i<LBUFFERSIZE; i++){
		fftdataReal[i] = 0;
		fftdataImag[i] = 0;
	}
  samples = nsamples;
  fs = samplefrequency;
  freq = 0;
  afft = arduinoFFT();
	Serial.println("fft instance ready.");
}

double FFT::frequency(void){
  return(freq);
}

void FFT::clear(void){
    for (int i = 0; i<LBUFFERSIZE; i++){
      fftdataReal[i] = 0;
      fftdataImag[i] = 0;
  }
}

void FFT::calculate(void){
  //macht die fft berechnung
  /*Serial.println("Data:");
  PrintVector(fftdataReal, samples, SCL_TIME);
  */
  afft.Windowing(fftdataReal, samples, FFT_WIN_TYP_RECTANGLE, FFT_FORWARD); /* Weigh data  not hamming
  Serial.println("Weighed data:");
  PrintVector(fftdataReal, samples, SCL_TIME);
  
  afft.Compute(fftdataReal, fftdataImag, samples, FFT_FORWARD); /* Compute FFT */
 /* Serial.println("Computed Real values:");
  PrintVector(fftdataReal, samples, SCL_INDEX);
  Serial.println("Computed Imaginary values:");
  PrintVector(fftdataImag, samples, SCL_INDEX);
*/
  afft.ComplexToMagnitude(fftdataReal, fftdataImag, samples); /* Compute magnitudes */
  /*Serial.println("Computed magnitudes:");
  PrintVector(fftdataReal, (samples >> 1), SCL_FREQUENCY);  
*/
  // f < 1 Hz abschwächen. Bei 64 Samples sind das N 1..2 (0.5 Hz per Bin)
  fftdataReal[0] = 0.33 * fftdataReal[0];
  fftdataReal[1] = 0.66 * fftdataReal[1];
  
  freq = afft.MajorPeak(fftdataReal, samples, fs);
  Serial.println(freq,6);

    
}





void FFT::PrintVector(double *vData, uint16_t bufferSize, uint8_t scaleType)
{
  for (uint16_t i = 0; i < bufferSize; i++)
  {
    double abscissa;
    /* Print abscissa value */
    switch (scaleType)
    {
      case SCL_INDEX:
        abscissa = (i * 1.0);
  break;
      case SCL_TIME:
        abscissa = ((i * 1.0) / fs);
  break;
      case SCL_FREQUENCY:
        abscissa = ((i * 1.0 * fs) / samples);
  break;
    }
    Serial.print(abscissa, 6);
    Serial.print(" ");
    Serial.print(vData[i], 4);
    Serial.println();
  }
  Serial.println();
}
