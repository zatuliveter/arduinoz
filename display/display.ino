#include <TM1637Display.h>

// Module connection pins (Digital Pins)
#define CLK 4
#define DIO 3

TM1637Display display(CLK, DIO);

void setup() {
  display.setBrightness(0x01);
}

void loop() {
  for(int i = 100; i > 0; i=i-2)
  {
    display.showNumberDec(i, false);
    delay(50);
  }  
}
