#include <Arduino.h>
#include <Servo.h>
#include <NewPing.h>

Servo myservo;
NewPing sonar(3 /*TRIGGER_PIN*/, 4 /*ECHO_PIN*/, 50 /*MAX_DISTANCE*/);

void setup() {                
  myservo.attach(9);
}

void loop() 
{  
  int s = sonar.ping_cm();
  if (s > 0 and s < 30) 
  {
    myservo.write(0);
    delay(2500);  
  }
  else {
    myservo.write(75);
    delay(20);  
  }
}
