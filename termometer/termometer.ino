#include "DHT.h"
#include <Arduino.h>
#include <TM1637Display.h>

DHT dht(2, DHT11);

#define CLK 4
#define DIO 3
TM1637Display display(CLK, DIO);

void setup() 
{
  dht.begin();
  Serial.begin(9600);
  display.setBrightness(0x01);
}

void loop() 
{
  float t = dht.readTemperature(); 
  display.showNumberDec(int(t), false);
  delay(250);
}
