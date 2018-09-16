/*****************************************/
// random fade for Titchaino and ikkeiplexing shield
// by ikkei 2014.05.06
// 

#include <arduino.h>
#include <ikkeiplexing.h>

#include "random_fade.h"
#include "heartbeat.h"

static ikkeiplexing iLedSign;

static byte w_cnt = 0;
static byte t_cnt = 0;
static byte icount;
static byte period;
static byte cnt;


#define THMAX 47
#define SEEDMAX 10
#define WAIT 20
static int th=0;
static int dt=1;
static byte r_state;
static int seed = 0;


void random_fade_init(){ 
  period = 1;
  cnt = WAIT;
  r_state = 0;
  seed = 0;
} 


void change_seed(){
  seed++;
  if (seed > SEEDMAX){
    seed = 0;
  }
}

void change_state(){
  switch (r_state){
    case 0:
      cnt--;
      if (cnt == 0){
        r_state = 1;
        //change_seed();
      }
      break;
    case 1:
      th++;
      if (th > THMAX){
        r_state = 2;
        cnt = WAIT;
      }
      break;
    case 2:
      cnt--;
      if (cnt == 0){
        r_state = 3;
        //change_seed();
      }
      break;
    case 3:
      th--;
      if (th == 0){
        r_state = 0;
        cnt = WAIT;
      }
      break;
  }
}   


void random_fade(){
  icount++;
  if (icount == period){
    icount = 0;
    change_state(); 
    randomSeed(seed); // seed == 0 : invalid
    for (byte y=0; y<8; y++){
      for (byte x=0; x<16; x++){
        iLedSign.Set(x, y, bitRead(heart[2][y], 15-x) & (random(0,THMAX) < th));
      }
    }
  }
}
