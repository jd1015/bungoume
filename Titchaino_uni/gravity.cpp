/*
  For Titchaino uni

  bounce for ikkeiplexing shield by ikkei
  http://blog.goo.ne.jp/jh3kxm
  
  History:
        2010-12-11 - V1.0 bounce by ikkei
        reviewed 2018.02.01
        
*/

#include <arduino.h>
#include <MsTimer2.h>
#include <ikkeiplexing.h>
#include "gravity.h"


ikkeiplexing iLedSign;

#define AX 5      // for Titchaino uni
#define AY 4      // for Titchaino uni
#define AVE 8 // averaging number of times
#define REF1 3  // Reflectance is REF1/REF2
#define REF2 4
#define MAG 1024  // Magnification
#define FRAME 1


uint8_t spt = 0;  // averaging pointer
uint8_t apt = 0;

const  Coordinate MAX = { 15, 7 };
static Coordinate previous = {1, 1}; // previous position
static Coordinate  present = {1, 1}; // present position
static Coordinate acceleration_in[AVE]; // averaging buffer
static Coordinate acceleration;
static Coordinate velocity;
static Coordinate position;
static Coordinate offset;
static Coordinate32 adj;



void gravity(){
  // averaging acceleration sensor signal
  acceleration_in[ spt ].x = analogRead( AX ) - offset.x;
  acceleration_in[ spt ].y = analogRead( AY ) - offset.y;
  spt++;
  if ( spt >= AVE ){
    spt = 0;
  }
  acceleration.x = 0;
  acceleration.y = 0;
  for (byte i=0; i < AVE; i++){
    acceleration.x +=  acceleration_in[ i ].x;
    acceleration.y +=  acceleration_in[ i ].y;
  }
  acceleration.x /= AVE;
  acceleration.y /= AVE;
 
  // integrating acceleration makes velocity
  velocity.x +=  acceleration.x;
  velocity.y += -acceleration.y;
  
  // integrating velocity makes position
  position.x += velocity.x;
  position.y += velocity.y;
  
  // reflection ( reverse velocity )
  // 0 < x < MAX.x
  if ( position.x >= MAG * MAX.x){
    position.x = MAG * MAX.x - 1;
    velocity.x = -( velocity.x * REF1 ) / REF2;
  }else if ( position.x < MAG ){
    position.x = MAG;
    velocity.x = -( velocity.x * REF1 ) / REF2;
  }
  // 0 < y < MAX.y
  if ( position.y >= MAG * MAX.y){
    position.y = MAG * MAX.y - 1;
    velocity.y = -( velocity.y * REF1 ) / REF2;
  }else if ( position.y < MAG ){
    position.y = MAG;
    velocity.y = -( velocity.y * REF1 ) / REF2;
  }

  present.x = position.x / MAG;
  present.y = position.y / MAG;

  // display limitter
  constrain(present.x, 1, MAX.x - 1);
  constrain(present.y, 1, MAX.y - 1);

  // turn off the last position
  iLedSign.Set(previous.x,    previous.y,    0);
  iLedSign.Set(previous.x +1, previous.y,    0);
  iLedSign.Set(previous.x -1, previous.y,    0);
  iLedSign.Set(previous.x,    previous.y +1, 0);
  iLedSign.Set(previous.x,    previous.y -1, 0);
  
  // turn on the next position
  iLedSign.Set(present.x,    present.y,    1);
  iLedSign.Set(present.x +1, present.y,    1);
  iLedSign.Set(present.x -1, present.y,    1);
  iLedSign.Set(present.x,    present.y +1, 1);
  iLedSign.Set(present.x,    present.y -1, 1);
  
  // store last position
  previous.x = present.x;
  previous.y = present.y;
}

void gravity_init(){
  iLedSign.Clear();
  offset.x = analogRead( AX );
  offset.y = analogRead( AY );
  position.x = 1;
  position.y = 1;
}




