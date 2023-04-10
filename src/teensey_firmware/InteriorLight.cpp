//USE for WS2812B LED Strip: 

#include "InteriorLight.h"

void InteriorLight::Setup(CRGB *leds, int num_leds, uint8_t brightness, bool debug){
    print = debug;
    Brightness = brightness;
    NumLeds = num_leds;

    FastLED.setBrightness(Brightness);
    FastLED.setMaxPowerInVoltsAndMilliamps(5, 1500);
    set_max_power_indicator_LED(13);
    FillSolid(leds, CRGB::Black);
    FastLED.show();
    if(print){
        Serial.println("InteriorLED Setup Done!");
    }
}


void InteriorLight::FillAlternating(CRGB *leds, CRGB base_color, CRGB color, uint16_t spacing){
  for (uint16_t i = 0; i < NumLeds; i++){
    if (i%spacing == 0){
      leds[i] = color;
       FastLED.show();
    }
    else{
      leds[i] = base_color;
       FastLED.show();
    }
  }
 
  if(print){
      Serial.println("Interior LED filled alternating colors");
  }
}


void InteriorLight::FillSolid(CRGB *leds, CRGB color){
  for (uint16_t i = 0; i < NumLeds; i++){
    leds[i] = color;
    FastLED.show();
  }

  if(print){
      Serial.println("Interior LED filled solid color");
  }
}

void InteriorLight::ArmCabin(CRGB *leds){
  FillAlternating(leds, White, Red, 4);
  delay(1000);
  FillAlternating(leds, White, Yellow, 4);
  delay(1000);
  FillSolid(leds, White);
}

void InteriorLight::DisarmCabin(CRGB *leds){
  FillAlternating(leds, White, Yellow, 4);
  delay(1000);
  FillAlternating(leds, White, Red, 4);
  delay(1000);
  FillSolid(leds, White);
 
}
