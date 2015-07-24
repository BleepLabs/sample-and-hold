
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>

long prev0,prev1;

AudioEffectSH          SH1;          

AudioSynthWaveform       pulse1;
AudioSynthWaveformSine   sine1;          

AudioOutputAnalog        dac1;           
AudioConnection          patchCord5(sine1, 0, SH1, 0);
AudioConnection          patchCord11(SH1, 0, dac1, 0);




void setup(void)
{

  Serial.begin(9600);
  AudioMemory(10);
  pulse1.begin(.8,100,WAVEFORM_PULSE);
  sine1.amplitude(.8);
  SH1.begin(0,0);  // (smooth enable 0 or 1 ,amount 0.00-1.00 )

  analogReadResolution(12);
  analogReadAveraging(21);
  pinMode(3,INPUT_PULLUP);

}


void loop(void)
{

  uint16_t sine_freq = analogRead(A1)*4;
  float SH_amount = analogRead(A2)*.00025; 
  short smooth_switch =!digitalRead(3); //if 3 is low, smooth is on


  SH1.amount(SH_amount);  //expects 0.0 to 1.0.
  SH1.smooth(smooth_switch);  

  /*
    When smooth = 0 127 levels of reduction are selected.
   The signal is reduced by simple division. 44.k / 2, 44.k / 3 etc.
   This is the classic bit crush sound
   
   If smooth = 1 the reduction is smoothed between steps. 
   The value going in needs to be stable. If it jitters there will be a lot of noise.
   
   */

  sine1.frequency(sine_freq);

  if (millis() - prev0>200){  
    prev0=millis();

    Serial.print("   pitch "); 
    Serial.println(sine_freq);
    Serial.println();

  }

  delay(5);
}






