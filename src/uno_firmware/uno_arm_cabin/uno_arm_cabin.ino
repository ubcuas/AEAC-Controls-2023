// Ground Control Arduino Uno Firware
// Receive char from keyboard, 1 = secure cabin, 0 = open cabin
#define PIN7 7

void setup() {
  pinMode(PIN7, OUTPUT);
  Serial.begin(9600);

  digitalWrite(PI7N, 1);
}

void loop() {
  int out;

  // Keyboard input - TEMP!!
  if (Serial.available() > 0) {
    char key = Serial.read();
    if (key == '1') {
      out = 1;
    } else if (key == '0') {
      out = 0;
    }
 
    // RFD TX OUTPUT
    digitalWrite(PIN7, out);
  }
}