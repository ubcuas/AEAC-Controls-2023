#include "HardwareSerial.h"
#include "Stream.h"
#include "DoorServo.h"
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