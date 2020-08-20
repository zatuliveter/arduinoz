#include <Arduino.h>
#include <TM1637Display.h>

#define PIN_PIR A7
#define CLK 4
#define DIO 5

TM1637Display display(CLK, DIO);

int seenMovements = 0;

void setup() {
  Serial.begin(9600);
  pinMode (PIN_PIR, INPUT);
  display.setBrightness(0x0f);
  display.clear();
  display.showNumberDec(seenMovements, false);
}

void loop() {
  int pirVal = analogRead (PIN_PIR);

  Serial.println(pirVal);
    
  if (pirVal > 400)
  {
    seenMovements = seenMovements + 1;
    display.showNumberDec(seenMovements, false);
    delay(10000);
  }
}
