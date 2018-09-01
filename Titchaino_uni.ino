/*
  multiplex pattern for Titchaino uni
    by ikkei 2015.04.04
    add acceleration sensor  2015.6.6
    reviewed 2018,02.03
    add auto adjust acceleration sensor 2018.04.17
*/

#include <arduino.h>
#include <MsTimer2.h>
#include <ikkeiplexing.h>
#include <EEPROM.h>
#include "iFont.h"
#include <avr/sleep.h>

#include "complex_pattern.h"
#include "heartbeat.h"
#include "random_fade.h"
#include "wave_animation.h"
#include "scroll_text.h"
#include "bounce_balls.h"
#include "fountain.h"
#include "gravity.h"

static ikkeiplexing iLedSign;
static iFont iFont;

#define FRAME  0x01
#define TENMS  0x02

static byte icount = 0;
static int sleep_count;
//#define SLEEPTIME 0 // no sleep
#define SLEEPTIME 1875 // 16ms x 1875 = 30 sec

byte event = 0;
byte swlvl = 0;
static byte state;
#define S_OFF 99
#define S_WAKE 88
#define S_AOFF 77

static byte mode_num;
void mode_setup(byte num) {
  icount++;
  if (icount >= 20) {
    icount = 0;
    state = num;
    switch (num) {
      case 1: // space invaders comlex pattern
        complex_pattern_init();
        break;
      case 2: // heart beat
        heartbeat_init();
        break;
      case 3: // random fade
        random_fade_init();
        break;
      case 4: // wave
        wave_animation_init();
        break;
      case 5: // scroll text "Titchaino"
        scroll_text_init();
        break;
      case 6: //
        bounce_balls_init();
        break;
      case 7: //
        fountain_init();
        break;
      case 8: //
        gravity_init();
        break;
    }
  }
}

void display_number(byte num) {
  iLedSign.Clear();
  byte d = iFont.Width('0' + num);
  for (byte i = 0; i < d; i++) {
    iLedSign.Vwrite(i + 7 - d / 2, iFont.Data('0' + num, i));
  }
}



ISR(PCINT2_vect) {
  // do nothing
}

#define PSW1 0
#define PSW2 1


void sleep_power_down() {
  MsTimer2::stop();
  cli();
  ADCSRA &= ~(1 << ADEN); // disable ADC
  PRR = 0xEF;
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sei();
  // sleep start
  sleep_cpu();
  // wake up
  sleep_disable();
  PRR = 0x00;
  ADCSRA |= (1 << ADEN); // enable ADC
  MsTimer2::start();
}


void setup() {
  iLedSign.Init(TITCHAINO_UNI, SINGLE_BUFFER);
  //iLedSign.Init(TITCHAINO_UNI,SINGLE_BUFFER);
  mode_num = EEPROM.read(0);
  if (mode_num > 8 || mode_num == 0) {
    mode_num = 1;
    EEPROM.write(0, mode_num);
  }
  mode_setup(mode_num);
  // PSW1 -- PD0 / PCINT16 -- PCIE2
  PCICR = 0x00;
  PCMSK2 = 0x01; // PCINT16
  PCMSK1 = 0;
  PCMSK0 = 0;
  PCICR = 0x04; // PCIE2  pin change interrupt enable  PCINT16
  sleep_count = SLEEPTIME;
}


void loop() {
#define HOLDTIME 80
  static byte hold_cnt = 0;
  if ((iLedSign.GetPeriod() & FRAME) != 0) {
    event = iLedSign.GetSW(2);
    swlvl = iLedSign.GetSW(0);
    if (swlvl & 0x80) {
      if (hold_cnt < HOLDTIME) {
        hold_cnt++;
        if (hold_cnt == HOLDTIME) {
          if (state == S_WAKE) {
            mode_num = EEPROM.read(0);
            state = mode_num;
          } else {
            iLedSign.Clear();
            state = S_OFF;
          }
        }
      }
    } else {
      hold_cnt = 0;
      if (sleep_count) {
        sleep_count--;
        if (sleep_count == 0) {
          iLedSign.Clear();
          state = S_AOFF;
        }
      }
    }
    if ((event & 0x80) != 0 || state == S_AOFF) {
      if (state == S_OFF || state == S_WAKE || state == S_AOFF) {
        pinMode(PSW1, INPUT_PULLUP);
        sleep_power_down();
        hold_cnt = 0;
        sleep_count = SLEEPTIME;
        state = S_WAKE;
      }
    } else if ((event & 0x40) != 0) {
      mode_num++;
      if (mode_num > 8 || mode_num == 0) {
        mode_num = 1;
      }
      EEPROM.write(0, mode_num);
      display_number(mode_num);
      icount = 0;
      state = 0;
      sleep_count = SLEEPTIME;
    }
    switch (state) {
      case 0:
        mode_setup(mode_num);
        break;
      case 1:
        invader();
        break;
      case 2:
        heartbeat();
        break;
      case 3:
        random_fade();
        break;
      case 4:
        wave_animation();
        break;
      case 5:
        scroll_text();
        break;
      case 6:
        bounce_balls();
        break;
      case 7:
        fountain();
        break;
      case 8:
        gravity();
        break;
    }
  }
}

