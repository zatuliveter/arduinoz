// Adafruit ILI9341 v.1.5.6
#include "Adafruit_ILI9341.h"

// PMS Library, from arduino library manager.
// Mariusz Kacki 1.1.0 
// https://github.com/fu-hsi/pms
#include "PMS.h"

#include <SoftwareSerial.h>

// MH-Z19 Arduino library, v.1.5.1
// Jonathan Dempsey
// https://github.com/WifWaf/MH-Z19
#include "MHZ19.h"   

PMS pms(Serial);
PMS::DATA data;
int pm1 = 0;
int pm25 = 0;
int pm10 = 0;

#define TFT_DC 9
#define TFT_CS 10
// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

#define MHZ_RX_PIN 4 // tx on mh-z19
#define MHZ_TX_PIN 5 // rx on mh-z19    
SoftwareSerial mhzSerial(MHZ_RX_PIN, MHZ_TX_PIN);
MHZ19 mhz; 
int co2 = 0;
int temp = 0;

void setup()
{
  // PMS Sensor Config:
  Serial.begin(9600);

  // TFT Display Config:
  tft.begin();
  tft.fillScreen(ILI9341_BLACK);  

  // MH-Z19 CO2 Sensor Config:
  mhzSerial.begin(9600);
  mhz.begin(mhzSerial); 
  mhz.autoCalibration();   
}

unsigned long getDataTimer = 0;

void loop()
{
  if (pms.read(data))
  {
    pm1  = data.PM_AE_UG_1_0;    
    pm25 = data.PM_AE_UG_2_5;    
    pm10 = data.PM_AE_UG_10_0;
  }  
  
  
  if (millis() - getDataTimer >= 2000)
  {
    co2 = mhz.getCO2();
    temp = mhz.getTemperature();
    
    displayData();    
    
    getDataTimer = millis();
  }
}

void displayData()
{
  tft.setRotation(3);
  tft.setCursor(0, 0);
  tft.setTextColor(ILI9341_RED, ILI9341_BLACK); 
  tft.setTextSize(4);
  
  tft.print("PM 1.0:  ");
  tft.print(pm1);
  tft.println(" "); // previous numbers cleanum
  
  tft.print("PM 2.5:  ");
  tft.print(pm25);
  tft.println(" ");
  
  tft.print("PM 10.0: ");
  tft.print(pm10);
  tft.println(" ");
  
  tft.print("CO2: ");
  tft.print(co2);
  tft.println(" ");
  
  tft.print("Temp: ");
  tft.print(temp);
  tft.println(" ");
}
