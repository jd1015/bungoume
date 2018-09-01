/*****************************************/
// bounce ball for Titchaino and ikkeiplexing shield
// by ikkei 2014.07.08
// reviewed 2018.02.01
// 

#include <arduino.h>
#include <ikkeiplexing.h>

#include "bounce_balls.h"
#include "gravity.h"

static ikkeiplexing iLedSign;


static const byte NUM_X = 16;
static const byte NUM_Y = 8;

//const Coordinate NUM = { 16, 8 };
const Coordinate MAX = { 15, 7 };

static byte plane[NUM_X][NUM_Y];
static byte backcolor = 0;
static byte ballcolor = 1;



void bounce_balls_init(){
  iLedSign.Clear();
  for (byte x=0; x<=MAX.x; x++){
    for (byte y=0; y<=MAX.y; y++){
        plane[x][y] = backcolor;
    }
  }
}

void bounce_balls(){
#define SENS 1  // Sensitivity
#define MAG 1024  // Magnification
#define REF1 3  // Reflectance is REF1/REF2
#define REF2 4

  static Coordinate previous[10] = {{0,0}};
  static Coordinate  present[10] = {{0,0}};
  static Coordinate acceleration = {-40, 0};
  static Coordinate velocity[10] = {{0,0}};
  static Coordinate position[10] = {
    {17000,    0},
    {20000, 1200},
    {30000, 2400},
    {20000, 3400},
    {18000, 1200},
    {19000, 2400},
    {17000, 2048},
    {18000, 3072},
    {19000,    0},
    {30000, 1024},
    };
  static byte time[10] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
  
  for(byte i=0; i<8; i++){
    time[i]--;
    if (time[i] == 0){
      time[i] = random(40,70);
      position[i].x = random(16000,40000);
      velocity[i].x = random(-1000,500);
      velocity[i].y = random(-500,500);
    }
  
    // integrating acceleration makes velocity
    velocity[i].x += acceleration.x;
    velocity[i].y += acceleration.y;

    // integrating velocity makes position
    position[i].x += velocity[i].x;
    position[i].y += velocity[i].y;
  
    // reflection ( reverse velocity )
    // 0 < x1 < X_MAX
    if ( position[i].x > MAG * MAX.x){
      position[i].x = MAG * MAX.x;
      velocity[i].x = -( velocity[i].x * REF1 ) / REF2;
    }else if ( position[i].x < 0 ){
      position[i].x = 0;
      velocity[i].x = -( velocity[i].x * REF1 ) / REF2;
    }
    // 0 < y1 < Y_MAX
    if ( position[i].y > MAG * MAX.y){
      position[i].y = MAG * MAX.y;
      velocity[i].y = -( velocity[i].y * REF1 ) / REF2;
    }else if ( position[i].y < 0 ){
      position[i].y = 0;
      velocity[i].y = -( velocity[i].y * REF1 ) / REF2;
    }

    present[i].x = position[i].x / MAG;
    present[i].y = position[i].y / MAG;
  
    // display limitter
    constrain(present[i].x, 0, MAX.x);
    constrain(present[i].y, 0, MAX.y);

    // turn off the last position
    plane[ previous[i].x ][ previous[i].y ] = backcolor;
    
    // turn on the next position
    plane[  present[i].x ][  present[i].y ] = ballcolor;
    
    // store last position
    previous[i].x = present[i].x;
    previous[i].y = present[i].y;

  }    
  for (byte x = 0; x <= MAX.x; x++){
    for (byte y = 0; y <= MAX.y; y++){
        iLedSign.Set(x, y, plane[x][y]);
    }
  }
   
}
