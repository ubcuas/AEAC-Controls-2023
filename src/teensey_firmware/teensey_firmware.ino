#include "LightPCB.h"

LightPCB L1(7, 1);
LightPCB L2(8, 1);
LightPCB L3(9, 1);

volatile uint8_t LightSel = 0;  

void Arm();
void Disarm();

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
      case 'a':
        Arm();  
        break;
      case 'd':
        Disarm();
        break;
      case 's':
        LightSel++;
        if(LightSel>2){
          LightSel = 0;
        }
        Serial.printf("Active Light PCB is : L%d\n", (LightSel+1));
        break;
      default:
        Serial.println("Input not Recognized");
    }
   }
}

void Arm(){
  switch (LightSel){
    case 0:
      L1.ArmCabin();
      break;
    case 1:
      L2.ArmCabin();
      break;
    case 2:
      L3.ArmCabin();
      break;
    default:
      break;
  }
}

void Disarm(){
  switch (LightSel){
    case 0:
      L1.DisarmCabin();
      break;
    case 1:
      L2.DisarmCabin();
      break;
    case 2:
      L3.DisarmCabin();
      break;
    default:
      break;
  }
}