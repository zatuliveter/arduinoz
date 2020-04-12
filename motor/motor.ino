#include <Servo.h>
#include <NewPing.h>
#include <SoftwareSerial.h>

Servo servo1;
NewPing FrontSonar(2 /*Trig*/, 3 /*Echo*/, 70 /*max distance*/);
NewPing BackSonar(5 /*Trig*/, 4 /*Echo*/, 70 /*max distance*/);
SoftwareSerial Bluetooth(6, 7); // RX, TX

int Right = 105;
int Left = 40;
int Center = 67;
    
int MotorForward = 12;
int MotorBack = 13;
int MotorPWM = 11;

String state = "s" ;

struct Pos
{
  int x = 0;
  int y = 0;
  int button = 0;
};

Pos pos;

void setup()
{
  Serial.begin(9600);
  servo1.attach(9);

  Bluetooth.begin(9600);
  Bluetooth.print("AT+NAMESport-Car");
  
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
  if (frontSonarValue == 0) frontSonarValue = 100;
  
  int backSonarValue = BackSonar.ping_cm();
  if (backSonarValue == 0) backSonarValue = 100;

  pos = GetPos(pos);

  int servoPos = map(pos.x, -100, 100, Left, Right);
  servo1.write(servoPos);
  
  int motorVal = map(pos.y, -100, 100, -210, 210);
  Motor(motorVal);
     
  if ( pos.button == 1 ) {    
    //dipperServo.write(100);     
  }  
  if ( pos.button == 2 ) {    
    //dipperServo.write(250);     
  }  
}

Pos GetPos(Pos pos)
{
  if (Bluetooth.available() > 0)
  {  
    String value = Bluetooth.readStringUntil('#');
    
    if (value.length() == 7)
    {
      float angle = toRadians(value.substring(0, 3).toFloat());
      
      //Serial.print("angle=");
      //Serial.println(angle);
  
      int strength = value.substring(3, 6).toInt();

      //Serial.print("strength=");
      //Serial.println(strength);

      int button = value.substring(6, 7).toInt();
      Serial.println(value);
      Serial.println(button);

      pos.x = strength * cos(angle);
      pos.y = strength * sin(angle);  
      pos.button = button; 
    }
  }

  return pos;
}

const float pi = 3.14159267;
float toRadians(float degrees) {
  return degrees / 360 * 2 * pi;
}
