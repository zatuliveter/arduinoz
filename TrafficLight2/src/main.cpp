#include <Arduino.h>
// test
const int red = 6;
const int yellow = 5;
const int green = 3;
const int beep = 7;
const int buttonPin = 2;     // номер входа, подключенный к кнопке

bool buttonState;

void setup() {
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(beep, OUTPUT);
  pinMode(buttonPin, INPUT);

  digitalWrite(red, 1);
}

void SetLight(bool redSig, bool yellowSig, bool greenSig, int waitTime, int repeatCount, int repeatDelay)
{   
  digitalWrite(red, redSig);
  digitalWrite(yellow, yellowSig);
  digitalWrite(green, greenSig);
  delay(waitTime);

  for(int i=0; i<repeatCount; i++)
  { 
    if(redSig==1) digitalWrite(red, !redSig);
    if(yellowSig==1) digitalWrite(yellow, !yellowSig);
    if(greenSig==1) digitalWrite(green, !greenSig);
    
    digitalWrite(beep, 0); 

    delay(repeatDelay / 2);

    digitalWrite(red, redSig);
    digitalWrite(yellow, yellowSig);
    digitalWrite(green, greenSig);
    digitalWrite(beep, 1);

    delay(repeatDelay / 2);
  }
  
  digitalWrite(beep, 0);
}


void loop() {

  // считываем значения с входа кнопки
  buttonState = digitalRead(buttonPin);
   
  if (buttonState == 0) {
    delay(100);
    return;
  }

  SetLight(1, 0, 0, 0, 7, 300); //мигающий красный
    
  SetLight(0, 1, 0, 1000, 0, 0); //жёлтый

  SetLight(0, 0, 1, 10000, 7, 300); //зеленый
  
  SetLight(0, 1, 0, 1000, 0, 0); //жёлтый
  
  SetLight(1, 0, 0, 3000, 0, 300); //красный
}