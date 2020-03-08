#include <AFMotor.h>
#include <Servo.h>
#include <NewPing.h>

AF_DCMotor motor(2);
Servo servo1;
NewPing sonar(A1 /*Trig*/, A0 /*Echo*/, 70 /*max distance*/);

int Left = 105;
int Right = 40;

void setup()
{  
  //Serial.begin(9600); 
  pinMode(A0, INPUT);
  pinMode(A1, OUTPUT);
  servo1.attach(9);
}

void loop()
{
  int s = sonar.ping_cm();
  //Serial.println(s);
  
  if (s > 50 || s == 0)
  {    
    motor.run(RELEASE);
    motor.run(FORWARD);
    motor.setSpeed(210);
    servo1.write(67);
  }
  else
  {
    motor.run(BACKWARD);  
    motor.setSpeed(255); 
    delay(800);
    
    if (random(0, 2) == 0)
      servo1.write(Left);
    else
      servo1.write(Right);
      
    delay(800);
  }
   
  delay(50);
}
