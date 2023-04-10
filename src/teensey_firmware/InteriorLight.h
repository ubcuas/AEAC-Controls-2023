/*
*   InteriorLED.h
*/
#ifndef INTERIORLED_H
#define INTERIORLED_H
#include "Arduino.h"
#include <FastLED.h> 

class InteriorLight {
    private:
    uint8_t Brightness;
    int NumLeds;
    CRGB White = 0xffe082;
    CRGB Yellow =  0xfcba03;
    CRGB Red = 0xfc0303;


    //HardwareSerial Serial;
    bool print;

    public:
    void Setup(CRGB *leds, int num_leds, uint8_t brightness, bool debug);
    void ArmCabin(CRGB *leds);
    void DisarmCabin(CRGB *leds);
    void FillAlternating(CRGB *leds, CRGB base_color, CRGB color, uint16_t spacing);
    void FillSolid(CRGB *leds, CRGB color); 
};
#endif
