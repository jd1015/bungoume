


#ifndef gravity_h
#define gravity_h

typedef struct {
  int x;
  int y;
} Coordinate;

typedef struct {
  double x;
  double y;
} Coordinate32;

void gravity_init();
void gravity();


#endif
