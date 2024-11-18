#include <Arduino.h>

int mic_pin = 34;       
int digitalPin = 25;    
int digitalVal;         
volatile int clapCount = 0; 
unsigned long lastClapTime = 0; 
unsigned long currentClapTime = 0; 
const unsigned long debounceTime = 200; 

void IRAM_ATTR clapInterrupt() {
  currentClapTime = millis();  
  
  if (currentClapTime - lastClapTime > debounceTime) {
    clapCount++;  
    lastClapTime = currentClapTime;  
  }
}

void setup() {
  pinMode(digitalPin, INPUT);  
  Serial.begin(115200);         
  
  attachInterrupt(digitalPin, clapInterrupt, RISING);  
}

void loop() {
  
  if (clapCount == 2) {
    Serial.println("DOUBLE CLAP");  
    clapCount = 0;
  }

  if (millis() - lastClapTime > 500) {
    clapCount = 0;  
  }
}
