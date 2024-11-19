//
// Created by Gaetan Salvi on 19/11/2024.
//

#include "JoystickManager.h"
#include <Arduino.h>

void JoystickManager::initialize() {
    pinMode(xPin, INPUT);
    pinMode(yPin, INPUT);
    pinMode(buttonPin, INPUT);

    // Calibration automatique
    centerX = analogRead(xPin);
    centerY = analogRead(yPin);
    thresholdX = analogRead(xPin) / 2;
    thresholdY = analogRead(yPin) / 2;


    Serial.print("Valeur neutre X: ");
    Serial.print(centerX);
    Serial.print("    |    Valeur neutre Y: ");
    Serial.println(centerY);
}

JoystickState JoystickManager::getStateUpdated() {
    int xValue = analogRead(xPin);
    int yValue = analogRead(yPin);
    int buttonValue = analogRead(buttonPin);

    if (xValue < centerX - thresholdX) {
        Serial.print("Left!");
        return LEFT;
    } else if (xValue > centerX + thresholdX) {
        Serial.print("Right!");
        return RIGHT;
    }else if (yValue < centerY - thresholdY) {
        Serial.print("Bottom!");
        return BOTTOM;
    } else if (yValue > centerY + thresholdY) {
        Serial.print("Top!");
        return TOP;
    } else if(buttonValue == LOW) {
        Serial.print("Button pressed!");
        return BUTTON_PRESSED;
    } else {
        return NONE;
    }
}