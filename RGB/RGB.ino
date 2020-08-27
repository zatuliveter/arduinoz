#include <FastLED.h>

#define LED_PIN 13
#define LED_COUNT 72

CRGB strip[LED_COUNT];

void setup ()  {

  FastLED.addLeds<WS2812, LED_PIN, RGB>(strip, LED_COUNT);

}

float color = 0;
int dif = 0;

void loop ()  
{
  for (int i = 0; i < LED_COUNT; i++)
  {
    strip[i] = CHSV(i*color + dif, 255, 120);
  }
  
  FastLED.show();  
  dif += 1;
  color += 0.01;

  if (color > 15000){
    color == 0;
  }
  
  if (dif > 15000){
    dif == 0;
  }
}



