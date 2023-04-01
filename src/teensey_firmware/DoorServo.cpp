#include "HardwareSerial.h"
#include "Stream.h"
#include "DoorServo.h"

DoorServo::DoorServo(uint8_t pin, bool debug, uint16_t Freq){
    Servopin = pin;
    print = debug;
    Frequency = Freq;
    state = 0;
    //Serial = serialport;
    pinMode(Servopin, OUTPUT);
    analogWriteFrequency(Servopin, Frequency); 
    analogWriteResolution(12);
    if(print){
        Serial.println("Servo Setup Done!");
    }
}

void DoorServo::open(){
    if(state != 1){
      state = 1;
      if(ClosePos > OpenPos){
        for(int i = ClosePos; i >= OpenPos; i--){
        analogWrite(Servopin, i);
        //Serial.printf("pos: %d\n", i);
        delay(Delay);
        }
      }
      else{
        for(int i = ClosePos; i <= OpenPos; i++){
        analogWrite(Servopin, i);
        //Serial.printf("pos: %d\n", i);
        delay(Delay);
        }  
      }
      //analogWrite(Servopin, OpenPos);
      if(print){
          Serial.println("Servo Opened");

      }
    }
}

void DoorServo::close(){
  if(state != 2){
    state = 2;
    if(OpenPos < ClosePos){
        for(int i = OpenPos; i <= ClosePos; i++){
        analogWrite(Servopin, i);
        //Serial.printf("pos: %d\n", i);
        delay(Delay);
        }
      }
    else{
        for(int i = OpenPos; i >= ClosePos; i--){
        analogWrite(Servopin, i);
        //Serial.printf("pos: %d\n", i);
        delay(Delay);
        }  
      }
      //analogWrite(Servopin, ClosePos);
      if(print){
          Serial.println("Servo Closed");
      }
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