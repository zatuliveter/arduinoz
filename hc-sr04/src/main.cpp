#include <Arduino.h>

int echoPin = 9;
int trigPin = 8;
 
void setup() {
  Serial.begin (9600);
  
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB.
  }

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}
 
void loop() {
  int duration = 0;
  float cm;
  const int checkCount = 10;

  for(int i=0; i<checkCount; i++)
  {
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = duration + pulseIn(echoPin, HIGH);
  }
  float avgDuration = duration / checkCount;

  //cm = 343.0 * avgDuration / 1000000.0 / 2.0 * 100.0;
  cm = avgDuration / 58.309;
  
  Serial.print(cm);
  Serial.println(" cm");
  
}
