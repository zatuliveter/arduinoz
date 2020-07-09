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
  mx.setPoint(1, 1, true);
  
   //drawhead(1, 0);
   //drawear(1, 22);
   //drawear(0, 10);
   delay(350);    
}

void drawhead(int x, int y)
{
  mx.setPoint(x + 5, y + 5, true);
  mx.setPoint(x + 5, y + 4, true);
  mx.setPoint(x + 5, y + 3, true);
  mx.setPoint(x + 4, y + 2, true);
  mx.setPoint(x + 3, y + 2, true);
  mx.setPoint(x + 2, y + 2, true);
  mx.setPoint(x + 1, y + 3, true);
  mx.setPoint(x + 1, y + 4, true);
  mx.setPoint(x + 1, y + 5, true);
  mx.setPoint(x + 3, y + 6, true);
  mx.setPoint(x + 4, y + 6, true);
  mx.setPoint(x + 2, y + 6, true);
}

void drawear(int x, int y)
{
  mx.setPoint(x + 5, y + 5, true);
  mx.setPoint(x + 6, y + 6, true);
  mx.setPoint(x + 3, y + 5, true);
}
   
