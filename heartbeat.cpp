/*****************************************/
// heartbeat for Titchaino and ikkeiplexing shield
// by ikkei 2014.05.06
// 

#include <arduino.h>
#include <ikkeiplexing.h>

#include "heartbeat.h"

static ikkeiplexing iLedSign;

static byte period;
static byte h_cnt = 0;

const unsigned int heart[2][8] = {
 { // big heart
  256*B00011100+B01110000,
  256*B00100010+B10001000,
  256*B00100001+B00001000,
  256*B00000000+B00000000,
  256*B00010000+B00010000,
  256*B00001000+B00100000,
  256*B00000010+B10000000,
  256*B00000001+B00000000,
 },
 { // small heart
  256*B00000000+B00000000,
  256*B00000100+B01000000,
  256*B00001010+B10100000,
  256*B00001001+B00100000,
  256*B00000100+B01000000,
  256*B00000010+B10000000,
  256*B00000001+B00000000,
  256*B00000000+B00000000,
 },
};

void heartbeat_init(){
  period = 47;
  h_cnt = 0;
}


void heartbeat(){
  static byte icount = 0;
  icount++;
  if (icount == period){
    icount = 0;
    iLedSign.write(0, heart[h_cnt], 8);
    h_cnt ^= 1;
  }
}
