#ifndef ACCELEROMETREMANAGER_H
#define ACCELEROMETREMANAGER_H

#include <Adafruit_MMA8451.h>

enum AccelerometreState {
    NONE_ACCELERO = 0,
    LEFT_ACCELERO = 1,
    RIGHT_ACCELERO = 2
};

class AccelerometreManager {
    public : 


        Adafruit_MMA8451 mma;
        void initialize();

        AccelerometreState getStateUpdated();

};

#endif 