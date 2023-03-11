#include "HardwareSerial.h"
#include "Stream.h"
#include "rail_servo.h"

RailServo::RailServo(uint8_t pin, bool debug){
    servo_pin = pin;
    print = debug;
    //Serial = serialport;
    pinMode(servo_pin, OUTPUT);
    analogWriteFrequency(servo_pin, FREQUENCY); 
    analogWriteResolution(8);
    if(print){
        Serial.println("Rail Servo Setup Done!");
    }
}

void RailServo::open(){
    analogWrite(servo_pin, open_pos);
    if(print){
        Serial.println("Rail Opened");
    }
}

void RailServo::close(){
    analogWrite(servo_pin, close_pos);
    if(print){
        Serial.println("Rail Closed");
    }
}