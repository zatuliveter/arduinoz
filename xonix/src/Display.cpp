
#include "Arduino.h"
#include "Adafruit_GFX.h"
#include "PxMatrix.h"
#include "Common.h"
#include "Display.h"

#define P_LAT 16
#define P_A 5
#define P_B 4
#define P_C 15
#define P_D 12
#define P_OE 2


byte Display::MaxX = 64;
byte Display::MaxY = 32;

Display::Display() 
{
  pMatrix = new PxMATRIX(MaxX, MaxY, P_LAT, P_OE, P_A, P_B, P_C, P_D);

  // Define your display layout here, e.g. 1/8 step
  pMatrix->begin(16);
  pMatrix->setFastUpdate(true);
  pMatrix->setRotation(0); // we don't wrap text so it scrolls nicely  
  pMatrix->clearDisplay();   

  this->EnableUpdate(true); 

  // Some standard colors
  uint16_t myRED = this->pMatrix->color565(255, 0, 0);
  uint16_t myGREEN = this->pMatrix->color565(0, 255, 0);
  uint16_t myBLUE = this->pMatrix->color565(0, 0, 255);
  uint16_t myWHITE = this->pMatrix->color565(255, 255, 255);
  uint16_t myYELLOW = this->pMatrix->color565(255, 255, 0);
  uint16_t myCYAN = this->pMatrix->color565(0, 255, 255);
  uint16_t myMAGENTA = this->pMatrix->color565(255, 0, 255);
  uint16_t myBLACK = this->pMatrix->color565(0, 0, 0);

  DefaultColors[0] = myRED;
  DefaultColors[1] = myGREEN;
  DefaultColors[2] = myBLUE;
  DefaultColors[3] = myWHITE;
  DefaultColors[4] = myYELLOW;
  DefaultColors[5] = myCYAN;
  DefaultColors[6] = myMAGENTA;

  BlackColor = myBLACK;
};

#ifdef ESP8266
  // ISR for display refresh
  void Display::Updater()
  {
    // This defines the 'on' time of the display is us. The larger this number,
    // the brighter the display. If too large the ESP will crash
    //10-50 is usually fine
    pMatrix->display(75);
  }

  void Display::EnableUpdate(bool is_enable)
  {
    if (is_enable)
      pDisplayTicker->attach(0.002, std::bind(&Display::Updater, this));
    else
      pDisplayTicker->detach();
  }
#endif
