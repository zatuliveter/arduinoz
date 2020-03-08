#include "Arduino.h"
#include "Display.h"
#include "Common.h"
#include "PxMatrix.h"
#include "Display.h"

#ifndef Rocket_h
#define Rocket_h

struct Rocket 
{
private:  
  byte y;
  int color;
  int my;

  Display* pDisplay;

public:
  Rocket(Display* display);
  void Draw(bool cls);
  void Move();
};

#endif