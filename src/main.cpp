#include <Arduino.h>
#include "NetworkManager.h"

NetworkManager networkManager;

void setup() {
  wm.resetSettings();
  Serial.begin(115200);
  networkManager.initialize();
}

void loop() {
  networkManager.reconnectIfNeeded();
  
  // clientMqtt.loop();
}