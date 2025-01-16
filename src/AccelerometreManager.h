#ifndef ACCELEROMETREMANAGER_H
#define ACCELEROMETREMANAGER_H

enum AccelerometreState {
    LEFT = 1,
    RIGHT = 2,
    NONE = 0
};

class AccelerometreManager {
    public : 


        Adafruit_MMA8451 mma = Adafruit_MMA8451();

        void initialize();

        AccelerometreState getStateUpdated();

};

#endif 