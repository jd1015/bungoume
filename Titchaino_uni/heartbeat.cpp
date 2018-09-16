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

const unsigned int heart[3][8] = {
 { // 点滅1
  256*B10101010+B10101010,
  256*B01010101+B01010101,
  256*B10101010+B10101010,
  256*B01010101+B01010101,
  256*B10101010+B10101010,
  256*B01010101+B01010101,
  256*B10101010+B10101010,
  256*B01010101+B01010101,
 },
 { // 点滅2
  256*B01010101+B01010101,
  256*B10101010+B10101010,
  256*B01010101+B01010101,
  256*B10101010+B10101010,
  256*B01010101+B01010101,
  256*B10101010+B10101010,
  256*B01010101+B01010101,
  256*B10101010+B10101010,
 },
 { // oshushi?
  256*B00000000+B00000000,
  256*B01111111+B11111110,
  256*B10000000+B00000001,
  256*B00001110+B11100000,
  256*B00010000+B00010000,
  256*B01000101+B01000100,
  256*B10100010+B10001010,
  256*B10100000+B00001010,
 },
};
void heartbeat_init(){
  period = 1;
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
