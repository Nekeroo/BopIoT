#include <Arduino.h>
#include "NetworkManager.h"
#include "JoystickManager.h"

JoystickManager joystickManager;
NetworkManager networkManager;
boolean shouldRespond;
void IRAM_ATTR pressedInterrupt() {
  joystickManager.currentActionTime = millis();  
  
  if (joystickManager.currentActionTime -joystickManager.lastActionTime > joystickManager.debounceTime) {
    joystickManager.buttonPressed = true;
  }
}

void setup() {
  Serial.begin(115200);
  networkManager.initialize();
  joystickManager.initialize();
  attachInterrupt(digitalPinToInterrupt(joystickManager.buttonPin), pressedInterrupt, FALLING);  

}

void loop() {
  JoystickState state = NONE;
  networkManager.reconnectIfNeeded();
  if (networkManager.shouldRespond) {
    state = joystickManager.getStateUpdated();
    networkManager.shouldRespond = false;
  }

  if (state != NONE) {
    networkManager.sendMqttMessage(::RESPONSE, state);
    state = NONE;
  }
  delay(500);
}