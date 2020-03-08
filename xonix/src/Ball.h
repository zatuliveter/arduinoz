#include "Arduino.h"
#include "Display.h"

#ifndef Ball_h
#define Ball_h

struct Ball {
private:
  byte x;
  byte y;
  int color;

  int mx;
  int my;

  Display* pDisplay;

public: 
  Ball(Display* display);
  void Move();
  void Draw(bool cls);
};

#endif