#include <AFMotor.h>
#include <Servo.h>
#include <NewPing.h>

AF_DCMotor motor(2);
Servo servo1;
NewPing sonar1(A1 /*Trig*/, A0 /*Echo*/, 70 /*max distance*/);
NewPing sonar2(A2 /*Trig*/, A3 /*Echo*/, 70 /*max distance*/);

int Left = 105;
int Right = 40;

void setup()
{  
  //Serial.begin(9600);
  
  pinMode(A3, INPUT);
  pinMode(A2, OUTPUT); 
  
  pinMode(A0, INPUT);
  pinMode(A1, OUTPUT);
  
  servo1.attach(9);
}

void loop()
{
  int s1 = sonar1.ping_cm();
  int s2 = sonar1.ping_cm();
  //Serial.println(s);
  
  if (s1 > 50 || s1 == 0)
  { 
    //вперёд   
    motor.run(RELEASE);
    motor.run(FORWARD);
    motor.setSpeed(210);
    servo1.write(67);
  }
  else
  {
    //назад
    motor.run(BACKWARD);  
    motor.setSpeed(210); 
    delay(800);
    
    if (random(0, 2) == 0)
      servo1.write(Left);
    else
      servo1.write(Right);

    if (s2 < 20 && s2 != 0)
    {
      motor.run(FORWARD);
      motor.setSpeed(210);
      delay(800);
      
      if (random(0, 2) == 0)
        servo1.write(Left);
      else
        servo1.write(Right);
    }
      
    delay(800);
  }
   
  delay(50);
}
