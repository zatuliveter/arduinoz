// Adafruit ILI9341 v.1.5.6
#include "Adafruit_ILI9341.h"

// PMS Library, from arduino library manager.
// Mariusz Kacki 1.1.0 
// https://github.com/fu-hsi/pms
#include "PMS.h"

#include <SoftwareSerial.h>


SoftwareSerial pmsSerial(2, 3);
 
PMS pms(pmsSerial);
PMS::DATA data;


#define TFT_DC 9
#define TFT_CS 10
// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);


void setup()
{
  // our debugging output
  Serial.begin(115200);
 
  // sensor baud rate is 9600
  pmsSerial.begin(9600);
  
  tft.begin();
  tft.fillScreen(ILI9341_BLACK);  
}

void loop()
{
  if (pms.read(data))
  {
    printToSerial();
    displayData();
  }  
}

void displayData()
{
  tft.setRotation(3);
  tft.setCursor(0, 0);
  //tft.setTextColor(ILI9341_RED);
  tft.setTextColor(ILI9341_RED, ILI9341_BLACK); 
  tft.setTextSize(4);
  
  tft.print("PM 1.0:  ");
  tft.print(data.PM_AE_UG_1_0);
  tft.println("  "); // previous numbers cleanum
  
  tft.print("PM 2.5:  ");
  tft.print(data.PM_AE_UG_2_5);
  tft.println("  "); // previous numbers cleanum
  
  tft.print("PM 10.0: ");
  tft.print(data.PM_AE_UG_10_0);
  tft.println("  "); // previous numbers cleanum
}

void printToSerial()
{
  Serial.print("PM 1.0 (ug/m3): ");
  Serial.println(data.PM_AE_UG_1_0);
  
  Serial.print("PM 2.5 (ug/m3): ");
  Serial.println(data.PM_AE_UG_2_5);
  
  Serial.print("PM 10.0 (ug/m3): ");
  Serial.println(data.PM_AE_UG_10_0);
  
  Serial.println();  
}
