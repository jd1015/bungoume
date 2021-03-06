/*****************************************/
// space invaders
// complex pattern for Titchaino and ikkeiplexing shield
// by ikkei 2014.05.06
// 

#include <arduino.h>
#include <ikkeiplexing.h>

#include "complex_pattern.h"

static ikkeiplexing iLedSign;

// data ID
#define PATT 0 // pattern data
#define TIME 1 // interval time
#define TERM 2 // terminator

static byte cnt;
static byte icount;
static byte period;
static byte pattern;

const uint16_t BitMap[][40][9] PROGMEM = {
{ // 0:INVADER1
{TIME,25,0,0,0,0,0,0,0},
{PATT,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000},
{PATT,0x0000,0x0002,0x0002,0x0003,0x0003,0x0001,0x0000,0x0001},
{PATT,0x0002,0x0001,0x0003,0x0006,0x000F,0x000B,0x000A,0x0001},
{PATT,0x0008,0x0024,0x002F,0x003B,0x003F,0x001F,0x0008,0x0010},
{PATT,0x0020,0x0011,0x003F,0x006E,0x00FF,0x00BF,0x00A0,0x001B},
{PATT,0x0082,0x0244,0x02FE,0x03BB,0x03FF,0x01FF,0x0082,0x0101},
{PATT,0x0208,0x0110,0x03F8,0x06EC,0x0FFE,0x0BFA,0x0A0A,0x01B0},
{PATT,0x0820,0x2448,0x2FE8,0x3BB8,0x3FF8,0x1FF0,0x0820,0x1010},
{PATT,0x2080,0x1100,0x3F80,0x6EC0,0xFFE0,0xBFA0,0xA0A0,0x1B00},
{PATT,0x0820,0x2448,0x2FE8,0x3BB8,0x3FF8,0x1FF0,0x0820,0x1010},
{PATT,0x0208,0x0110,0x03F8,0x06EC,0x0FFE,0x0BFA,0x0A0A,0x01B0},
{PATT,0x0082,0x0244,0x02FE,0x03BB,0x03FF,0x01FF,0x0082,0x0101},
{PATT,0x0020,0x0011,0x003F,0x006E,0x00FF,0x00BF,0x00A0,0x001B},
{PATT,0x0008,0x0024,0x002F,0x003B,0x003F,0x001F,0x0008,0x0010},
{PATT,0x0002,0x0001,0x0003,0x0006,0x000F,0x000B,0x000A,0x0001},
{PATT,0x0000,0x0002,0x0002,0x0003,0x0003,0x0001,0x0000,0x0001},
{PATT,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000},
{PATT,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000},
{TERM,0,0,0,0,0,0,0,0},},

{ // 1:INVADER2
{TIME,25,0,0,0,0,0,0,0},
{PATT,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000},
{PATT,0x0000,0x0000,0x0001,0x0003,0x0003,0x0000,0x0001,0x0002},
{PATT,0x0001,0x0003,0x0007,0x000D,0x000F,0x0005,0x0008,0x0004},
{PATT,0x0006,0x000F,0x001F,0x0036,0x003F,0x0009,0x0016,0x0029},
{PATT,0x0018,0x003C,0x007E,0x00DB,0x00FF,0x005A,0x0081,0x0042},
{PATT,0x0060,0x00F0,0x01F8,0x036C,0x03FC,0x0090,0x0168,0x0294},
{PATT,0x080,0x03C0,0x07E0,0x0DB0,0x0FF0,0x05A0,0x0810,0x0420},
{PATT,0x0600,0x0F02,0x1F82,0x36C3,0x3FC3,0x0901,0x1680,0x2941},
{PATT,0x1802,0x3C01,0x7E03,0xDB06,0xFF0F,0x5A0B,0x810A,0x4201},
{PATT,0x6008,0xF024,0xF82F,0x6C3B,0xFC3F,0x901F,0x6808,0x9410},
{PATT,0x8020,0xC011,0xE03F,0xB06E,0xF0FF,0xA0BF,0x10A0,0x201B},
{PATT,0x0082,0x0244,0x82FE,0xC3BB,0xC3FF,0x01FF,0x8082,0x4101},
{PATT,0x0208,0x0110,0x03F8,0x06EC,0x0FFE,0x0BFA,0x0A0A,0x01B0},
{PATT,0x0820,0x2448,0x2FE8,0x3BB8,0x3FF8,0x1FF0,0x0820,0x1010},
{PATT,0x2080,0x1101,0x3F83,0x6EC3,0xFFE3,0xBFA0,0xA0A0,0x1B03},
{PATT,0x8200,0x4487,0xFE8F,0xBB8E,0xFF8F,0xFF03,0x8206,0x0103},
{PATT,0x0803,0x101F,0xF83F,0xEC39,0xFE3F,0xFA06,0x0A0D,0xB030},
{PATT,0x200F,0x487F,0xE8FF,0xB8E6,0xF8FF,0xF039,0x2066,0x1030},
{PATT,0x803C,0x01FF,0x83FF,0xC399,0xE3FF,0xA066,0xA0DB,0x0300},
{PATT,0x00F0,0x87FE,0x8FFF,0x8E67,0x8FFF,0x039C,0x0666,0x030C},
{PATT,0x03C0,0x1FF8,0x3FFC,0x399C,0x3FFC,0x0660,0x0DB0,0x300C},
{PATT,0x0F00,0x7FE0,0xFFF0,0xE670,0xFFF0,0x39C0,0x6660,0x30C0},
{PATT,0x3C00,0xFF80,0xFFC0,0x99C0,0xFFC0,0x6600,0xDB00,0x00C0},
{PATT,0xF000,0xFE00,0xFF00,0x6700,0xFF00,0x9C00,0x6600,0x0C00},
{PATT,0xC000,0xF800,0xFC00,0x9C00,0xFC00,0x6000,0xB000,0x0C00},
{PATT,0x0000,0xE000,0xF000,0x7000,0xF000,0xC000,0x6000,0xC000},
{PATT,0x0000,0x8000,0xC000,0xC000,0xC000,0x0000,0x0000,0xC000},
{PATT,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000},
{TERM,0,0,0,0,0,0,0,0},},

{ // 2:INVADER3
{TIME,25,0,0,0,0,0,0,0},
{PATT,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000},
{PATT,0x0000,0x0000,0x0001,0x0003,0x0003,0x0000,0x0001,0x0002},
{PATT,0x0001,0x0003,0x0007,0x000D,0x000F,0x0005,0x0008,0x0004},
{PATT,0x0006,0x000F,0x001F,0x0036,0x003F,0x0009,0x0016,0x0029},
{PATT,0x0018,0x003C,0x007E,0x00DB,0x00FF,0x005A,0x0081,0x0042},
{PATT,0x0060,0x00F0,0x01F8,0x036C,0x03FC,0x0090,0x0168,0x0294},
{PATT,0x0220,0x1144,0x0808,0x0410,0x3006,0x0410,0x0948,0x1224},
{PATT,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000},
{PATT,0x0000,0x0002,0x0002,0x0003,0x0003,0x0001,0x0000,0x0001},
{PATT,0x0002,0x0001,0x0003,0x0006,0x000F,0x000B,0x000A,0x0001},
{PATT,0x0008,0x0024,0x002F,0x003B,0x003F,0x001F,0x0008,0x0010},
{PATT,0x0020,0x0011,0x003F,0x006E,0x00FF,0x00BF,0x00A0,0x001B},
{PATT,0x0082,0x0244,0x02FE,0x03BB,0x03FF,0x01FF,0x0082,0x0101},
{PATT,0x0208,0x0110,0x03F8,0x06EC,0x0FFE,0x0BFA,0x0A0A,0x01B0},
{PATT,0x0220,0x1144,0x0808,0x0410,0x3006,0x0410,0x0948,0x1224},
{PATT,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000},
{PATT,0x0000,0x0001,0x0003,0x0003,0x0003,0x0000,0x0000,0x0003},
{PATT,0x0000,0x0007,0x000F,0x000E,0x000F,0x0003,0x0006,0x0003},
{PATT,0x0003,0x001F,0x003F,0x0039,0x003F,0x0006,0x000D,0x0030},
{PATT,0x000F,0x007F,0x00FF,0x00E6,0x00FF,0x0039,0x0066,0x0030},
{PATT,0x003C,0x01FF,0x03FF,0x0399,0x03FF,0x0066,0x00DB,0x0300},
{PATT,0x00F0,0x07FE,0x0FFF,0x0E67,0x0FFF,0x039C,0x0666,0x030C},
{PATT,0x0220,0x1144,0x0808,0x0410,0x3006,0x0410,0x0948,0x1224},
{PATT,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000},
{TERM,0,0,0,0,0,0,0,0},},

{ // 3:UFO_R
{TIME,4,0,0,0,0,0,0,0},
{PATT,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000},
{PATT,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000},
{PATT,0x0000,0x0000,0x0000,0x0001,0x0003,0x0000,0x0000,0x0000},
{PATT,0x0000,0x0001,0x0003,0x0006,0x000F,0x0003,0x0001,0x0000},
{PATT,0x0001,0x0007,0x000F,0x001B,0x003F,0x000E,0x0004,0x0000},
{PATT,0x0007,0x001F,0x003F,0x006D,0x00FF,0x0039,0x0010,0x0000},
{PATT,0x001F,0x007F,0x00FF,0x01B6,0x03FF,0x00E6,0x0040,0x0000},
{PATT,0x007E,0x01FF,0x03FF,0x06DB,0x0FFF,0x0399,0x0100,0x0000},
{PATT,0x01F8,0x07FE,0x0FFF,0x1B6D,0x3FFF,0x0E67,0x0402,0x0000},
{PATT,0x07E0,0x1FF8,0x3FFC,0x6DB6,0xFFFF,0x399C,0x1008,0x0000},
{PATT,0x1F80,0x7FE0,0xFFF0,0xB6D8,0xFFFC,0xE670,0x4020,0x0000},
{PATT,0x7E00,0xFF80,0xFFC0,0xDB60,0xFFF0,0x99C0,0x0080,0x0000},
{PATT,0xF800,0xFE00,0xFF00,0x6D80,0xFFC0,0x6700,0x0200,0x0000},
{PATT,0xE000,0xF800,0xFC00,0xB600,0xFF00,0x9C00,0x0800,0x0000},
{PATT,0x8000,0xE000,0xF000,0xD800,0xFC00,0x7000,0x2000,0x0000},
{PATT,0x0000,0x8000,0xC000,0x6000,0xF000,0xC000,0x8000,0x0000},
{PATT,0x0000,0x0000,0x0000,0x8000,0xC000,0x0000,0x0000,0x0000},
{PATT,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000},
{PATT,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000},
{TERM,0,0,0,0,0,0,0,0},},

{ // 4:UFO_R_B
{TIME,4,0,0,0,0,0,0,0},
{PATT,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000},
{PATT,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000},
{PATT,0x0000,0x0000,0x0000,0x0001,0x0003,0x0000,0x0000,0x0000},
{PATT,0x0000,0x0001,0x0003,0x0006,0x000F,0x0003,0x0001,0x0000},
{PATT,0x0001,0x0007,0x000F,0x001B,0x003F,0x000E,0x0004,0x0000},
{PATT,0x0007,0x001F,0x003F,0x006D,0x00FF,0x0039,0x0010,0x0000},
{PATT,0x001F,0x007F,0x00FF,0x01B6,0x03FF,0x00E6,0x0040,0x0000},
{PATT,0x007E,0x01FF,0x03FF,0x06DB,0x0FFF,0x0399,0x0100,0x0000},
{PATT,0x01F8,0x07FE,0x0FFF,0x1B6D,0x3FFF,0x0E67,0x0402,0x0000},
{PATT,0x07E0,0x1FF8,0x3FFC,0x6DB6,0xFFFF,0x399C,0x1008,0x0000},
{PATT,0x2228,0x9152,0x4AA4,0x2411,0x514A,0xA424,0x4952,0x9289},
{PATT,0x4914,0x24A9,0x1152,0xC824,0x2204,0x4953,0x9208,0x2426},
{PATT,0x2228,0x9152,0x4AA4,0x2411,0x514A,0xA424,0x4952,0x9289},
{PATT,0x4914,0x24A9,0x1152,0xC824,0x2204,0x4953,0x9208,0x2426},
{PATT,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000},
{TERM,0,0,0,0,0,0,0,0},},

{ // 5:UFO_L
{TIME,4,0,0,0,0,0,0,0},
{PATT,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000},
{PATT,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000},
{PATT,0x0000,0x0000,0x0000,0x8000,0xC000,0x0000,0x0000,0x0000},
{PATT,0x0000,0x8000,0xC000,0x6000,0xF000,0xC000,0x8000,0x0000},
{PATT,0x8000,0xE000,0xF000,0xD800,0xFC00,0x7000,0x2000,0x0000},
{PATT,0xE000,0xF800,0xFC00,0xB600,0xFF00,0x9C00,0x0800,0x0000},
{PATT,0xF800,0xFE00,0xFF00,0x6D80,0xFFC0,0x6700,0x0200,0x0000},
{PATT,0x7E00,0xFF80,0xFFC0,0xDB60,0xFFF0,0x99C0,0x0080,0x0000},
{PATT,0x1F80,0x7FE0,0xFFF0,0xB6D8,0xFFFC,0xE670,0x4020,0x0000},
{PATT,0x07E0,0x1FF8,0x3FFC,0x6DB6,0xFFFF,0x399C,0x1008,0x0000},
{PATT,0x01F8,0x07FE,0x0FFF,0x1B6D,0x3FFF,0x0E67,0x0402,0x0000},
{PATT,0x007E,0x01FF,0x03FF,0x06DB,0x0FFF,0x0399,0x0100,0x0000},
{PATT,0x001F,0x007F,0x00FF,0x01B6,0x03FF,0x00E6,0x0040,0x0000},
{PATT,0x0007,0x001F,0x003F,0x006D,0x00FF,0x0039,0x0010,0x0000},
{PATT,0x0001,0x0007,0x000F,0x001B,0x003F,0x000E,0x0004,0x0000},
{PATT,0x0000,0x0001,0x0003,0x0006,0x000F,0x0003,0x0001,0x0000},
{PATT,0x0000,0x0000,0x0000,0x0001,0x0003,0x0000,0x0000,0x0000},
{PATT,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000},
{PATT,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000},
{TERM,0,0,0,0,0,0,0,0},},

{ // 6:UFO_L_B
{TIME,4,0,0,0,0,0,0,0},
{PATT,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000},
{PATT,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000},
{PATT,0x0000,0x0000,0x0000,0x8000,0xC000,0x0000,0x0000,0x0000},
{PATT,0x0000,0x8000,0xC000,0x6000,0xF000,0xC000,0x8000,0x0000},
{PATT,0x8000,0xE000,0xF000,0xD800,0xFC00,0x7000,0x2000,0x0000},
{PATT,0xE000,0xF800,0xFC00,0xB600,0xFF00,0x9C00,0x0800,0x0000},
{PATT,0xF800,0xFE00,0xFF00,0x6D80,0xFFC0,0x6700,0x0200,0x0000},
{PATT,0x7E00,0xFF80,0xFFC0,0xDB60,0xFFF0,0x99C0,0x0080,0x0000},
{PATT,0x1F80,0x7FE0,0xFFF0,0xB6D8,0xFFFC,0xE670,0x4020,0x0000},
{PATT,0x07E0,0x1FF8,0x3FFC,0x6DB6,0xFFFF,0x399C,0x1008,0x0000},
{PATT,0x2228,0x9152,0x4AA4,0x2411,0x514A,0xA424,0x4952,0x9289},
{PATT,0x4914,0x24A9,0x1152,0xC824,0x2204,0x4953,0x9208,0x2426},
{PATT,0x2228,0x9152,0x4AA4,0x2411,0x514A,0xA424,0x4952,0x9289},
{PATT,0x4914,0x24A9,0x1152,0xC824,0x2204,0x4953,0x9208,0x2426},
{PATT,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000},
{TERM,0,0,0,0,0,0,0,0},},

{ // 7:P100
{TIME,6,0,0,0,0,0,0,0},
{PATT,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000},
{TIME,62,0,0,0,0,0,0,0},
{PATT,0x18C4,0x2526,0x2524,0x2524,0x2524,0x2524,0x18CE,0x0000},
{TIME,6,0,0,0,0,0,0,0},
{PATT,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000},
{TERM,0,0,0,0,0,0,0,0},},

{ // 8:P300
{TIME,6,0,0,0,0,0,0,0},
{PATT,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000},
{TIME,62,0,0,0,0,0,0,0},
{PATT,0x318C,0x4A52,0x4A50,0x4A4C,0x4A50,0x4A52,0x318C,0x0000},
{TIME,6,0,0,0,0,0,0,0},
{PATT,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000},
{TERM,0,0,0,0,0,0,0,0},},

};

