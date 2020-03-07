#include <TM1637Display.h>

int sensorPin = A0;
int sensorValue = 0;  

TM1637Display display(3 /*clk*/, 2 /*dio*/);

void setup() 
{
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(13, OUTPUT); 
  display.setBrightness(0x02);
}

void loop() 
{
  sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);
  
  display.showNumberDec(sensorValue, false);

  if(sensorValue < 500) 
    digitalWrite(13, HIGH);
  else
    digitalWrite(13, LOW);
    
  delay(1000);
}
