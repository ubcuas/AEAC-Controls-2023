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
void Help();
void Stop();
void TrackLoop(bool flag);
void ToggleLoop();
void playFile(const char*filename);
bool StartLoop = false;

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
  Help();
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

/*
Function to Enable Sound Looping
*/
void TrackLoop(bool flag){
  if(!flag){
    return;
  }
  else{
    //Check if music is stopped, if yes then play the last song
    if(!playWav1.isPlaying()){
      playFile(MyList.SendTrack(MyList.CurrentTrackNo));
    }
  }
}

/*
Function to toggle the Loop Flag
*/
void ToggleLoop(){
  StartLoop = !StartLoop;
  Serial.printf("Looping Toggled, it is now: %s\n", StartLoop? "ENALBED": "DISABLED");
}

/*
Function to let the user know how to use the Music Player.
*/
void Help() {
  Serial.println(Message);  
  Serial.println("---------------------------------------------------------");
  Serial.println("Thank you for using the Music Player v1.0. ~~ Nischay J. [28th March 2023]");
  Serial.println("The Player is very simple to operate.");
  Serial.println("You operate using single character inputs.");
  Serial.println("The music player will display all available track at startup.");
  Serial.println("At a time only 10 can be selected.");
  Serial.println("Press 'l'(Lowercase L) to display the current 10 selected tracks." );
  Serial.println("To play a specific track, send the track number (0-9).");
  Serial.println("To stop a track, press 's'");  
  Serial.println("Send 'x' to toggle loop of track.");
  Serial.println("To go to the next 10 tracks press 'f' the next 10 tracks will be displayed.");
  Serial.println("To go to the last 10 tracks press 'b' the previous 10 tracks will be displayed.");
  Serial.println("To extend the arm, send 'e'.");
  Serial.println("To retract the arm, send 'r'.");
  Serial.println("Note: The arm is a servo motor and was used to test if the music playing block the Teensy.");
  Serial.println("To see this Help message again, press 'h'.");
  Serial.println("Enjoy your music!");
  Serial.println("---------------------------------------------------------");
}

#endif