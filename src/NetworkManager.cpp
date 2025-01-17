//
// Created by Gaetan Salvi on 19/11/2024.
//

#include "NetworkManager.h"

boolean NetworkManager::shouldRespond = false;

void NetworkManager::initialize() {
    setup_wifi();
    clientMqtt.setServer(mqtt_server, 1883);
    clientMqtt.setCallback(callback);
}

void NetworkManager::loopClientMqtt() {
    clientMqtt.loop();
}

void NetworkManager::setup_wifi() {
    wm.autoConnect(name, "securiteMax");
}

void NetworkManager::callback(char* topic, byte* payload, unsigned int length) {
    
    String message = "";
    for (int i = 0; i < length; i++) {
        message += (char)payload[i];
    }

    Serial.print("message : ");
    Serial.println(message);
    if (message.indexOf("\"type\":1") != -1) {
        Serial.println("OK shouldRespond");
        shouldRespond = true;
    }
}

void NetworkManager::reconnectIfNeeded() {
    clientMqtt.loop();

    if (WiFi.status() == WL_CONNECTED && !clientMqtt.connected()) {
        // Tentative de reconnexion
        while (!clientMqtt.connected()) {
            String clientId = "mqttx_";
            clientId += String(random(0xffff), HEX);
            if (clientMqtt.connect(clientId.c_str())) {
                // Publication d'un message pour notifier la connexion
                clientMqtt.publish(name, "Client connecté");
                // S'abonner au topic
                clientMqtt.subscribe(name);
            } else {
                delay(5000);
            }
        }
    }
}

void NetworkManager::sendMqttMessage(int type, int actionId) {
    char message[MQTT_MSG_BUFFER_SIZE];
    snprintf(
        message,
        MQTT_MSG_BUFFER_SIZE,
        "{\"type\": %d, \"action\": { \"id\": %d }}",
        type,
        actionId
    );
    clientMqtt.publish(name, message);
}

void NetworkManager::resetSettings() {
  wm.resetSettings();
}