//
// Created by Gaetan Salvi on 19/11/2024.
//

#ifndef JOYSTICKMANAGER_H
#define JOYSTICKMANAGER_H

#include <Arduino.h>

enum JoystickState {
    NONE = 9,
    LEFT = 5,
    RIGHT = 4,
    TOP = 6,
    BOTTOM = 7,
    BUTTON_PRESSED = 0
  };

class JoystickManager {
    const int xPin = 34;
    const int yPin = 35;

    int centerX = 0;
    int centerY = 0;
    int thresholdX = 0;
    int thresholdY = 0;

public:

    static const int buttonPin = 26;

    int digitalVal;         
    unsigned long lastActionTime = 0; 
    unsigned long currentActionTime = 0; 
    const unsigned long debounceTime = 200; 
    volatile bool buttonPressed = false;
    /**
    * Initialize and sync joysticks
    */
    void initialize();
    /**
    * get current joystick direction
    * @return some of RIGHT, LEFT, TOP, BOTTOM or NONE values
    */
    JoystickState getStateUpdated();

    // void IRAM_ATTR pressedInterrupt();
};



#endif //JOYSTICKMANAGER_H
