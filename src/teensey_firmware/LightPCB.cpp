#include "LightPCB.h"

void LightPCB::Setup(uint8_t pin, bool debug){
    Pin = pin;
    print = debug;
    pinMode(Pin, OUTPUT);
    if(print){
        Serial.println("LightPCB Setup Done!");
    }
}

void LightPCB::ArmCabin(){
    digitalWrite(Pin, HIGH);
    if(print){
        Serial.println("Cabin Armed");
    }
}

void LightPCB::DisarmCabin(){
    digitalWrite(Pin, LOW);
    if(print){
        Serial.println("Cabin Disarmed");
    }
}