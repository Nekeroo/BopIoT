#ifndef MICROMANAGER_H
#define MICROMANAGER_H

class MicroManager {
    public :
        /**
        * Initialize Micro
        */
        void initialize();

        bool microClapDetect();

        int micPin = 25;          
        volatile int clapCount = 0; 
        unsigned long lastClapTime = 0; 
        unsigned long currentClapTime = 0; 
        const unsigned long debounceTime = 200; 
        volatile bool microClap = false;

};

#endif // MICROMANAGER_H