#include <Arduino.h>
#include <WiFiManager.h>
#include <PubSubClient.h>

const char* mqtt_server = "broker.emqx.io";

WiFiClient espClient;
WiFiManager wm;
PubSubClient clientMqtt(espClient);
unsigned long lastMsg = 0;
bool shouldRespond = false; // Flag pour indiquer si une commande a été reçue
#define MSG_BUFFER_SIZE (50)
char msg[MSG_BUFFER_SIZE];

void setup_wifi();
void callback(char* topic, byte* payload, unsigned int length);
void reconnect();
void sendMessage();

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

  if (shouldRespond) {
    sendMessage();
    shouldRespond = false; // Après avoir envoyé un message, on attend une nouvelle commande
  }
}

void setup_wifi() {
  wm.autoConnect("BopIoTSpot", "securiteMax");
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message reçu [");
  Serial.print(topic);
  Serial.print("] ");
  
  String message = "";
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  Serial.println(message);

  // Vérification si le message contient "command"
  if (message.indexOf("request") != -1) {
    Serial.println("Commande détectée !");
    shouldRespond = true; // Active le flag pour envoyer une réponse
  }
}

void reconnect() {
  // Tentative de reconnexion
  while (!clientMqtt.connected()) {
    Serial.print("Connexion au broker MQTT ...");
    String clientId = "mqttx_";
    clientId += String(random(0xffff), HEX);
    if (clientMqtt.connect(clientId.c_str())) {
      Serial.println("connecté");
      // Publication d'un message pour notifier la connexion
      clientMqtt.publish("bopiotexchange", "Client connecté");
      // S'abonner au topic
      clientMqtt.subscribe("bopiotexchange");
    } else {
      Serial.print("Echec, rc=");
      Serial.print(clientMqtt.state());
      Serial.println("Retry dans 5 secondes");
      delay(5000);
    }
  }
}

void sendMessage() {
  snprintf(msg, MSG_BUFFER_SIZE, "{\"message\": \"%s\"}", "Commande traitée");
  Serial.print("Message envoyé: ");
  Serial.println(msg);
  clientMqtt.publish("bopiotexchange", msg);
}
