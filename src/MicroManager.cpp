#include "MicroManager.h"
#include <Arduino.h>


// Initialization function
void MicroManager::initialize() {
    pinMode(micPin, INPUT);
    calibrerMMA8451();
}

void MicroManager::microUpdate(){
  if (clapCount==2) {
    Serial.println("DOUBLE CLAP");  
    clapDetected = true;
    clapCount = 0;
  } 
  if (millis() - lastClapTime > 500) {
    clapCount = 0;
  }
}

void calibrerMMA8451() {
  float sommeX = 0, sommeY = 0, sommeZ = 0, sommeAccelX = 0, sommeAccelY = 0, sommeAccelZ = 0;
  const int numMesures = 100;
  
  for (int i = 0; i < numMesures; i++) {
    mma.read();
    sensors_event_t event; 
    mma.getEvent(&event);
    sommeX += mma.x;
    sommeY += mma.y;
    sommeZ += mma.z;
    sommeAccelX += event.acceleration.x;
    sommeAccelY += event.acceleration.y;
    sommeAccelZ += event.acceleration.z;
    delay(10);
}
 biaisX = sommeX / numMesures;
  biaisY = sommeY / numMesures;
  biaisZ = sommeZ / numMesures;
  accelX = sommeAccelX / numMesures;
    accelY = sommeAccelY / numMesures;
  accelZ = sommeAccelZ / numMesures;


  Serial.println("Calibration terminée !");
  Serial.print("Biais X: "); Serial.println(biaisX);
  Serial.print("Biais Y: "); Serial.println(biaisY);
  Serial.print("Biais Z: "); Serial.println(biaisZ);
    Serial.print("Accel X: "); Serial.println(accelX);

  Serial.print("Accel Y: "); Serial.println(accelY);

  Serial.print("Accel Z: "); Serial.println(accelZ);

}