#define INVADER1  0
#define INVADER2  1
#define INVADER3  2
#define UFO_R     3
#define UFO_R_B   4
#define UFO_L     5
#define UFO_L_B   6
#define P100      7
#define P300      8
#define PEND      99

const byte seq[] PROGMEM = {
  INVADER1,
  UFO_R,
  INVADER2,
  UFO_L,
  INVADER1,
  UFO_R,
  INVADER3,
  UFO_L_B,
  P100,
  
  INVADER1,
  UFO_R,
  INVADER2,
  UFO_L,
  INVADER1,
  UFO_R_B,
  P100,
  INVADER3,
  UFO_L,
  
  INVADER1,
  UFO_R,
  INVADER2,
  UFO_L,
  INVADER1,
  UFO_R,
  INVADER3,
  UFO_L_B,
  P300,
  PEND
};

static byte frame = 0;

void complex_pattern_init(){
  cnt = 0;
  frame = 0;
  period = 6;
  pattern = pgm_read_word_near (&seq[cnt]);
}
      

void invader1(){
  byte com;
  com = pgm_read_word_near (&BitMap[pattern][frame][0]);
  if (com == TIME){
    period = pgm_read_word_near (&BitMap[pattern][frame][1]);
    frame++;
    com = pgm_read_word_near (&BitMap[pattern][frame][0]);
  }
  if (com == TERM){
    cnt++;
    frame = 0;
    pattern = pgm_read_word_near (&seq[cnt]);
    if (pattern == PEND){
      cnt = 0;
      pattern = pgm_read_word_near (&seq[cnt]);
    }
    com = pgm_read_word_near (&BitMap[pattern][frame][0]);
  }
  if (com == PATT){
    for(byte line = 1; line < 9; line++) {
      uint16_t data = pgm_read_word_near (&BitMap[pattern][frame][line]);
      for (byte led=0; led<16; led++) {
        if (data & (1<<led)) {
          iLedSign.Set(led, line-1, 1);
        } else {
          iLedSign.Set(led, line-1, 0);
        }
      }
    }
    frame++;
  }
}


void invader(){
  icount++;
  if (icount >= period){
    icount = 0;
    invader1();
  }
}
