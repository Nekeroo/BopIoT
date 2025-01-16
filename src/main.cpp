#include <Arduino.h>
#include "NetworkManager.h"
#include "JoystickManager.h"

JoystickManager joystickManager;
NetworkManager networkManager;
MicroManager micromanager;
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
  attachInterrupt(digitalPinToInterrupt(joystickManager.buttonPin), pressedInterrupt, FALLING);  
  attachInterrupt(microManager.micPin, clapedInterrupt, RISING);  
}

void loop() {
  JoystickState state = NONE;
  networkManager.reconnectIfNeeded();
  if (networkManager.shouldRespond) {
    state = joystickManager.getStateUpdated();
    microManager.microUpdate();
    networkManager.shouldRespond = false;
  }

  if (state != NONE) {
    networkManager.sendMqttMessage(::RESPONSE, state);
    state = NONE;
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