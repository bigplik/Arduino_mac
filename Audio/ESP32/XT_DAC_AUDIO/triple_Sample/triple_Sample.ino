//nie działa

#include "SoundData.h"
#include "rawData.h"
#include "XT_DAC_Audio.h"


XT_DAC_Audio_Class DacAudio(25,0);      // Create the main player class object. 
                                        // Use GPIO 25, one of the 2 DAC pins and timer 0
                                      
XT_Wav_Class Rooster(kogut);     // create an object of type XT_Wav_Class that is used by 
XT_Wav_Class Cow(krowa);
                   
void setup() {
  //analogReadResolution(10);
  pinMode(0,INPUT_PULLUP);
  pinMode(35,INPUT_PULLUP);
  //WarOfWorlds.RepeatForever=true;
  DacAudio.Play(&Rooster);             // Set to play initially at normal speed, will be altered in main loop according to
                                        // the value of the anaog input 
}

void loop() {
  DacAudio.FillBuffer();                // Fill the sound buffer with data, required once in your main loop
  //WarOfWorlds.Speed=analogRead(ANALOG_PIN)/512.0;   // Gives us a speed range between 0 and 7
  //DacAudio.Play(&Cow);
  /*
  if(digitalRead(35)==0){
    DacAudio.Play(&Rooster);
    //SetVolume(125);
  }
  else if(digitalRead(0)==0){
    DacAudio.Play(&Cow);
  }
  else{    
  }
  */
}
