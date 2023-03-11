
#ifndef RAILSERVO_H
#define RAILSERVO_H
#include "HardwareSerial.h"
#include "Arduino.h"

#define FREQUENCY 300


class RailServo {
    private:
    uint16_t open_pos = 80;
    uint16_t close_pos = 155;
    uint8_t servo_pin;
    //HardwareSerial Serial;
    bool print;

    public:
    RailServo(uint8_t pin, bool debug);
    void open();
    void close();
};
#endif
