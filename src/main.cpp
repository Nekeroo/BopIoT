#include <Arduino.h>
#include "NetworkManager.h"
#include "JoystickManager.h"

JoystickManager joystickManager;
NetworkManager networkManager;

void setup() {
  Serial.begin(115200);
  //networkManager.initialize();
  joystickManager.initialize();
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