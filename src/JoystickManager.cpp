#include "JoystickManager.h"
#include <Arduino.h>

// Ensure buttonPressed is volatile for use in ISR
volatile bool buttonPressed = false;

// Initialization function
void JoystickManager::initialize() {
    pinMode(xPin, INPUT);
    pinMode(yPin, INPUT);
    pinMode(buttonPin, INPUT_PULLUP);

    // Calibration for neutral position
    centerX = analogRead(xPin);
    centerY = analogRead(yPin);

    // Set a fixed threshold for joystick movement
    thresholdX = 100; // Example value
    thresholdY = 100;

    // Debugging output
    Serial.print("Neutral X: ");
    Serial.print(centerX);
    Serial.print(" | Neutral Y: ");
    Serial.println(centerY);
}


// Function to get updated joystick state
JoystickState JoystickManager::getStateUpdated() {
    // Read joystick and button values
    int xValue = analogRead(xPin);
    int yValue = analogRead(yPin);

    if (buttonPressed) {
        buttonPressed = false;
        Serial.println("Button Pressed!");
        return BUTTON_PRESSED;
    }

    if (xValue > centerX + thresholdX) {
        Serial.println("Right!");
        return RIGHT;
    } else if (xValue < centerX - thresholdX) {
        Serial.println("Left!");
        return LEFT;
    } else if (yValue > centerY + thresholdY) {
        Serial.println("Top!");
        return TOP;
    } else if (yValue < centerY - thresholdY) {
        Serial.println("Bottom!");
        return BOTTOM;
    }

    return NONE;
}
