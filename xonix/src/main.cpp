// REQUIRES the following Arduino libraries:
// - Adafruit GFX Library by Adafruit: https://github.com/adafruit/Adafruit-GFX-Library
// - PxMatrix LED MATRIX library by Dominic Buchstaller: https://github.com/2dom/PxMatrix

#include "Arduino.h"
#include "Display.h"
#include "Ball.h"
#include "Rocket.h"

Display* pDisplay;
Rocket* pRocket;

const int ballCount = 3;
Ball* pBalls[ballCount];

void setup() {
  pRocket = new Rocket(pDisplay);

  for(int i=0; i<ballCount; i++)
  {
    pBalls[i] = new Ball(pDisplay);
  }

  Serial.begin(115200);
}

void loop() {

  for(int i = 0; i < ballCount; i++)
  {
    pBalls[i]->Draw(false);
    pBalls[i]->Move();
    pBalls[i]->Draw(true);
  }
  
  pRocket->Draw(false);
  pRocket->Move();
  pRocket->Draw(true);

  // display.drawPixel(x, y, display.color565(250, 0, 0));
  // display.fillCircle(x, y, 1, display.color565(r, g, b));
  // display.drawRect(x, y, 1, 1, display.color565(r, g, b));
  
  delay(50);
}