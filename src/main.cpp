#include <Arduino.h>
#include "NetworkManager.h"
#include "JoystickManager.h"

JoystickManager joystickManager;
NetworkManager networkManager;

void IRAM_ATTR pressedInterrupt() {
  joystickManager.currentActionTime = millis();  
  
  if (joystickManager.currentActionTime -joystickManager.lastActionTime > joystickManager.debounceTime) {
    joystickManager.buttonPressed = true;
  }
}

void setup() {
  Serial.begin(115200);
  //networkManager.initialize();
  joystickManager.initialize();
  attachInterrupt(digitalPinToInterrupt(joystickManager.buttonPin), pressedInterrupt, FALLING);  

}

void loop() {
  //networkManager.reconnectIfNeeded();
  // clientMqtt.loop();

  JoystickState state = joystickManager.getStateUpdated();

  if (state != NONE) {
    Serial.println(state);
  }
  delay(500);
}