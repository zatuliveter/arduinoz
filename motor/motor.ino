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
int Right = 105;
int Left = 40;
int Center = 67;
int headlightsPin = 5;
int steeringPin = 3;
int breakPin = 4;
    
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
  
  pinMode(MotorForward, OUTPUT);
  pinMode(MotorBack, OUTPUT);
  pinMode(MotorPWM, OUTPUT);
  pinMode(steeringPin, OUTPUT);
  pinMode(headlightsPin, OUTPUT);
  pinMode(breakPin, OUTPUT);
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
  
  int motorVal = map(_radioData.Analog1, 0, 1023, 120, -200);
  Motor(motorVal);
  
  if (motorVal > 0) 
    digitalWrite(breakPin, 1);
  else
    digitalWrite(breakPin, 0);
  
  int sterlingPos = map(_radioData.Analog2, 0, 1023, Left, Right);
  sterlingServo.write(sterlingPos);
  
  switch (_radioData.Switch) {
    case 0: analogWrite(headlightsPin, 0); break;
    case 1: analogWrite(headlightsPin, 100); break;
    case 2: analogWrite(headlightsPin, 255); break;  
  }  
}
