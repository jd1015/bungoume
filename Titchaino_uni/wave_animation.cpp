/*****************************************/
// wave animation for Titchaino and ikkeiplexing shield
// by ikkei 2014.05.06
//

#include <arduino.h>
#include <ikkeiplexing.h>

#include "wave_animation.h"

static ikkeiplexing iLedSign;

const byte wave[] = {
  B00110000,
  B00001100,
  B00000010,
  B00000010,
  B00001100,
  B00110000,
  B01000000,
  B01000000,
};

static byte w_cnt = 0;
static byte icount;
static byte period;

void wave_animation_init(){
  period = 5;
  w_cnt = 0;
}


void wave_animation(){
  icount++;
  if (icount == period){
    icount = 0;
    iLedSign.ShiftRight();
    iLedSign.Vwrite(0, wave[w_cnt]);
    w_cnt++;
    w_cnt %= sizeof(wave)/sizeof(wave[0]);
  }
}
