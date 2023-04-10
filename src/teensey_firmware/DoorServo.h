
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
    uint16_t OpenPos;
    uint16_t ClosePos;
    uint8_t Servopin;
    uint8_t Delay;
    uint16_t Frequency;
    uint8_t state;
    //HardwareSerial Serial;
    bool print;

    public:
    DoorServo(uint8_t pin, bool debug, uint16_t Freq, uint16_t open, uint16_t close, uint16_t delay_time);
    void open();
    void close();
    void turnOff();
    void updateParams(uint16_t open, uint16_t close, uint16_t delay_time);
};
#endif
