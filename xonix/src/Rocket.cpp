#include "Arduino.h"
#include "Display.h"
#include "Common.h"
#include "PxMatrix.h"
#include "Rocket.h"

Rocket::Rocket(Display* display)
{
  y = random(5, pDisplay->MaxY-5);
  pDisplay = display;
  color = pDisplay->DefaultColors[random(0, 7)];
}

void Rocket::Draw(bool cls)
{
  if (cls == false)
    pDisplay->pMatrix->drawLine(0, y, 0, y+5, pDisplay->BlackColor);
  else
    pDisplay->pMatrix->drawLine(0, y, 0, y+5, color); 
}

void Rocket::Move()
{
  int val = analogRead(A0);
  Serial.println(val);
  if (val < 200) y = y + 1;    
  if (val > 700) y = y - 1;
}
