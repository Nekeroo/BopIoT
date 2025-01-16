#include <Arduino.h>
#include "NetworkManager.h"
#include "JoystickManager.h"
#include "AccelerometreManager.h"
#include "MicroManager.h"

JoystickManager joystickManager;
NetworkManager networkManager;
MicroManager micromanager;
AccelerometreManager accelerometreManager
boolean shouldRespond;
bool isClaped = false;
void IRAM_ATTR pressedInterrupt() {
  joystickManager.currentActionTime = millis();  
  
  if (joystickManager.currentActionTime -joystickManager.lastActionTime > joystickManager.debounceTime) {
    joystickManager.buttonPressed = true;
  }
}

void IRAM_ATTR clapedInterrupt() {
  isClaped = true;
}

void setup() {
  Serial.begin(115200);
  networkManager.initialize();
  joystickManager.initialize();
  micromanager.initialize();
  accelerometreManager.initialize();
  attachInterrupt(digitalPinToInterrupt(joystickManager.buttonPin), pressedInterrupt, FALLING);  
  attachInterrupt(microManager.micPin, clapedInterrupt, RISING);  
}

void loop() {
  JoystickState joystickState = NONE;
  AccelerometreState acceleroState = NONE;
  networkManager.reconnectIfNeeded();
  if (networkManager.shouldRespond) {
    joystickState = joystickManager.getStateUpdated();
    acceleroState = accelerometreManager.getStateUpdated();
    microManager.microUpdate();
    networkManager.shouldRespond = false;
  }

  if (joystickState != NONE) {
    networkManager.sendMqttMessage(::RESPONSE, joystickState);
    joystickState = NONE;
  }

  if (acceleroState != NONE) {
    networkManager.sendMqttMessage(::RESPONSE, acceleroState);
    acceleroState = NONE;
  }

  if (isClaped){
    isClaped = false;
    long currentClapTime = millis();  
  
    if (currentClapTime - microManager.lastClapTime > microManager.debounceTime) {
      microManager.clapCount++;
      microManager.lastClapTime = currentClapTime;  
    }
    
  }

  if (microManager.clapDetected == true) {
      networkManager.sendMqttMessage(::RESPONSE, 3);
      microManager.clapDetected = false;
  }


  delay(500);
}