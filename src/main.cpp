#include <Arduino.h>
#include "NetworkManager.h"
#include "JoystickManager.h"

JoystickManager joystickManager;
NetworkManager networkManager;
boolean shouldRespond;
void IRAM_ATTR pressedInterrupt() {
  joystickManager.currentActionTime = millis();  
  
  Serial.println("Interrupt");

  if (joystickManager.currentActionTime -joystickManager.lastActionTime > joystickManager.debounceTime) {
    joystickManager.buttonPressed = true;
  }

  Serial.println("Interrupt 2");
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
    Serial.println("shouldRespond");
    state = joystickManager.getStateUpdated();
  }

  if (state != NONE) {
    Serial.print("state :");
    Serial.println(state);
    networkManager.sendMqttMessage(::RESPONSE, state);
    state = NONE;
    networkManager.shouldRespond = false;
  }
}