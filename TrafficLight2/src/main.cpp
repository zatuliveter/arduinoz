#include <Arduino.h>
// test 2
int red = 4;
int yellow = 3;
int green = 2;
int beep = 5;

void setup() {
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(beep, OUTPUT);
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
  SetLight(0, 0, 1, 3000, 7, 300);
  
  SetLight(0, 1, 0, 1000, 0, 0);
  
  SetLight(1, 0, 0, 3000, 7, 300);
  
  SetLight(0, 1, 0, 3000, 0, 0);
}


