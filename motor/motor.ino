#include <Arduino.h>
#include <Servo.h>

#include <SPI.h>
#include <NRFLite.h>

const static uint8_t RADIO_ID = 0;       // Our radio's id.  The transmitter will send to this id.
const static uint8_t PIN_RADIO_CE = 9;
const static uint8_t PIN_RADIO_CSN = 10;

struct RadioPacket // Any packet up to 32 bytes can be sent.
{
  bool Button1;
  bool Button2;
  byte Switch;    
  short Analog1;
  short Analog2;
};

NRFLite _radio;
RadioPacket _radioData;

Servo sterlingServo;
Servo dipperServo;

int Right = 105;
int Left = 40;
int Center = 67;
int dipperPin = 5;
int steeringPin = 3;
    
int MotorForward = 8;
int MotorBack = 7;
int MotorPWM = 6;

void setup()
{
  Serial.begin(115200);
    
  if (!_radio.init(RADIO_ID, PIN_RADIO_CE, PIN_RADIO_CSN, NRFLite::BITRATE250KBPS, 100))
  {
      Serial.println("Cannot communicate with radio");
      while (1); // Wait here forever.
  }
  
  sterlingServo.attach(steeringPin);
  dipperServo.attach(dipperPin);
  
  pinMode(MotorForward, OUTPUT);
  pinMode(MotorBack, OUTPUT);
  pinMode(MotorPWM, OUTPUT);
  pinMode(dipperPin, OUTPUT);
  pinMode(steeringPin, OUTPUT);
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
  while (_radio.hasData())
  {
    _radio.readData(&_radioData); // Note how '&' must be placed in front of the variable name.
    //printData();
  }
  
  int motorVal = map(_radioData.Analog1, 0, 1023, 250, -250);
  Motor(motorVal);
  
  int sterlingPos = map(_radioData.Analog2, 0, 1023, Left, Right);
  sterlingServo.write(sterlingPos);
  
  switch (_radioData.Switch) {
    case 1: dipperServo.write(10); break;
    case 2: dipperServo.write(80); break;
    case 3: dipperServo.write(131); break;  
  }  
}
