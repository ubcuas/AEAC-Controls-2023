// Teensey 4.0 firware state machine for automating cabin belt and door systems using RFD input

//Libraries
#include "DoorServo.h"
#include "LightPCB.h"
#include "InteriorLight.h"
#include "AudioFunctions.h"


// Pin Map
#define RFD_IN 0
#define DOOR_SERVO 1
#define DOOR_LOCK 2
#define BELT_ACT 3
#define PAX_LED 4
#define INTERIOR_LED 15

//Cabin States
#define OPEN 0
#define SECURED 1

//Seat Belt
#define BELT_OPEN 1980
#define BELT_CLOSE 1150
#define BELT_FREQ 300
#define BELT_DELAY 1
#define PrintDebug 1
DoorServo seatBeltServo(BELT_ACT, PrintDebug, BELT_FREQ, BELT_OPEN, BELT_CLOSE, BELT_DELAY);

//Cabin Door
#define DOOR_OPEN 220
#define DOOR_CLOSE 450
#define DOOR_FREQ 50
#define DOOR_DELAY 5
#define PrintDebug 1
DoorServo doorServo(DOOR_SERVO, PrintDebug, DOOR_FREQ, DOOR_OPEN, DOOR_CLOSE, DOOR_DELAY);

//Cabin Door Lock
#define LOCK_OPEN 1980
#define LOCK_CLOSE 1150
#define LOCK_FREQ 300
#define LOCK_DELAY 1
DoorServo lockServo(DOOR_LOCK, PrintDebug, LOCK_FREQ, LOCK_OPEN, LOCK_CLOSE, LOCK_DELAY);

//Exterior Lights 
LightPCB CabinLight;

//Interior Lights


#define NUM_LEDS_PER_STRIP 29
#define NUM_STRIPS 1
#define NUM_LEDS  NUM_LEDS_PER_STRIP * NUM_STRIPS
#define INTERIOR_LIGHT_BRIGHTNESS 50
CRGB leds[NUM_LEDS_PER_STRIP * NUM_STRIPS];

InteriorLight CabinInteriorLight; 


int cabin_state = 2;// = digitalRead(RFD_IN);
bool changed = false;



void setup() {
  // teensey serial config
  Serial.begin(9600);
    while (!Serial && millis () < 3000)
    ;

  // INPUT PIN CONFIG
  pinMode(RFD_IN, INPUT);
  
  //Configure Exterior Light
  CabinLight.Setup(PAX_LED, PrintDebug);

  //Configure Interior Light
  FastLED.addLeds<NUM_STRIPS, WS2812B, INTERIOR_LED, GRB>(leds, NUM_LEDS_PER_STRIP); 
  CabinInteriorLight.Setup(leds, NUM_LEDS, INTERIOR_LIGHT_BRIGHTNESS, PrintDebug);


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
    CabinInteriorLight.ArmCabin(leds);
    
    // seatbelt ON
    seatBeltServo.close();
    delay(1000);
    
    // door CLOSE
    doorServo.close();
    delay(1000);

    // door LOCK
    lockServo.close();
    delay(1000);
    // cabin Lights Armed
    CabinLight.ArmCabin();
  } 
  else if (cabin_state == OPEN  &&  changed == true) {
    changed = false;
    CabinInteriorLight.DisarmCabin(leds);

    // door UNLOCK
    lockServo.open();
    delay(1000);

    // door OPEN
    doorServo.open();
    delay(1000);

    // seatbelt OFF
    seatBeltServo.open();
    delay(1000);

    // cabin Lights Un-Armed
    CabinLight.DisarmCabin();
  }
}