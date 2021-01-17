
#include <Adafruit_GFX.h>  
#include <SPI.h>

#define TFT_CS        10
#define TFT_RST       -1 // Or set to -1 and connect to Arduino RESET pin
#define TFT_DC         8

void setup(void) {  
  tft.initR(INITR_GREENTAB);
}

void loop() {  
  tft.fillScreen(ST77XX_BLACK);
  testLines();
  
  //tft.drawLine(0, 0, 100, 50, ST77XX_BLUE);

  //tft.drawLine(X1, Y1, X2, Y2, COLOR);
  
  //tft.drawLine(20, 140, 20, 80, ST77XX_RED);
  //tft.drawLine(20, 140, 90, 140, ST77XX_RED);
  //tft.drawLine(90, 140, 90, 80, ST77XX_RED);
  
  tft.drawLine(90, 80, 20, 80, ST77XX_BLUE);
  tft.drawLine(20, 80, 55, 30, ST77XX_BLUE);
  tft.drawLine(55, 30, 90, 80, ST77XX_BLUE);

  tft.fillTriangle(22, 78, 55, 32, 88, 78, ST77XX_RED);
  //tft.fillRect(20, 80, 90, 140, ST77XX_RED);
  
  delay(1000000);
}

void testLines()
{
  float i = 0;
  while(true) 
  {
    int x = sin(i) * 64 + 64;
    int y = cos(i*2.2) * 80 + 80;
    int x1 = sin(i*3.3) * 64 + 64;
    int y1 = cos(i*4.4) * 80 + 80;

    uint16_t color = 
       
                   int(i*9)%155 + 100, 
                   int(i*41)%155 + 100
                  );
    
    
    i = i + 0.0030 ;
  }
}
