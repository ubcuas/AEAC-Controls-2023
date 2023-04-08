#ifndef __AUDIOFUNCTIONS_H__
#define __AUDIOFUNCTIONS_H__

#include "SongList.h"

// Use these with the Teensy Audio Shield
#define SDCARD_CS_PIN    10

//Sound Initialization
AudioPlaySdWav           playWav1;
AudioOutputI2S           audioOutput;
AudioConnection          patchCord1(playWav1, 0, audioOutput, 0);
SongList MyList;
File LastDir;

void initAudio();
void Stop();
void playFile(const char*filename);

void playFile(const char *filename)
{
  Serial.print("Playing file: ");
  Serial.println(filename);
  // Start playing the file.  This sketch continues to
  // run while the file plays.
  playWav1.play(filename);
  // A brief delay for the library read WAV info
  delay(25);
}

void initAudio(){
  AudioMemory(8);

  Serial.println("Starting sd setup");
  if (!(SD.begin(SDCARD_CS_PIN))) {
    // stop here, but print a message repetitively
    while (1) {
      Serial.println("Unable to access the SD card");
      delay(500);
    }    
  }
  LastDir = SD.open("/");
  MyList.SearchSongs(LastDir);
  Serial.println("Audio Setup Done");
}

/*
Function to Stop Playing Music
*/
void Stop(){
  Serial.println("Sound Stopped");
  playWav1.stop();
}
#endif