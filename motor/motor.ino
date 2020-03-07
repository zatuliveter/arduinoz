#include <AFMotor.h>
#include <Servo.h>
#include <NewPing.h>

AF_DCMotor motor(4);
Servo servo1;
NewPing sonar(A1 /*Trig*/, A0 /*Echo*/, 70 /*max distance*/);
 

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
    servo1.write(66);
  }
  else
  {
    motor.run(BACKWARD);  
    motor.setSpeed(255);
    delay(800);
    servo1.write(105);
    delay(800);
  }
   
  delay(50);
  
  //motor.run(RELEASE);
  //motor.run(BACKWARD);
  //motor.setSpeed(150);
  //servo1.write(40);
  //delay(2500);

}
