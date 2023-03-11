#include <Servo.h>
#include "rail_servo.h"

RailServo rail(6, 0);
Servo servo;  // create servo object to control a servo

int pos = 0;    // variable to store the servo position

void setup() {
  servo.attach(9);  // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);
}

void loop() {

  /*
  rfd 900x config code

  for (pos = 0; pos <= 180; pos += 1) { // rotate from 0 degrees to 180 degrees
    // in steps of 1 degree
    servo.write(pos);                   // tell servo to go to position in variable 'pos'
    delay(10);                          // waits 10ms for the servo to reach the position
  }

  for (pos = 180; pos >= 0; pos -= 1) { // rotate from 180 degrees to 0 degrees
    servo.write(pos);                   // tell servo to go to position in variable 'pos'
    delay(10);                          // waits 10ms for the servo to reach the position
  }
  */

  while (Serial.available() > 0) {
    char mode = Serial.read();
    Serial.printf("Keyboard input: %c\n", mode);
    switch(mode){
      case '0':
        rail.close();
        break;
      case '1':
        rail.open();
        break;
      default:
        Serial.println("Input not Recognized");
    }
   }
}
