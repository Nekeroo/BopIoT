#include "MicroManager.h"
#include <Arduino.h>

// Ensure microEnabled is volatile for use in ISR
volatile bool microEnabled = false;

// Initialization function
void MicroManager::initialize() {
    pinMode(micPin, INPUT);
}

bool MicroManager::microClapDetect(){
  if (microClap) {
    Serial.println("DOUBLE CLAP");  
    clapCount = 0;
    microClap = false;
    return true;
  }

  if (millis() - lastClapTime > 500) {
    clapCount = 0;  
  }
  return false;
}