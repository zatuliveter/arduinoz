#include "Arduino.h"
#include "Display.h"
#include "Common.h"
#include "Ball.h"

Ball::Ball(Display* display)
{    
  x = random(2, Display::MaxX-1);
  y = random(2, Display::MaxY-1);
  mx = GetRandomDirection();
  my = GetRandomDirection();
  pDisplay = display;
  color = pDisplay->DefaultColors[random(0, 7)];
};

void Ball::Move()
{
  x = x + mx;
  y = y + my;
  
  if ( x <= 0 || x >= Display::MaxX - 1) { mx = -mx; }    
  if ( y <= 0 || y >= Display::MaxY - 1) { my = -my; }
};

void Ball::Draw(bool cls)
{
  if (cls == false)
    pDisplay->pMatrix->drawPixel(x, y, pDisplay->BlackColor);
  else
    pDisplay->pMatrix->drawPixel(x, y, color);    
};
