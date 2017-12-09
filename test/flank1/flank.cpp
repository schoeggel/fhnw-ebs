#include "flank.h"
#include <Arduino.h>
#define SCL_INDEX 0x00
#define SCL_TIME 0x01
#define SCL_FREQUENCY 0x02
#define DIR_UP 0x01
#define DIR_DOWN 0x02

Flank::Flank(double samplefrequency){
  fs = samplefrequency;
  clearTn();
}

double Flank::frequency(void){
  return(freq);
}


void Flank::clearTn(){
  // So kann auch bei nur teilweise befülltem tn mit dem median gearbeitet werden. Ausser wenn nur ein tn wert befüllt ist....
  for (int i = 0; i < LBUFFERSIZE; i++){
    tn[i] = LBUFFERSIZE-1;
    i++;
    tn[i] = 0;
  }
}

void Flank::findMedian(){
  Serial.println("Tn-Array:");
    for (int k = 0; k<LBUFFERSIZE/2; k++){
      if (k == LBUFFERSIZE/4) {
        Serial.println("----------------");
      }
      Serial.println(tn[k]);
    }
  
}

void Flank::calculate(int8_t * data){
  //macht die fft berechnung
  clearTn();
  Serial.println("\n\tCLEARED TN ----");
  findMedian(); // Nur zum Drucken im Moment
  findFlanks(data);
  findExtrema(data);
  findMedian(); 
  Serial.println(freq,6);
}


void Flank::findFlanks(int8_t * v){
  /* suche nach wecheselnden flanken.
   * Schreibe die vergangenen Anzahl Bins n 
   * zwischen den gefundenen Flanken in die 
   * erste Hälfte des Arrays tn[].
  */
  int k = 0;
  uint8_t dir = 0;      // Richtung undefiniert
  if (v[0] < 0) {
    dir = DIR_UP;
  } else {
    dir = DIR_DOWN;
  }

// vektor absuchen nach flanke bis vektor fertig oder bis 16 flanken gefunden.
  uint16_t bincounter = 0;
  for (int i = 1; (i < LBUFFERSIZE) && (k < (LBUFFERSIZE / 4)); i++){
    ++bincounter;
    if ( (dir = DIR_UP) && (v[i] > 0) && (v[i-1] <= 0) ){    // steigend durch Nullachse
        tn[k] = bincounter;
        ++k;
        bincounter = 0;        
        dir = DIR_DOWN;
        
      } else if ( (dir = DIR_DOWN) && (v[i] <= 0) && (v[i-1] > 0) ){    // sinkend durch Nullachse
        tn[k] = bincounter;
        ++k;
        bincounter = 0;        
        dir = DIR_UP;
      }
  }    
 }


void Flank::findExtrema(int8_t * v){
  /* suche nach Peaks Min Max.
   * Schreibe die vergangenen Anzahl Bins n 
   * zwischen den gefundenen Peaks in die 
   * zweite Hälfte des Arrays tn[].
  */
  int k = LBUFFERSIZE/4;
  uint8_t dir = 0;      // Richtung undefiniert
  if (v[1] - v[0] > 0) {
    dir = DIR_UP;
  } else {
    dir = DIR_DOWN;
  }

// vektor absuchen nach peaks bis vektor fertig oder bis 16 peaks gefunden.
  uint16_t bincounter = 0;
  int8_t delta = 0;
  for (int i = 1; (i < LBUFFERSIZE) && (k < (LBUFFERSIZE / 2)); i++){
    ++bincounter;
    delta = v[i] - v[i-1];
    if ( (dir = DIR_UP) && (delta < 0) ){    // wendepunkt oben gefunden
        tn[k] = bincounter;
        ++k;
        bincounter = 0;        
        dir = DIR_DOWN;
        
      } else if ( (dir = DIR_DOWN) && (delta > 0) ){    // wendepunkt unten gefunden
        tn[k] = bincounter;
        ++k;
        bincounter = 0;        
        dir = DIR_UP;
      }
  }    
 }



