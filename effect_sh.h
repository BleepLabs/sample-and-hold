#ifndef effect_sh_h_
#define effect_sh_h_

#include "Arduino.h"
#include "AudioStream.h"

class AudioEffectSH : public AudioStream
{
public:
  AudioEffectSH() : AudioStream(2, inputQueueArray) { }


  virtual void update(void);

  void smooth(short sm) {
    smooth_en=sm;
  }

  void manual_hold(short mh) {
    manual_hold_en=mh;
  }

  void amount(float rr_amt) {

    if (smooth_en==1){
      if (rr_amt>0){
        float a3t = pow(rr_amt, 2);
        rate_reduction_amt =rr_amt* 65536.0f;

      }
      if (rr_amt<=0){
        rate_reduction_amt=0;
      } 
    }   

    if (smooth_en==0){
      if (rr_amt>0){
        float temp0=(rr_amt-1)*-1;
        float temp2 = pow(temp0, 2);

        rate_reduction_amt =temp2*127.0f;

      }
      if (rr_amt<=0){
        rate_reduction_amt=0;
      } 
    }     

  }

  void begin(float rrr,short sss){
    smooth(rrr);
    amount(rrr);
  }

 


private:
  audio_block_t *inputQueueArray[2];
  uint32_t rate_reduction_amt=0;  
  int32_t  mix;  
  int32_t  mix_inv;  
  short smooth_en=0 ;  
  short manual_hold_en=0; ;  


};

#endif
