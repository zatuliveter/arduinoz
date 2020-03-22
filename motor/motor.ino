#include <Servo.h>
#include <NewPing.h>
#include <SoftwareSerial.h>

Servo servo1;
NewPing FrontSonar(2 /*Trig*/, 3 /*Echo*/, 70 /*max distance*/);
NewPing RearSonar(5 /*Trig*/, 4 /*Echo*/, 70 /*max distance*/);
SoftwareSerial Bluetooth(6, 7); // RX, TX

int Right = 105;
int Left = 40;
int Center = 67;
    
int MotorForward = 12;
int MotorBack = 13;
int MotorPWM = 11;

String state = "s" ;

void setup()
{
  Serial.begin(9600);
  servo1.attach(9);

  Bluetooth.begin(9600);
  
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
  bluetooth();
  //sonar();
}

void bluetooth()
{
  int frontSonarValue = FrontSonar.ping_cm();
  if (frontSonarValue == 0) frontSonarValue = 100;
  
  int rearSonarValue = RearSonar.ping_cm();
  if (rearSonarValue == 0) rearSonarValue = 100;
  
  if (Bluetooth.available())
  {
    String val = Bluetooth.readString();    
    val = val.substring(0, 1);
    state = val;    
  }

  
  if (state == "f" and frontSonarValue < 30)
  {
    state = "s";
  }

  if (state == "b" and rearSonarValue < 30)
  {
    state = "s";
  }

  if (state == "r" and frontSonarValue < 30)
  {
    state = "s";  
  }

  if (state == "l" and frontSonarValue < 30)
  {
    state = "s";  
  }
  
  if (state == "s") { 
    servo1.write(Center);
    Motor(0);
  }
  
  if (state == "f") { 
    servo1.write(Center);
    Motor(210); 
  }
  
  if (state == "b") { 
    servo1.write(Center);
    Motor(-210);
  } 
  
  if (state == "l") { 
    servo1.write(Left);
    Motor(210); 
  }  
  
  if (state == "r") { 
    servo1.write(Right);
    Motor(210);
  }
}

void sonar()
{
  int frontSonarValue = FrontSonar.ping_cm();
  int rearSonarValue = RearSonar.ping_cm();
  
  //Serial.println(s);

  if (frontSonarValue > 50 || frontSonarValue == 0)
  {
    //назад
    Motor(-210);
    servo1.write(67);
  }
  else
  {
    //вперёд
    Motor(210);
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
