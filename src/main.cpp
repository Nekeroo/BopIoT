#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_Sensor.h>
#include "MicroManager.h"
    
// int digitalPin = 25;    
// int digitalVal;         
// volatile int clapCount = 0; 
// unsigned long lastClapTime = 0; 
// unsigned long currentClapTime = 0; 
// const unsigned long debounceTime = 200; 

// void IRAM_ATTR clapInterrupt() {
//   currentClapTime = millis();  
  
//   if (currentClapTime - lastClapTime > debounceTime) {
//     clapCount++;  
//     lastClapTime = currentClapTime;  
//   }
// }

// void setup() {
//   pinMode(digitalPin, INPUT);  
//   Serial.begin(115200);         
  
//   attachInterrupt(digitalPin, clapInterrupt, RISING);  
// }

// void loop() {
  
//   if (clapCount == 2) {
//     Serial.println("DOUBLE CLAP");  
//     clapCount = 0;
//   }

//   if (millis() - lastClapTime > 500) {
//     clapCount = 0;  
//   }
// }



MicroManager microManager;
bool isClaped = false;

void IRAM_ATTR clapedInterrupt() {
  isClaped = true;
}

void setup() {
  Serial.begin(115200);
  //networkManager.initialize();
  microManager.initialize();
  pinMode(microManager.micPin, INPUT_PULLUP);  
  attachInterrupt(microManager.micPin, clapedInterrupt, RISING);  

}

void loop() {
  //networkManager.reconnectIfNeeded();
  // clientMqtt.loop();
  if (isClaped){
    isClaped = false;
    long currentClapTime = millis();  
  
    if (currentClapTime - microManager.lastClapTime > microManager.debounceTime) {
      microManager.clapCount++;
      microManager.lastClapTime = currentClapTime;  
    }
  }
  microManager.microUpdate();
}
