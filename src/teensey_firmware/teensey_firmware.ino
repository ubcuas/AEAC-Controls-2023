//Libraries
#include "DoorServo.h"
#include "LightPCB.h"
#include "AudioFunctions.h"

// Teensey 4.0 firware state machine for automating cabin belt and door systems using RFD input
#define RFD_IN 0
#define DOOR_SERVO 1
#define DOOR_LOCK 2
#define BELT_ACT 3
#define PAX_LED 4

// cabin states
#define OPEN 0
#define SECURED 1

// motor specs
#define BELT_OFF 1980
#define BELT_ON 1150
#define BELT_ACT_FREQ 300

//Cabin door
#define SERVO_FREQ 50
#define PrintDebug 1
DoorServo doorServo(DOOR_SERVO, PrintDebug, SERVO_FREQ);

//Cabin Door Lock
#define LOCKOPEN 1980
#define LOCKCLOSE 1150
#define LockFrequency 300
DoorServo lockServo(DOOR_LOCK, PrintDebug, LockFrequency);

//Cabin Lights 
LightPCB CabinLight;
int cabin_state = 2;// = digitalRead(RFD_IN);
bool changed = false;

void setup() {
  // teensey serial config
  Serial.begin(9600);
    while (!Serial && millis () < 3000)
    ;

  // INPUT PIN CONFIG
  pinMode(RFD_IN, INPUT);

  // OUTPUT PIN CONFIG
  pinMode(BELT_ACT, OUTPUT);
  analogWriteFrequency(BELT_ACT, BELT_ACT_FREQ);

  //Setup LockServo Open/CloseValues
  lockServo.updateParams(LOCKOPEN, LOCKCLOSE);

  //Configure Cabin Light
  CabinLight.Setup(PAX_LED, PrintDebug);

  //Initialize the audio
  initAudio();
}

void loop() {
  //int cabin_state;// = digitalRead(RFD_IN);

  //Take Input from User via serial port
  while (Serial.available() > 0) {
    char mode = Serial.read();
    if (Serial.read() == '\n') {}
    switch(mode){
      case 'c':
        cabin_state = SECURED;
        changed = true;
        break;
      case 'o':
        cabin_state = OPEN;
        changed = true;
        break;
      case 's':
        Stop();
        break;
      case 'f':
        MyList.Fwd();
        break;
      case 'b':
        MyList.Bwd();
        break;
      case 'l':
        MyList.DisplayCurrentList();
        break;  
      default:
        int tracknum = MyList.isInList(mode);
        if(tracknum != -1){
          playFile(MyList.SendTrack((uint16_t)tracknum));
        }
        else{
          Serial.println("Input not Recognized");
        }
        break;
    }
  }
  if (cabin_state == SECURED && changed == true) {
    changed = false;
    // seatbelt ON
    analogWrite(BELT_ACT, BELT_ON);
    //delay(1000);
    
    // door CLOSE
    doorServo.close();
    delay(1000);

    // door LOCK
    lockServo.close();

    // cabin Lights Armed
    CabinLight.ArmCabin();
  } 
  else if (cabin_state == OPEN  &&  changed == true) {
    changed = false;
    // door UNLOCK
    lockServo.open();
    delay(1000);

    // door OPEN
    doorServo.open();
    //delay(1000);

    // seatbelt OFF
    analogWrite(BELT_ACT, BELT_OFF);

    // cabin Lights Un-Armed
    CabinLight.DisarmCabin();
  }
}