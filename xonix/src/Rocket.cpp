#include "Arduino.h"
#include "Display.h"
#include "Common.h"
#include "PxMatrix.h"
#include "Rocket.h"

Rocket::Rocket(Display* display)
{
  x = random(5, pDisplay->MaxX-5);  
  y = random(5, pDisplay->MaxY-5);
  pDisplay = display;
  color = pDisplay->DefaultColors[random(0, 7)];
}

void Rocket::Draw(bool cls)
{
  if (cls == false)
    pDisplay->pMatrix->drawPixel(x, y, pDisplay->BlackColor);
  else
    pDisplay->pMatrix->drawPixel(x, y, color); 
}

void Rocket::Move()
{
  
  pinMode(0, OUTPUT);
  pinMode(3, INPUT);
  digitalWrite(0, 0);
  int xv = analogRead(A0);
  Serial.print("x=");
  Serial.print(xv);
    
  pinMode(0, INPUT);
  pinMode(3, OUTPUT);
  digitalWrite(3, 0);
  int yv = analogRead(A0);
  Serial.print("y=");
  Serial.println(yv);

  if (yv < 700) y = y + 1;    
  if (yv > 880) y = y - 1;

  if (xv < 800) x = x + 1;    
  if (xv > 920) x = x - 1;
}
