#include <Arduino.h>
#include <Servo.h>
#include <SPI.h>
#include <NRFLite.h>

/* Radio: 
MISO -> Arduino 12 MISO
MOSI -> Arduino 11 MOSI
SCK  -> Arduino 13 SCK
CE   -> Any GPIO Pin (can be same as CSN)
CSN  -> Any GPIO Pin (pin 10 recommended)
IRQ  -> Any GPIO Pin (optional) */
const static uint8_t RADIO_ID = 0;       // Our radio's id.  The transmitter will send to this id.
const static uint8_t PIN_RADIO_CE = 10;
const static uint8_t PIN_RADIO_CSN = 10;


struct RadioPacket // Any packet up to 32 bytes can be sent.
{
  bool Button1;
  bool Button2;
  byte Switch = 1;    
  short Analog1 = 370;
  short Analog2 = 512;
};

NRFLite _radio;
RadioPacket _radioData;

Servo sterlingServo;
int steringPin = 7;
int Right = 60;
int Left = 140;
int Center = (Left + Right) / 2;
int prevSterlingPos = -1;

//int headlightsPin = 8;
//int breakPin = 7;
    
int Motor1Forward = 4;
int Motor1Back = 2;

int Motor2Forward = 5;
int Motor2Back = 6;

int MotorPWM = 3;
int minBackwardSpeed = 160;
int maxForwardSpeed = 255;



void setup()
{
  Serial.begin(115200);
  
  Serial.println("Init"); 
  if (!_radio.init(RADIO_ID, PIN_RADIO_CE, PIN_RADIO_CSN, NRFLite::BITRATE250KBPS, 100))
  {
      Serial.println("Cannot communicate with radio");
      while (1); // Wait here forever.
  }
  
  sterlingServo.attach(steringPin);

  // Change PWM frequency for D5 & D6:
  //TCCR0B = TCCR0B & B11111000 | B00000001; // for PWM frequency of 62500.00 Hz
  //TCCR0B = TCCR0B & B11111000 | B00000010; //7812.50 Hz
  //TCCR1B = TCCR1B & B11111000 | B00000001;
  //TCCR2B = TCCR2B & B11111000 | B00000001; 
  
  pinMode(Motor1Forward, OUTPUT);
  pinMode(Motor1Back, OUTPUT);
  pinMode(Motor2Forward, OUTPUT);
  pinMode(Motor2Back, OUTPUT);
  pinMode(MotorPWM, OUTPUT);
  
  pinMode(steringPin, OUTPUT);
  //pinMode(headlightsPin, OUTPUT);
  //pinMode(breakPin, OUTPUT); 
  Serial.println("Init completed."); 
}

void Motor(int val) {
  //Serial.println(val);
  bool motor1Enabled = false;
  bool motor2Enabled = false;

  switch (_radioData.Switch) {
    case 0: motor1Enabled = true; break;
    case 1: motor2Enabled = true; break;
    case 2: motor1Enabled = motor2Enabled = true; break;  
  }
  
  if (val > 0) {
    digitalWrite(Motor1Forward, motor1Enabled);
    digitalWrite(Motor1Back, 0);
    
    digitalWrite(Motor2Forward, motor2Enabled);
    digitalWrite(Motor2Back, 0);
    
    analogWrite(MotorPWM, val); 
  }
  else if (val < 0) {
    digitalWrite(Motor1Forward, 0);
    digitalWrite(Motor1Back, motor1Enabled);
    
    digitalWrite(Motor2Forward, 0);
    digitalWrite(Motor2Back, motor2Enabled);
    
    analogWrite(MotorPWM, -val);
  }
  else {
    digitalWrite(Motor1Forward, 0);
    digitalWrite(Motor1Back, 0);
    digitalWrite(Motor2Forward, 0);
    digitalWrite(Motor2Back, 0);
    analogWrite(MotorPWM, 0);
  }
}

void loop()
{
  while (_radio.hasData())
  {
    _radio.readData(&_radioData); // Note how '&' must be placed in front of the variable name.
    break;
  }
  
  Serial.println(_radioData.Analog1); 
  int motorVal = map(_radioData.Analog1, 0, 1023, minBackwardSpeed, -maxForwardSpeed);
  Motor(motorVal);
  
//  if (motorVal > 0) 
//    digitalWrite(breakPin, 1);
//  else
//    digitalWrite(breakPin, 0);
  
  int sterlingPos = map(_radioData.Analog2, 0, 1023, Left, Right);

  //Serial.println(sterlingPos);
  if (prevSterlingPos != sterlingPos)
  {
    sterlingServo.write(sterlingPos);
    prevSterlingPos = sterlingPos;
  }
  
//  switch (_radioData.Switch) {
//    case 0: analogWrite(headlightsPin, 0); break;
//    case 1: analogWrite(headlightsPin, 100); break;
//    case 2: analogWrite(headlightsPin, 255); break;  
//  }

  //delay(7000);
}
