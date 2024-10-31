#include <Arduino.h>
#include <WiFiManager.h>
#include <PubSubClient.h>

const char* mqtt_server = "broker.emqx.io";

WiFiClient espClient;
WiFiManager wm;
PubSubClient clientMqtt(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE	(50)
char msg[MSG_BUFFER_SIZE];
int value = 0;

void setup_wifi();
void callback(char* topic, byte* payload, unsigned int length);
void reconnect();
void sendMessage(long now);

void setup() {
  wm.resetSettings();
  Serial.begin(115200);
  setup_wifi();
  clientMqtt.setServer(mqtt_server, 1883);
  clientMqtt.setCallback(callback);
}

void loop() {

  if (WiFi.status() == WL_CONNECTED && !clientMqtt.connected()) {
    reconnect();
  }
  
  clientMqtt.loop();

  unsigned long now = millis();
  sendMessage(now);
}

void setup_wifi() {

  wm.autoConnect("BopIoTSpot", "securiteMax");

}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message reçu [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

}

void reconnect() {
  // Loop until we're reconnected
  while (!clientMqtt.connected()) {
    Serial.print("Connexion au broker MQTT ...");
    // Create a random client ID
    String clientId = "mqttx_";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (clientMqtt.connect(clientId.c_str())) {
      Serial.println("connecté");
      // Once connected, publish an announcement...
      clientMqtt.publish("test", "Client connecté : ", clientId);
      // ... and resubscribe
      clientMqtt.subscribe("test");
    } else {
      Serial.print("Echec, rc=");
      Serial.print(clientMqtt.state());
      Serial.println("Retry dans 5 secondes");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}


void sendMessage(long now) {
  if (now - lastMsg > 2000) {
    lastMsg = now;
    ++value;
    snprintf (msg, MSG_BUFFER_SIZE, "hello world #%ld", value);
    Serial.print("Message envoyé: ");
    Serial.println(msg);
    clientMqtt.publish("test", msg);
  }
}
