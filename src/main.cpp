#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h>

Adafruit_MMA8451 mma = Adafruit_MMA8451();
float accelZ;

void setup() {
    Serial.begin(115200);
    if (! mma.begin()) {
        Serial.println("Couldnt start");
        while (1);
    }
    Serial.println("MMA8451 found!");
    sensors_event_t event; 
    mma.getEvent(&event);
    accelZ = event.acceleration.z;
}

void loop() {

    mma.read();

    delay(2000);

    sensors_event_t event; 
    mma.getEvent(&event);
    if ((event.acceleration.z > accelZ + 1) || (event.acceleration.z < accelZ - 1)) {
        Serial.println("IT MOVES");
    }

    uint8_t o = mma.getOrientation();
  
    switch (o) {
        case MMA8451_PL_PUF: 
        Serial.println("Portrait Up Front");
        break;
        case MMA8451_PL_LRF: 
        Serial.println("Landscape Right Front");
        break;
        case MMA8451_PL_LLF: 
        Serial.println("Landscape Left Front");
        break;
        }
    Serial.println();
    delay(500);
    
}