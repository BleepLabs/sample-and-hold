//rather than altering your audio.h or using my vesion of the audio library 
// you can just include the effect and haive the files in this sketches folder
#include <effect_sh.h> 

/*
This is kind of a long way around just to make a waveform produce random frequencies
but its is a method used in analog syntheseis to make the classic "computer is thinking" sound
and is a good example of sample and hold

*/
  
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>

AudioSynthNoiseWhite     noise1;       
AudioSynthWaveform       pulse1;      
AudioEffectSH                   SH1;          
AudioSynthWaveformSineModulated sine_fm1;      
AudioOutputAnalog        dac1;         
AudioConnection          patchCord1(noise1, 0, SH1, 0);
AudioConnection          patchCord2(pulse1, 0, SH1, 1);
AudioConnection          patchCord3(SH1, sine_fm1);
AudioConnection          patchCord4(sine_fm1, dac1);


long prev0,prev1;

void setup(void)
{

  Serial.begin(9600);
  AudioMemory(10);
  SH1.begin(0,0);  // (smooth enable 0 or 1 ,amount 0.00-1.00 )
  pulse1.begin(.8,100,WAVEFORM_PULSE);
  sine_fm1.amplitude(.8);

  analogReadResolution(12);
  analogReadAveraging(21);
  noise1.amplitude(.8);

  pinMode(3,INPUT_PULLUP);

}


void loop(void)
{

  uint16_t sine_freq = analogRead(A1)*4;
  uint16_t pulse_freq = analogRead(A2)/4;
  float pulse_width = analogRead(A3)*.00025; 

  short hold_button=!digitalRead(3);


  
  SH1.manual_hold(hold_button); 
  /*
  when this is 1, or the signl coming into input 1 is above 0 the signal will be held at the last value. 
  This can make some neat audio effects when modualted at an LFO or audio rate but a changing pule wave
  but here we're using it to take random levels from the noise.
  
  */


  sine_fm1.frequency(sine_freq);

  pulse1.frequency(pulse_freq);
  pulse1.pulseWidth(.0005); //or try "pulse_width"
  

  delay(5);
}
