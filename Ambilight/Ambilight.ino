
//----------------------НАСТРОЙКИ-----------------------
#define NUM_LEDS 228         // число светодиодов в ленте
#define DI_PIN 13            // пин, к которому подключена лента

#define start_flashes 1      // проверка цветов при запуске (1 - включить, 0 - выключить)

#define max_bright 180       // максимальная яркость (0 - 255)
#define min_bright 50        // минимальная яркость (0 - 255)

//----------------------НАСТРОЙКИ-----------------------

int new_bright, new_bright_f;
unsigned long bright_timer;

#define serialRate 115200  // скорость связи с ПК
uint8_t prefix[] = {'A', 'd', 'a'}, hi, lo, chk, i;  // кодовое слово Ada для связи
#include <FastLED.h>
CRGB leds[NUM_LEDS];  // создаём ленту
byte buffer[3];

void ledTest(byte r, byte g, byte b)
{
  byte st = 3;
  byte i;
  for (i = 0; i < 255; i=i+st)
  {
    LEDS.showColor(CRGB(i * r, i * g, i * b));
  }
  for (i = 255; i > 0; i=i-st)
  {
    LEDS.showColor(CRGB(i * r, i * g, i * b));
  }
}

void setup()
{
  FastLED.addLeds<WS2812, DI_PIN, GRB>(leds, NUM_LEDS);  // инициализация светодиодов
  
  // тест ленты в начале
  if (start_flashes) {
    ledTest(1, 0, 0);
    ledTest(0, 1, 0);
    ledTest(0, 0, 1);
  }

  Serial.begin(serialRate);
  Serial.print("Ada\n");     // Связаться с компом

  memset(leds, 0, NUM_LEDS * sizeof(struct CRGB));
}

void initConnect() {
  
  for (i = 0; i < sizeof prefix; ++i) {
waitLoop: while (!Serial.available()) ;;
    if (prefix[i] == Serial.read()) continue;
    i = 0;
    goto waitLoop;
  }

  while (!Serial.available());
  hi = Serial.read();
  
  while (!Serial.available());
  lo = Serial.read();
  
  while (!Serial.available());
  chk = Serial.read();
  
  if (chk != (hi ^ lo ^ 0x55))
  {
    i = 0;
    goto waitLoop;
  }
  
}

void loop() {
  initConnect();
  
  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    
    // читаем данные для каждого цвета

    if (Serial.readBytes((char*)buffer, 3) < 3) break;

    leds[i].r = buffer[0];
    leds[i].g = buffer[1]; 
    leds[i].b = buffer[2];
  }
  
  FastLED.show();  // записываем цвета в ленту
}
