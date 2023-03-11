
#ifndef RAILSERVO_H
#define RAILSERVO_H
#include "HardwareSerial.h"
#include "Arduino.h"

#define FREQUENCY 300


class RailServo {
    private:
    uint16_t open_pos = 75;
    uint16_t mid_pos = 100;
    uint16_t close_pos = 115;
    uint8_t servo_pin;
    //HardwareSerial Serial;
    bool print;

    public:
    RailServo(uint8_t pin, bool debug);
    void open();
    void close();
    void mid();
};
#endif
