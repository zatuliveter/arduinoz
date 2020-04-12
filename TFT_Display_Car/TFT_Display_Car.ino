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
 

void drawWheel(int x, int y) { 
  int wheelsColor = tft.color565(150, 150, 150);
  int tiresColor = tft.color565(110, 110, 110);
 

  tft.drawCircle(x, y, 9, wheelsColor); 
  tft.fillCircle(x, y, 8, tiresColor); 
  tft.fillCircle(x, y, 5, wheelsColor);
}

void drawBody() {
  tft.drawLine(29, 40, 29, 110, ST77XX_BLUE);
  tft.drawLine(29, 40, 65, 40, ST77XX_BLUE);
  tft.drawLine(65, 40, 65, 80, ST77XX_BLUE);
  tft.drawLine(65, 80, 55, 95, ST77XX_BLUE);
  tft.drawLine(55, 95, 55, 110, ST77XX_BLUE);
  tft.drawLine(55, 110, 30, 110, ST77XX_BLUE);
}

void drawDetails() {
  tft.drawSquare
}

void loop() {  
  tft.fillScreen(ST77XX_BLACK);
  
  int roadColor = tft.color565(100, 100, 100);    
  tft.drawLine(20, 0, 20, 160, roadColor); //дорога   

  drawWheel(20, 50);
  drawWheel(20, 100);
  drawBody();
  
  //tft.drawLine() //корпус машины 
  
  //tft.drawLine(20, 140, 20, 80, ST77XX_RED);
  //tft.drawLine(20, 140, 90, 140, ST77XX_RED);
  //tft.drawLine(90, 140, 90, 80, ST77XX_RED);
  //
  //tft.drawLine(20, 80, 55, 30, ST77XX_BLUE);
  //tft.drawLine(55, 30, 90, 80, ST77XX_BLUE);

  //tft.fillTriangle(20, 80, 55, 30, 90, 80, ST77XX_BLUE);
  //tft.drawRect(20, 140, 90, 80, ST77XX_YELLOW);
  
  delay(1000000);
}
