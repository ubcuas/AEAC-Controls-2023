
/*
*   DoorServo.h
*
*/
#ifndef DOORSERVO_H
#define DOORSERVO_H
#include "HardwareSerial.h"
#include "Arduino.h"

class DoorServo {
    private:
    uint16_t OpenPos = 180;
    uint16_t ClosePos = 380;
    uint8_t Servopin;
    uint8_t Delay = 5;
    uint16_t Frequency;
    //HardwareSerial Serial;
    bool print;

    public:
    DoorServo(uint8_t pin, bool debug, uint16_t Freq);
    void open();
    void close();
    void turnOff();
};
#endif
