#include "LightPCB.h"
DoorServo::DoorServo(uint8_t pin, bool debug){
    Servopin = pin;
    print = debug;
    //Serial = serialport;
    pinMode(Servopin, OUTPUT);
    analogWriteFrequency(Servopin, FREQUENCY); 
    analogWriteResolution(12);
    if(print){
        Serial.println("Servo Setup Done!");
    }
}

void DoorServo::open(){
    analogWrite(Servopin, OpenPos);
    if(print){
        Serial.println("Servo Opened");
    }
}

void DoorServo::close(){
    analogWrite(Servopin, ClosePos);
    if(print){
        Serial.println("Servo Closed");
    }
}