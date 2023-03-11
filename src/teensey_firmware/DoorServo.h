
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
    uint16_t OpenPos = 400;
    uint16_t ClosePos = 150;
    uint8_t Servopin;
    //HardwareSerial Serial;
    bool print;

    public:
    DoorServo(uint8_t pin, bool debug);
    void open();
    void close();
};
#endif
