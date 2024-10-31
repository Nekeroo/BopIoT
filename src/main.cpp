#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 17
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
    Serial.begin(115200);
    dht.begin();
}

void loop() {
    delay(3000);

    float h = dht.readHumidity();
    float t = dht.readTemperature();
    
    if (isnan(h) || isnan(t)) {
        Serial.println("Echec reception");
        return;
    }

    Serial.print("Humidite: ");
    Serial.print(h);
    Serial.println("%");
    Serial.print("Temperature: ");
    Serial.println(t);
    
}