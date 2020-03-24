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
};

Pos pos;

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
  int frontSonarValue = FrontSonar.ping_cm();
  if (frontSonarValue == 0) frontSonarValue = 100;
  
  int backSonarValue = BackSonar.ping_cm();
  if (backSonarValue == 0) backSonarValue = 100;

  pos = GetPos(pos);

  int servoPos = map(pos.x, -40, 40, Left, Right);
  servo1.write(servoPos);
  
  int motorVal = map(pos.y, -40, 40, -210, 210);
  Motor(motorVal);
}

Pos GetPos(Pos pos)
{
  char input;
  String inputStr;
  
  if (Bluetooth.available())
  {
    input = Bluetooth.read();
    //Serial.println(input);
    if (input == '$')
    {
      while(true)
      {
        input = Bluetooth.read();
        if (input == ';') break;
        inputStr = inputStr + input;
      }
      inputStr.trim();
      //Serial.println(inputStr);

      int x;
      int y;
      if (inputStr != "") 
      {
        x = getValue(inputStr, ' ', 0).toInt();
        y = getValue(inputStr, ' ', 1).toInt();        
      }
      
      if (x != 0) pos.x = x;
      if (y != 0) pos.y = y;      
    }
  }
  
  return pos;
}

String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
