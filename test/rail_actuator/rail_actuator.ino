/*
300Hz
75 - fully extended - 2.5cm
160 - fully retracted - 0cm

75 - seat belt closed
115 - seat belt open

*/

#define PIN_SERVOR 3


void setup() {
   // set servo
  pinMode(PIN_SERVOR, OUTPUT);
  Serial.begin(9600);
  analogWriteFrequency(PIN_SERVOR, 300);
  analogWriteResolution(8);
}

void loop() {
  // int out;
  int pos;
/*
  for (int i = 1; i<255; i++){
    Serial.println(i);
    analogWrite(PIN_SERVOR, i);
    delay(100);
   
  }
  for (int i = 255; i<1; i--){
    Serial.println(i);
    analogWrite(PIN_SERVOR, i);
    delay(1000);
   
  }
*/

  while (Serial.available() > 0) {

    pos = Serial.parseInt();
    if (Serial.read() == '\n') {}
    Serial.printf("Keyboard input: %d\n", pos);
    analogWrite(PIN_SERVOR, pos);
  }

}
