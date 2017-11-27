// (C) joel koch 2017
// jobcontroller kontrolliert verschiedene jobs.
// die jobs können zeiltich in einem ablaufraster (bitmaske) mit divider konfiguriert werden
// die eigentliche auszuführende funktion wird über einen funciton pointer übergeben (TODO!)
// der JobController besitzt eine check-methode, die zyklisch aufgerufen werden muss.
// aufrufintervall der check() methode zusammen mit den bitmasken und dividern ergeben die 
// effektive job-aufruf-intervalle. Ein neuer Controller ist immer inaktiv. Neue Jobs immer aktiv.
// Wenn alle Jobs initialisiert sind, muss der Kontroller aktiviert werden mit .enable(); und danach
// über einen TimerInterrupt zyklisch aufgerufen werden über die .check() methode.


#include "JobController.h"

JobController scheduler;

void setup() {
  // Jobs initialisieren: jobnr, cycleConfigPattern, Divider, dummie):
// jobs sind nach init() automatisch aktiv, scheduler läuft aber noch nicht.
scheduler.init(0, 0b1111111111111111, 1, 0);
scheduler.init(1, 0b0000000000000001, 12, 99);
scheduler.init(2, 0b0001000100010001, 2, 32);
scheduler.enable();
}

void loop() {
  // put your main code here, to run repeatedly:
scheduler.check();
}