#ifndef MICROMANAGER_H
#define MICROMANAGER_H

class MicroManager {
    public :
        /**
        * Initialize Micro
        */
        void initialize();

        void microUpdate();

        int micPin = 25;      
        bool clapDetected = false;    
        volatile int clapCount = 0; 
        unsigned long lastClapTime = 0;
        const unsigned long debounceTime = 200;

};

#endif // MICROMANAGER_H