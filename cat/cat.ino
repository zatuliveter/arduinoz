#include <MD_MAX72xx.h>
#include <TM1637Display.h>

#define HARDWARE_TYPE MD_MAX72XX::PAROLA_HW
#define MAX_DEVICES  4

const uint8_t CLK_PIN = 13;
const uint8_t DATA_PIN = 11;
const uint8_t CS_PIN = 10;

//const uint8_t IO_PIN = 8;

MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);


void setup() {  
  mx.begin();
  mx.clear();
  mx.control(MD_MAX72XX::INTENSITY, 1);
}


void loop() 
{
   drawhead(-2, 3);
   drawear(-3, 7);
   drawear(-3, 0);
   draweye(4, 6);
   draweye(4, 11);
   delay(350);    
}

void drawhead(int x, int y)
{
  mx.setPoint(x + 5, y + 10, true);
  mx.setPoint(x + 5, y + 9, true);
  mx.setPoint(x + 5, y + 8, true);
  mx.setPoint(x + 5, y + 7, true);
  mx.setPoint(x + 5, y + 6, true);
  mx.setPoint(x + 5, y + 5, true);
  mx.setPoint(x + 5, y + 4, true);
  mx.setPoint(x + 5, y + 3, true);
  mx.setPoint(x + 5, y + 2, true);
  mx.setPoint(x + 5, y + 1, true);
  
  mx.setPoint(x + 6, y + 0, true);
  mx.setPoint(x + 7, y + 0, true);
  mx.setPoint(x + 8, y + 0, true);
  
  mx.setPoint(x + 9, y + 10, true);
  mx.setPoint(x + 9, y + 9, true);
  mx.setPoint(x + 9, y + 8, true);
  mx.setPoint(x + 9, y + 7, true);
  mx.setPoint(x + 9, y + 6, true);
  mx.setPoint(x + 9, y + 5, true);
  mx.setPoint(x + 9, y + 4, true);
  mx.setPoint(x + 9, y + 3, true);
  mx.setPoint(x + 9, y + 2, true);
  mx.setPoint(x + 9, y + 1, true);
  
  mx.setPoint(x + 6, y + 11, true);
  mx.setPoint(x + 7, y + 11, true);
  mx.setPoint(x + 8, y + 11, true);
}

void drawear(int x, int y)
{
  mx.setPoint(x + 5, y + 4, true);
  mx.setPoint(x + 4, y + 5, true);
  mx.setPoint(x + 5, y + 6, true);
  mx.setPoint(x + 5, y + 5, true);
}

void draweye(int x, int y)
{
  mx.setPoint(x, y, true);
  mx.setPoint(x + 1, y, true);
  mx.setPoint(x + 2, y, true);
}
  
   
