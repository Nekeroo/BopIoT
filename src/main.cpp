#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h>

Adafruit_MMA8451 mma = Adafruit_MMA8451();
float biaisX, biaisY, biaisZ, accelX, accelY, accelZ;

void calibrerMMA8451() {
  float sommeX = 0, sommeY = 0, sommeZ = 0, sommeAccelX = 0, sommeAccelY = 0, sommeAccelZ = 0;
  const int numMesures = 100;
  
  for (int i = 0; i < numMesures; i++) {
    mma.read();
    sensors_event_t event; 
    mma.getEvent(&event);
    sommeX += mma.x;
    sommeY += mma.y;
    sommeZ += mma.z;
    sommeAccelX += event.acceleration.x;
    sommeAccelY += event.acceleration.y;
    sommeAccelZ += event.acceleration.z;
    delay(10);
}
 biaisX = sommeX / numMesures;
  biaisY = sommeY / numMesures;
  biaisZ = sommeZ / numMesures;
  accelX = sommeAccelX / numMesures;
    accelY = sommeAccelY / numMesures;
  accelZ = sommeAccelZ / numMesures;


  Serial.println("Calibration terminée !");
  Serial.print("Biais X: "); Serial.println(biaisX);
  Serial.print("Biais Y: "); Serial.println(biaisY);
  Serial.print("Biais Z: "); Serial.println(biaisZ);
    Serial.print("Accel X: "); Serial.println(accelX);

  Serial.print("Accel Y: "); Serial.println(accelY);

  Serial.print("Accel Z: "); Serial.println(accelZ);

}

void setup() {
    Serial.begin(115200);
    if (! mma.begin()) {
        Serial.println("Couldnt start");
        while (1);
    }
    Serial.println("MMA8451 found!");
    mma.setRange(MMA8451_RANGE_2_G);
    calibrerMMA8451();

}

void loop() {

    mma.read();

    delay(2000);

    uint8_t o = mma.getOrientation();
    

    float accX = mma.x - biaisX;
    float accY = mma.y - biaisY;
    float accZ = mma.z - biaisZ;


    Serial.print("X: "); Serial.print(accX);
    Serial.print(" Y: "); Serial.print(accY);
    Serial.print(" Z: "); Serial.println(accZ);

    sensors_event_t event; 
    mma.getEvent(&event);

    float resultX = event.acceleration.x - accelX;
    float resultY = event.acceleration.y - accelY;
    float resultZ = event.acceleration.z - accelZ;

     Serial.print("aacel X: "); Serial.print(resultX);
    Serial.print("accel Y: "); Serial.print(resultY);
    Serial.print("accel Z: "); Serial.println(resultZ);
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