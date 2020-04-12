/*
 * Тест для нашего 1.8" монитора 128*160 точек
 * Заметки: экран работает если только подключить все контакты, 
 *   причем 11-й и 13-й явно не используются, а без них экран не работает.
 * #define TFT_CS        10
   #define TFT_RST       -1 // Or set to -1 and connect to Arduino RESET pin
   #define TFT_DC         8
   #define TFT_MOSI 11  // Data out
   #define TFT_SCLK 13  // Clock out
 */
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <SPI.h>

#define TFT_CS        10
#define TFT_RST       -1 // Or set to -1 and connect to Arduino RESET pin
#define TFT_DC         8

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

void setup(void) {  
  tft.initR(INITR_GREENTAB);
}

void loop() {  
  tft.fillScreen(ST77XX_BLACK);
  
  //tft.drawLine(0, 0, 100, 50, ST77XX_BLUE);

  //tft.drawLine(X1, Y1, X2, Y2, COLOR);  
  tft.drawLine(20, 140, 20, 80, ST77XX_RED);
  tft.drawLine(20, 140, 90, 140, ST77XX_RED);
  tft.drawLine(90, 140, 90, 80, ST77XX_RED);
  tft.drawLine(90, 80, 20, 80, ST77XX_BLUE);
  tft.drawLine(20, 80, 55, 30, ST77XX_BLUE);
  tft.drawLine(55, 30, 90, 80, ST77XX_BLUE);
  tft.fillTriangle(20, 80, 55, 30, 90, 80, ST77XX_BLUE);
  tft.drawRect(20, 140, 90, 80, ST77XX_YELLOW);
  
  delay(1000000);
}
