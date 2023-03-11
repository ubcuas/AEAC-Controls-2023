#include "DoorServo.h"

DoorServo Servo1(6, 1);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
   while (Serial.available() > 0) {
    // look for the next valid integer in the incoming serial stream:
    char mode = Serial.read();
    // look for the newline. That's the end of your sentence:
    if (Serial.read() == '\n') {}
    Serial.printf("Read This %c\n", mode);
    switch(mode){
      case '0':
        Servo1.close();
        break;
      case '1':
        Servo1.open();
        break;
      default:
        Serial.println("Input not Recognized");
    }
   }
}
