#include "Arduino.h"
#include "PxMatrix.h"
#include "Ticker.h"

#ifndef DISPLAY_h
#define DISPLAY_h

struct Display {
public:
  static byte MaxX;
  static byte MaxY;
  static int objectCount;
  
  uint16_t DefaultColors[7];
  uint16_t BlackColor;
  PxMATRIX* pMatrix;

  Display();

private:
  Ticker* pDisplayTicker;

#ifdef ESP8266
  void Updater();
  void EnableUpdate(bool is_enable);
#endif
};

#endif