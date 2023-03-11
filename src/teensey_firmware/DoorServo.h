
/*
*   DoorServo.h
*
*/
#ifndef DOORSERVO_H
#define DOORSERVO_H
#include "HardwareSerial.h"
#include "Arduino.h"

#define FREQUENCY 50


class DoorServo {
    private:
    uint16_t OpenPos = 180;
    uint16_t ClosePos = 380;
    uint8_t Servopin;
    uint8_t Delay = 5;
    //HardwareSerial Serial;
    bool print;

    public:
    DoorServo(uint8_t pin, bool debug);
    void open();
    void close();
};
#endif
