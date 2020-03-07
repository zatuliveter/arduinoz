#include "LedControl.h"
#include "DHT.h"

int CLK = 10;
int DIN = 8;
int CS = 9;

LedControl lc = LedControl(DIN, CLK, CS, 1);

DHT dht(2, DHT11);

void setup() 
{
  dht.begin();
   
  lc.shutdown(0,false);
  lc.setIntensity(0, 4);
  lc.clearDisplay(0);
  
  Serial.begin(9600);
}

void loop() 
{   
  int h = dht.readHumidity();
  int t = dht.readTemperature();

  int t10 = t / 10;
  int t1 = t - t10 * 10;
    
  lc.setDigit(0, 6, t10, false);
  lc.setDigit(0, 5, t1, false);
  lc.setRow(0, 4, B01100011); // отображение символа градуса

  int h10 = h / 10;
  int h1 = h - h10 * 10;
  
  lc.setDigit(0, 2, h10, false);
  lc.setDigit(0, 1, h1, false);    
  lc.setRow(0, 0, B00010111); // отображение символа влажности

  delay(500);
}
