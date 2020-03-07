#include <MD_MAX72xx.h>
#include <TM1637Display.h>

#define HARDWARE_TYPE MD_MAX72XX::PAROLA_HW
#define MAX_DEVICES  4

const uint8_t CLK_PIN = 13;
const uint8_t DATA_PIN = 11;
const uint8_t CS_PIN = 10;

const int axisX=A0;
const int axisY=A1;
const int axisZ=A2;
int xval, yval, zval = 0;
int x, y = 5;

MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

int minX = 0;
int maxX = 31;
int minY = 0;
int maxY = 7;

void setup() {  
 
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(axisZ, INPUT_PULLUP);

  mx.begin();
  mx.clear();
  mx.control(MD_MAX72XX::INTENSITY, 1);
}


void loop() 
{
  xval = analogRead(axisX);
  yval = analogRead(axisY);

  mx.setPoint(y, x, false);
  
  if (xval < 900) x = x + 1;
  if (xval > 100) x = x - 1;
  if (yval < 900) y = y - 1;
  if (yval > 100) y = y + 1;

  if (x > maxX) x = maxX;  
  if (y > maxY) y = maxY;
  if (x < minX) x = minX;
  if (y < minY) y = minY;
  
  mx.setPoint(y, x, true);
 
  delay(50);  
}
