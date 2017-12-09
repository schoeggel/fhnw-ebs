#include <Arduino.h>
#include "Lightsensor.h"

/* Sensor Vorverarbeitung
Die letzten n Werte werden in einem Array gespeichert, da die Datenauswertung den Wertverlauf über eine Zeit benötigt. Zuerst wird as Array um eine Stelle kopiert, so dass der älteste Wert durch den zweitältesten Wert überschrieben wird etc. Der Sensor wird gelesen und der gelesene Wert geglättet und als neuester Wert ins Array geschrieben. Die Glättung erfolgt, indem nur ein Tei der Differenz zwischen dem letzten gespeicherten Wert im Array und dem aktuell gemessenen Wert addiert wird zum zuletzt gespeicherten Wert.
data[0] : aktuellster Wert.
data[size-1]: ältester Wert. 
*/



Lightsensor::Lightsensor(){
	for (int  i = 0; i < LBUFFERSIZE; i++){
		data[i] = 127;
	}
}


void Lightsensor::update(){
	 static double precise_data0 = 127;   // wegen filterung, damit der wert nicht "hängen" bleiben kann. 
	 
	 shiftdata();				              // ein Sample schieben, damit Platz für neues
	 data[0] = (analogRead(5)>>2);         //  value read from analog pin 5 (max 1024) durch 4 teilen --> uint8_t
   
   int delta = data[0] - data[1];
   precise_data0 = precise_data0 + FILTER_K * delta;
   data[0] = precise_data0;
}


void Lightsensor::shiftdata(){
	// kopiert die daten um ein sample. das älteste Sample wird vom zweitältesten überschrieben etc.
	int i = LBUFFERSIZE -1;
  while (i > 0) { // i = 0 geht nicht mehr: data[0] = data[-1] :-(
		data[i] = data[i-1];
    --i;
	}		
}
