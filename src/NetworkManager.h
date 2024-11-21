//
// Created by Gaetan Salvi on 19/11/2024.
//
#include <WiFiManager.h>
#include <PubSubClient.h>

#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#define MQTT_MSG_BUFFER_SIZE (50)


enum MessageType {
  ERROR,
  ACTION,
  RESPONSE
};

class NetworkManager {
  const char* mqtt_server = "broker.emqx.io";
  const char* name = "BopIoT-953";
  WiFiClient espClient;
  WiFiManager wm;
  PubSubClient clientMqtt;
  
  void setup_wifi();
  static void callback(char* topic, byte* payload, unsigned int length);


public:
  static boolean shouldRespond;
  NetworkManager(): clientMqtt(espClient) {};
  void initialize();
  void reconnectIfNeeded();
  void sendMqttMessage(int type, int actionId);
  void resetSettings();
};



#endif //NETWORKMANAGER_H
