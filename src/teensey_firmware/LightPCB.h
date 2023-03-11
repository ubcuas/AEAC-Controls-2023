/*
*   LightPCB.h
*/
#ifndef LIGHTPCB_H
#define LIGHTPCB_H
#include "Arduino.h"

#define FREQUENCY 50


class LightPCB {
    private:
    uint8_t Pin;
    //HardwareSerial Serial;
    bool print;

    public:
    DoorServo(uint8_t pin, bool debug);
    void ArmCabin();        //blinking
    void DisarmCabin();     //not blinking
};
#endif
