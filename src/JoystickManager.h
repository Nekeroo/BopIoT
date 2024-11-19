//
// Created by Gaetan Salvi on 19/11/2024.
//

#ifndef JOYSTICKMANAGER_H
#define JOYSTICKMANAGER_H

enum JoystickState {
    NONE,
    LEFT,
    RIGHT,
    TOP,
    BOTTOM,
    BUTTON_PRESSED
  };

class JoystickManager {
    const int xPin = 34;
    const int yPin = 35;
    const int buttonPin = 25;

    int centerX = 0;
    int centerY = 0;
    int thresholdX = 0;
    int thresholdY = 0;

public:
    /**
    * Initialize and sync joysticks
    */
    void initialize();
    /**
    * get current joystick direction
    * @return some of RIGHT, LEFT, TOP, BOTTOM or NONE values
    */
    JoystickState getStateUpdated();
};



#endif //JOYSTICKMANAGER_H
