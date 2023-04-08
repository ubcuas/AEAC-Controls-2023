/*
*   LightPCB.h
*/
#ifndef LIGHTPCB_H
#define LIGHTPCB_H
#include "Arduino.h"

class LightPCB {
    private:
    uint8_t Pin;
    //HardwareSerial Serial;
    bool print;

    public:
    void Setup(uint8_t pin, bool debug);
    void ArmCabin();        //blinking
    void DisarmCabin();     //not blinking
};
#endif
