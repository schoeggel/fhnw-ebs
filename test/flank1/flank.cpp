#include "flank.h"
#include <Arduino.h>
#define SCL_INDEX 0x00
#define SCL_TIME 0x01
#define SCL_FREQUENCY 0x02
#define DIR_UP 0x01
#define DIR_DOWN 0x02

void printArray(int8_t * v, char * title, uint8_t len){
  Serial.println(title);
    for (int i = 0; i < len; i++){
      Serial.println(v[i]);
    }
  Serial.print(title);
  Serial.print(" --- End ---\n");
}






Flank::Flank(double samplefrequency){
  fs = samplefrequency;
  clearTn();
}

double Flank::frequency(void){
  return(freq);
}



void Flank::printTn(){
   Serial.println("Tn-Array:");
    for (int k = 0; k<LBUFFERSIZE/2; k++){
      if (k == LBUFFERSIZE/4) {
        Serial.println("----------------");
      }
      Serial.println(tn[k]);
    }
}

void Flank::clearTn(){
  // So kann auch bei nur teilweise befülltem tn mit dem median gearbeitet werden. Ausser wenn nur ein tn wert befüllt ist....
  for (int i = 0; i < LBUFFERSIZE/2; i++){ // condition (i<BUFFERSIZE) überschreibt anderen speicher :-)
    tn[i] = LBUFFERSIZE-1;
    i++;
    tn[i] = 0;
  }
}

void Flank::findMedian(){
  // sortiere array nach Werten
  // verwirf den tiefsten wert
  // nimm vom rest die 3 zentralen werte [indizes 15,16,17]
  // bilde einen gewichtete mittelwert


  int size = LBUFFERSIZE/2;
  
  //void sort(int a[], int size) {
    for(int i=0; i<(size-1); i++) {
        for(int o=0; o<(size-(i+1)); o++) {
                if(tn[o] > tn[o+1]) {
                    int t = tn[o];
                    tn[o] = tn[o+1];
                    tn[o+1] = t;
                }
        }
    }
Serial.println("SORTET --------------------->>>>>");
printTn();

Serial.print(tn[15]);
Serial.print(",");
Serial.print(tn[16]);
Serial.print(",");
Serial.print(tn[17]);

double med = ( 0.5*(tn[15] + tn[17]) + tn[16]) / 2;
Serial.print("med 3xGEW = ");
Serial.println(med, 4);
Serial.print("fs = ");
Serial.println(fs);
freq = 0.5*fs/med;
Serial.print("detected frequency = ");
Serial.println(freq, 6);


}

void Flank::calculate(int8_t * data){
   Serial.println(".calculate()");
  clearTn();
  printTn();
  findFlanks(data);
  findExtrema(data);
  findMedian(); 

  Serial.println("tn afer computation:");
  printTn();
 
}







void Flank::findFlanks(int8_t * v){
  /* suche nach wecheselnden flanken.
   * Schreibe die vergangenen Anzahl Bins n 
   * zwischen den gefundenen Flanken in die 
   * erste Hälfte des Arrays tn[].
  */

  ::printArray(v, "vdat:", 64);
  
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

  Serial.println();
  Serial.print("Direction = ");
  Serial.print(dir);
  Serial.print("\t v[i],v[i-1] = \t");
  Serial.print(v[i]);
  Serial.print(",");
  Serial.print(v[i-1]);
  Serial.print("\tCheck:\t");
  
    ++bincounter;
    if ( (dir == DIR_UP) && (v[i] > 0) && (v[i-1] <= 0) ){    // steigend durch Nullachse
        tn[k] = bincounter;
        ++k;
        bincounter = 0;        
        dir = DIR_DOWN;
        Serial.print("Case 1");
        
      } else if ( (dir == DIR_DOWN) && (v[i] <= 0) && (v[i-1] > 0) ){    // sinkend durch Nullachse
        tn[k] = bincounter;
        ++k;
        bincounter = 0;        
        dir = DIR_UP;
        Serial.print("Case 2");
      } else{
        Serial.print("None");
      }
  }    
 }







void Flank::findExtrema(int8_t * v){
  /* suche nach Peaks Min Max.
   * Schreibe die vergangenen Anzahl Bins n 
   * zwischen den gefundenen Peaks in die 
   * zweite Hälfte des Arrays tn[].
   *  LHYSTERESYS muss eingehalten werden
   * 
  */
  int k = LBUFFERSIZE/4;
  bool withinHysteresis = false;
  uint8_t dir = 0;      // Richtung undefiniert
  if (v[1] - v[0] > 0) {
    dir = DIR_UP;
  } else {
    dir = DIR_DOWN;
  }
 
Serial.print("\n\n******************** FIND EXTREMA *************");
// vektor absuchen nach peaks bis vektor fertig oder bis 16 peaks gefunden.
  uint16_t bincounter = 0;
  int8_t delta = 0;
  for (int i = 1; (i < LBUFFERSIZE) && (k < (LBUFFERSIZE / 2)); i++){
    ++bincounter;
    delta = v[i] - v[i-1];
   
    if (k>LBUFFERSIZE/4){                                                   // Falls schon mind. ein Peak gefunden wurde
        Serial.print("LastPeak v[tn[");
        Serial.print(k-1);
        Serial.print("]]=");
        Serial.print(v[tn[k-1]]);
        Serial.print("\t HIST=");
        Serial.print(LHYSTERESIS);
        Serial.print("\tv[i]=");
        Serial.println(v[i]);

      if ( dir == DIR_UP ){  
        if  (( v[tn[k-1]] + LHYSTERESIS < v[i] ) ){       // steigend hysterese verlassen  
          withinHysteresis = false;
          Serial.println("hyscheck Case 1");
        } 
        else {
          withinHysteresis = true;
          Serial.println("hyscheck Case 2");
        }
      } 
      else { // dir = down
        if  (( v[tn[k-1]] - LHYSTERESIS > v[i] ) ){      // sinkend hysterese verlassen  
          withinHysteresis = false;
          Serial.println("hyscheck Case 3");
        } else{
          withinHysteresis = true;
          Serial.println("hyscheck Case 4");
        }
      }
    }
    
  Serial.print("[k]=");
  Serial.print(k);
  Serial.print("\tDirection = ");
  Serial.print(dir);
  Serial.print("\t v[i],v[i-1], delta = \t");
  Serial.print(v[i]);
  Serial.print(",");
  Serial.print(v[i-1]);
  Serial.print(",");
  Serial.print(delta);
  Serial.print("\tCheck:\t");
  
    if ( (dir == DIR_UP) && (delta < 0) && (withinHysteresis == false)){    // wendepunkt oben gefunden
        tn[k] = bincounter;
        ++k;
        bincounter = 0;        
        dir = DIR_DOWN;
        Serial.print("Case 1\n");
        
      } else if ( (dir == DIR_DOWN) && (delta > 0) && (withinHysteresis == false)){    // wendepunkt unten gefunden
        tn[k] = bincounter;
        ++k;
        bincounter = 0;        
        dir = DIR_UP;
        Serial.print("Case 2\n");
      } else{
                Serial.print("Case none\n");
      }
  }    
  Serial.println();
 }





