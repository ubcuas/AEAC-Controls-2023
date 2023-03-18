#include "DoorServo.h"
#include "LightPCB.h"

// Teensey 4.0 firware state machine for automating cabin belt and door systems using RFD input
#define RFD_IN 0
#define DOOR_SERVO 1
#define DOOR_LOCK 7
#define BELT_ACT 3
#define LED_LEFT 4
#define LED_BOTTOM 5
#define LED_RIGHT 6
// #define LED_OUT 1 // TEMP

// cabin states
#define OPEN 0
#define SECURED 1

// motor specs
#define BELT_OFF 115
#define BELT_ON 75
#define BELT_ACT_FREQ 300

//Cabin door
#define FREQUENCY 50
#define PrintDebug 1
DoorServo doorServo(DOOR_SERVO, PrintDebug, FREQUENCY);

//Cabin Door Lock
#define LOCKOPEN 380
#define LOCKCLOSE 100
DoorServo lockServo(DOOR_LOCK, PrintDebug, FREQUENCY);

//Cabin Lights 
LightPCB LeftLight(LED_LEFT, PrintDebug);
LightPCB RightLight(LED_RIGHT, PrintDebug);
LightPCB BottomLight(LED_RIGHT, PrintDebug);


int cabin_state = 0;
int changed = 0;

void setup() {
    // teensey serial config
  Serial.begin(9600);

  // INPUT PIN CONFIG
  pinMode(RFD_IN, INPUT);

  // OUTPUT PIN CONFIG
  pinMode(RFD_IN, INPUT);

  pinMode(BELT_ACT, OUTPUT);
  analogWriteFrequency(BELT_ACT, BELT_ACT_FREQ);

  //Setup LockServo Open/CloseValues
  lockServo.updateParams(LOCKCLOSE, LOCKOPEN);

  // PIN INIT VALUE
  // digitalWrite(LED_OUT, OPEN);
}

void loop() {
  while (Serial.available() > 0) {
    // look for the next valid integer in the incoming serial stream:
    char mode = Serial.read();
    // look for the newline. That's the end of your sentence:
    if (Serial.read() == '\n') {}
    Serial.printf("Read This %c\n", mode);
    switch(mode){
      case '0':
        cabin_state = 0;
        changed = 1;
        break;
      case '1':
        changed = 1;      
        cabin_state = 1;
        break;
      default:
        Serial.println("Input not Recognized");
    }
   }
 if(changed == 1){
  if (cabin_state == SECURED) {
    changed = 0;
    // seatbelt ON
    analogWrite(BELT_ACT, BELT_ON);
    
    // door CLOSE
    doorServo.close();
    // door LOCK
    lockServo.open();
    // cabin Lights Armed
    LeftLight.ArmCabin();
    RightLight.ArmCabin();
    BottomLight.ArmCabin();

  } 
  else if (cabin_state == OPEN) {
    changed = 0;
    // door UNLOCK
    lockServo.close();
    // door OPEN
    doorServo.open();
    // seatbelt OFF
    analogWrite(BELT_ACT, BELT_OFF);

    // cabin Lights Un-Armed
    LeftLight.DisarmCabin();
    RightLight.DisarmCabin();
    BottomLight.DisarmCabin();
  }
 }
}