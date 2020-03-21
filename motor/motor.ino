#include <Servo.h>
#include <NewPing.h>

Servo servo1;
NewPing FrontSonar(2 /*Trig*/, 3 /*Echo*/, 70 /*max distance*/);
NewPing RearSonar(5 /*Trig*/, 4 /*Echo*/, 70 /*max distance*/);

int Left = 105;
int Right = 40;

int MotorForward = 12;
int MotorBack = 13;
int MotorPWM = 11;

void setup()
{
  //Serial.begin(9600);
  servo1.attach(9);

  pinMode(MotorForward, OUTPUT);
  pinMode(MotorBack, OUTPUT);
  pinMode(MotorPWM, OUTPUT);
}

void Motor(int val) {
  if (val > 0) {
    digitalWrite(MotorForward, 1);
    digitalWrite(MotorBack, 0);
    analogWrite(MotorPWM, val); 
  }
  else if (val < 0) {
    digitalWrite(MotorForward, 0);
    digitalWrite(MotorBack, 1);
    analogWrite(MotorPWM, -val);
  }
  else {
    digitalWrite(MotorForward, 0);
    digitalWrite(MotorBack, 0);
    analogWrite(MotorPWM, 0);
  }
}

void loop()
{
  int frontSonarValue = FrontSonar.ping_cm();
  int rearSonarValue = RearSonar.ping_cm();
  //Serial.println(s);

  if (frontSonarValue > 50 || frontSonarValue == 0)
  {
    //вперёд
    Motor(210);
    servo1.write(67);
  }
  else
  {
    //назад
    Motor(-210);
    delay(800);

    if (random(0, 2) == 0)
      servo1.write(Left);
    else
      servo1.write(Right);

    if (rearSonarValue < 20 && rearSonarValue != 0)
    {
      Motor(210);
      servo1.write(105);
      delay(800);
    }

    delay(800);
  }

  delay(50);
}
