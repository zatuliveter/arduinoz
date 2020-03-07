// REQUIRES the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - RGB matrix Panel Library: https://github.com/2dom/PxMatrix
// - Adafruit_GFX Library: https://github.com/adafruit/Adafruit-GFX-Library
// - esp8266 library (nodemcu) found at https://github.com/esp8266/Arduino
// - package_esp8266com_index.json found at http://arduino.esp8266.com/stable/package_esp8266com_index.json
// Find All "Great Projects" Videos : https://www.youtube.com/channel/UCCC8DuqicBtP3A_aC53HYDQ/videos

#include "Arduino.h"
//#include <ESP8266WiFi.h>
//WiFiClient client;
// test
#include <Adafruit_GFX.h>
//#include <FreeMonoBold12pt7b.h>
//#include <kongtext4pt7b.h>
#include <PxMatrix.h>
#include <Ticker.h>
Ticker display_ticker;

#define P_LAT 16
#define P_A 5
#define P_B 4
#define P_C 15
#define P_D 12
#define P_OE 2


//PxMATRIX display(matrix_width,matrix_height,P_LAT, P_OE,P_A,P_B,P_C);
PxMATRIX display(64,32,P_LAT, P_OE,P_A,P_B,P_C,P_D);

// Some standard colors
uint16_t myRED = display.color565(255, 0, 0);
uint16_t myGREEN = display.color565(0, 255, 0);
uint16_t myBLUE = display.color565(0, 0, 255);
uint16_t myWHITE = display.color565(255, 255, 255);
uint16_t myYELLOW = display.color565(255, 255, 0);
uint16_t myCYAN = display.color565(0, 255, 255);
uint16_t myMAGENTA = display.color565(255, 0, 255);
uint16_t myBLACK = display.color565(0, 0, 0);

uint16_t myCOLORS[8]={myRED,myGREEN,myBLUE,myWHITE,myYELLOW,myCYAN,myMAGENTA,myBLACK};


#ifdef ESP8266
// ISR for display refresh
void display_updater()
{
  // This defines the 'on' time of the display is us. The larger this number,
  // the brighter the display. If too large the ESP will crash
  //10-50 is usually fine
  display.display(75);
}
#endif

void display_update_enable(bool is_enable)
{
#ifdef ESP8266
  if (is_enable)
    display_ticker.attach(0.002, display_updater);
  else
    display_ticker.detach();
#endif
}


int maxX = 64;
int maxY = 32;

struct Rocket {
  byte y;
  int color;

  int my;

  Rocket()
  {
    y = random(5, maxY-5);
    color = myCOLORS[random(0, 7)];
  }

  void Draw(bool cls)
  {
    if (cls == false)
      display.drawLine(0, y, 0, y+5, myBLACK);
    else
      display.drawLine(0, y, 0, y+5, color); 
  }

  void Move()
  {
    int val = analogRead(A0);
    Serial.println(val);
    if (val < 200) y = y + 1;    
    if (val > 700) y = y - 1;
  }
};

struct Ball {
  byte x;
  byte y;
  int color;

  int mx;
  int my;
  
  Ball()
  {    
    x = random(2, maxX-1);
    y = random(2, maxY-1);
    mx = GetRandomDirection();
    my = GetRandomDirection();
    color = myCOLORS[random(0, 7)];
  }

  int GetRandomDirection()
  {
    if (random(0, 2) > 0) return random(1, 3);
    return -random(1, 3);
  }
  
  void Move()
  {
    x = x + mx;
    y = y + my;
    
    if ( x <= 0 || x >= maxX - 1) { mx = -mx; }    
    if ( y <= 0 || y >= maxY - 1) { my = -my; }
  }

  void Draw(bool cls)
  {
    if (cls == false)
      display.drawPixel(x, y, myBLACK);
    else
      display.drawPixel(x, y, color);    
  }
};


void setup() {
  Serial.begin(115200);
  
  // Define your display layout here, e.g. 1/8 step
  display.begin(16);

  display.setFastUpdate(true);
  display.setRotation(0); // we don't wrap text so it scrolls nicely
  
  display.clearDisplay();  
  
  //display.print("WiFi OK"); 
  display_update_enable(true); 

  //pinMode(10, INPUT);

}


const int ballCount = 3;
Ball ball[ballCount];

Rocket rocket;

void loop() {

  for(int i = 0; i < ballCount; i++)
  {
    ball[i].Draw(false);
    ball[i].Move();
    ball[i].Draw(true);
  }
  
  rocket.Draw(false);
  rocket.Move();
  rocket.Draw(true);

  //display.drawPixel(x, y, display.color565(250, 0, 0));
  //display.fillCircle(x, y, 1, display.color565(r, g, b));
  //display.drawRect(x, y, 1, 1, display.color565(r, g, b));
  
  delay(50);
}