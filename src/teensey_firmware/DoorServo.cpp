#include "HardwareSerial.h"
#include "Stream.h"
#include "DoorServo.h"

DoorServo::DoorServo(uint8_t pin, bool debug, uint16_t Freq){
    Servopin = pin;
    print = debug;
    Frequency = Freq;
    //Serial = serialport;
    pinMode(Servopin, OUTPUT);
    analogWriteFrequency(Servopin, Frequency); 
    analogWriteResolution(12);
    if(print){
        Serial.println("Servo Setup Done!");
    }
}

void DoorServo::open(){
    for(int i = ClosePos; i >= OpenPos; i--){
    analogWrite(Servopin, i);
    delay(Delay);
  }
    //analogWrite(Servopin, OpenPos);
    if(print){
        Serial.println("Servo Opened");
    }
}

void DoorServo::close(){
  for(int i = OpenPos; i <= ClosePos; i++){
    analogWrite(Servopin, i);
    delay(Delay);
  }
    //analogWrite(Servopin, ClosePos);
    if(print){
        Serial.println("Servo Closed");
    }
}

void DoorServo::turnOff(){
    analogWrite(Servopin, 0);
    if(print){
        Serial.println("Servo Turned OFF");
    }
}

void DoorServo::updateParams(uint16_t open, uint16_t close){
    OpenPos = open;
    ClosePos = close;
}