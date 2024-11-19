#include <Arduino.h>
#include "NetworkManager.h"

NetworkManager networkManager;

void setup() {
  Serial.begin(115200);
  networkManager.resetSettings();
  networkManager.initialize();
}

void loop() {
  networkManager.reconnectIfNeeded();
  
  // clientMqtt.loop();
}