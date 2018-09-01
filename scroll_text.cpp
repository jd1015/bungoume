/*****************************************/
// scroll text for Titchaino and ikkeiplexing shield
// by ikkei 2014.05.06
// reviewed 2018.02.01
// 

#include <arduino.h>
#include <ikkeiplexing.h>
#include <iFont.h>

#include "scroll_text.h"

static ikkeiplexing iLedSign;
static iFont iFont;

//const unsigned char text[]="Hello world!  \xCA\xDB\xB0\xDC\xB0\xD9\xC4\xDE! \xEA\xFB\xB0\xFC\xB0\xF9\xE4\xDE! \x81\x83\x84\x80   ";
//const unsigned char text[]="\xE1\x8F\xE1\x8C\x92\xB0\xE9  \x80 \x80        "; // Titchaino
const unsigned char text[] ="Hello world! Titchaino ";

static byte w_cnt = 0;
static byte t_cnt = 0;
static byte icount;
static byte period;

void scroll_text_init(){
  period = 5;
  t_cnt = 0;
  w_cnt = 0;
}


void scroll_text(){
  icount++;
  if (icount == period){
    icount = 0;
    iLedSign.ShiftLeft();
    uint8_t d = iFont.Width(text[t_cnt]);
    iLedSign.Vwrite(15, iFont.Data(text[t_cnt],w_cnt));
    w_cnt++;
    if (w_cnt > d){
      w_cnt = 0;
      t_cnt++;
      if (text[t_cnt] == '\0'){
        t_cnt = 0;
      }
    }
  }
}



