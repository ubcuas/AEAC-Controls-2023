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

#define DOOR_OPEN 400
#define DOOR_CLOSE 150
#define DOOR_SERVO_FREQ 50



void setup() {
  // teensey serial config
  Serial.begin(9600);

  // INPUT PIN CONFIG
  pinMode(RFD_IN, INPUT);

  // OUTPUT PIN CONFIG
  pinMode(RFD_IN, INPUT);

  // seat belt
  pinMode(BELT_ACT, OUTPUT);
  analogWriteFrequency(BELT_ACT, BELT_ACT_FREQ);

  // door open & close
  pinMode(DOOR_SERVO, OUTPUT);
  analogWriteFrequency(DOOR_SERVO, DOOR_SERVO_FREQ);

  // PIN INIT VALUE
  // digitalWrite(LED_OUT, OPEN);
}

void loop() {
  int cabin_state = digitalRead(RFD_IN);

  if (cabin_state == SECURED) {

    // seatbelt ON
    analogWrite(BELT_ACT, BELT_ON)
    
    // door CLOSE
    analogWrite(DOOR_SERVO, DOOR_CLOSE)

    // door LOCK

  } else if (cabin_state == OPEN) {
    // door UNLOCK

    // door OPEN
    analogWrite(DOOR_SERVO, DOOR_OPEN)

    // seatbelt OFF
    analogWrite(BELT_ACT, BELT_OFF)
  }
}