
#include <TimerThree.h>
#include "JobController.h"
#include "Lightsensor.h"
#include "fft.h";


JobController scheduler;
Lightsensor light;
FFT fft = FFT(LBUFFERSIZE,32);


// Die auszuführenden Aktionen. Werden vom Scheduler immer ohne Argumente aufgerufen!
void exe1(){   
  //Serial.print("data[0] = ");
  //Serial.println(light.data[0]);
  //Serial.println("*");
  light.update();
}

void exe2(){
  /*Serial.println(0);
  Serial.println(255);
  Serial.println(255);
  Serial.println(0);

  
  //Serial.println("\ndata[]: **********");
  for (int i = 0; i<LBUFFERSIZE; i++){
    Serial.println(light.data[i]);
  }
*/


  light.removeDC(light.data, fft.fftdataReal);
  /*Serial.println(0);
  Serial.println(-128);
  Serial.println(127);
  Serial.println(0);

  Serial.println("FFT-Data-Real:");
  for (int i = 0; i<LBUFFERSIZE; i++){
    Serial.print(fft.fftdataReal[i]);
    Serial.print(",");
    Serial.println(fft.frequency());
  }

  */
  fft.calculate();
  fft.clear();
}


void exe3(){
  
}


void ISR_scheduler(void){   
  scheduler.check();
}



void setup() {
// Jobs initialisieren: jobnr, cycleConfigPattern, Divider, dummie):
// jobs sind nach init() automatisch aktiv, scheduler läuft aber noch nicht.
// länger dauernde Jobs sollten eine höhere Nummer haben. Dann können sie im 
// gleichen pattern gestartet werden (nach den kurzen jobs), im nächsten Pattern
// wird leer gelassen, kein Job läuft = Kontrollierte Überlappung.

  scheduler.init(0, 0b1000000000000000, 2, exe1);  // ca 30 Hz
  scheduler.init(1, 0b0100000000000000,  32, exe2);
  scheduler.init(2, 0b0100000000000000,  8, exe3);

  Timer3.initialize(1000);
  Timer3.attachInterrupt(ISR_scheduler); // 
  
  Serial.println("Initialisazion ok.");
  wait(1000);
  Serial.println("Starting scheduler in 3...");
  wait(1000);
  Serial.println("Starting scheduler in 2...");
  wait(1000);

  

  
  Serial.println("Starting scheduler in 1...");
  wait(1000);
  scheduler.enable();
}

void loop() {
  // put your main code here, to run repeatedly:
  ;
}

void wait(int t){ // aus irgendeinem Grund funktioniert die "delay()" Funktion innerhalb des ISR nicht mehr.
  // dauert ca 1 ms:
  for (volatile int u = 0; u < 10; u++){
    for (volatile int v = 0; v < 100; v++){
      for (volatile int w = 0; w < t; w++){
          ;
      } 
    }
  }
}

