// Playing a digital WAV recording repeatadly using the XTronical DAC Audio library
// prints out to the serial monitor numbers counting up showing that the sound plays 
// independently of the main loop
// See www.xtronical.com for write ups on sound, the hardware required and how to make
// the wav files and include them in your code

#include "test.h"
#include "SoundData.h"
#include "XT_DAC_Audio.h"

XT_Wav_Class ForceWithYou(rawData);     // create an object of type XT_Wav_Class that is used by 
                                      // the dac audio class (below), passing wav data as parameter.

XT_Wav_Class ForceWithYou2(Force);
                                      
XT_DAC_Audio_Class DacAudio(25,0);    // Create the main player class object. 
                                      // Use GPIO 25, one of the 2 DAC pins and timer 0

uint32_t DemoCounter=0;               // Just a counter to use in the serial monitor
                                      // not essential to playing the sound
int sound = 0;

void setup() {
  Serial.begin(115200);               // Not needed for sound, just to demo printing to the serial
                                      // Monitor whilst the sound plays, ensure your serial monitor
                                      // speed is set to this speed also.
  pinMode(0,INPUT_PULLUP);
  pinMode(35,INPUT_PULLUP);
}


void loop() {

     switch (sound) {
        case 0:
            if(digitalRead(35)==0)sound = 1;
            //if(digitalRead(0)==0)sound = 2;
        break;
        case 1:
            DacAudio.FillBuffer(); // Fill the sound buffer with data
            if(ForceWithYou.Playing==false)
            DacAudio.Play(&ForceWithYou,true);       // play it, this will cause it to repeat and repeat...
            if(digitalRead(35)==0)sound = 0;
            //if(digitalRead(0)==0)sound = 2;
        break;
        /*
        case 2:
            DacAudio.FillBuffer(); // Fill the sound buffer with data
            if(ForceWithYou2.Playing==false)
            DacAudio.Play(&ForceWithYou2);       // play it, this will cause it to repeat and repeat...
            if(digitalRead(35)==0)sound = 0;
            if(digitalRead(0)==0)sound = 1;
        break;
        */
     }
}
