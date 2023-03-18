#include "DoorServo.h"
#include "LightPCB.h"

// Teensey 4.0 firware state machine for automating cabin belt and door systems using RFD input
#define RFD_IN 0
#define DOOR_SERVO 1
#define DOOR_LOCK 2
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
#define LOCKOPEN 50
#define LOCKCLOSE 230
DoorServo lockServo(DOOR_LOCK, PrintDebug, FREQUENCY);

//Cabin Lights 
LightPCB LeftLight(LED_LEFT, PrintDebug);
LightPCB RightLight(LED_RIGHT, PrintDebug);
LightPCB BottomLight(LED_RIGHT, PrintDebug);



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
  lockServo.updateParams(LOCKOPEN, LOCKCLOSE);

  // PIN INIT VALUE
  // digitalWrite(LED_OUT, OPEN);
}

void loop() {
  int cabin_state = digitalRead(RFD_IN);

  if (cabin_state == SECURED) {

    // seatbelt ON
    analogWrite(BELT_ACT, BELT_ON);
    
    // door CLOSE
    doorServo.close();
    // door LOCK
    lockServo.close();
    // cabin Lights Armed
    LeftLight.ArmCabin();
    RightLight.ArmCabin();
    BottomLight.ArmCabin();

  } 
  else if (cabin_state == OPEN) {
    // door UNLOCK
    lockServo.open();
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