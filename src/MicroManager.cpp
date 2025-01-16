#include "MicroManager.h"
#include <Arduino.h>


// Initialization function
void MicroManager::initialize() {
    pinMode(micPin, INPUT);
}

void MicroManager::microUpdate(){
  if (clapCount==2) {
    Serial.println("DOUBLE CLAP");  
    clapCount = 0;
  } 
  if (millis() - lastClapTime > 500) {
    clapCount = 0;
  }
}