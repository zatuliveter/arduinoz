#include <Arduino.h>
#include <Servo.h>
#include <SPI.h>
#include <NRFLite.h>

#include "PCA9685.h"
#include "Wire.h"

PCA9685 pwmController(Wire);  

/* Radio: 
MISO -> Arduino 12 MISO
MOSI -> Arduino 11 MOSI
SCK  -> Arduino 13 SCK
CE   -> Any GPIO Pin (can be same as CSN)
CSN  -> Any GPIO Pin (pin 10 recommended)
IRQ  -> Any GPIO Pin (optional) */
const static uint8_t RADIO_ID = 3;       // Our radio's id.  The transmitter will send to this id.
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


    
int Motor1Forward = 2;
int Motor1Back = 4;

int Motor2Forward = 6;
int Motor2Back = 5;

int MotorPWM = 3;
int minBackwardSpeed = 160;
int maxForwardSpeed = 255;

float servo0;
float servo1;
float servo2;


void setup()
{
  Serial.begin(115200);
  
  Serial.println("Init"); 
  if (!_radio.init(RADIO_ID, PIN_RADIO_CE, PIN_RADIO_CSN, NRFLite::BITRATE250KBPS, 100))
  {
      Serial.println("Cannot communicate with radio");
      while (1); // Wait here forever.
  }

  // servo module config  
  Wire.begin();
  pwmController.resetDevices();       // Resets all PCA9685 devices on i2c line
  pwmController.init();               // Initializes module using default totem-pole driver mode, and default disabled phase balancer
  pwmController.setPWMFreqServo();    // 50Hz provides standard 20ms servo phase length

  // pins config
  pinMode(Motor1Forward, OUTPUT);
  pinMode(Motor1Back, OUTPUT);
  pinMode(Motor2Forward, OUTPUT);
  pinMode(Motor2Back, OUTPUT);
  pinMode(MotorPWM, OUTPUT);
  
  Serial.println("Init completed."); 
}

void Motor(int val) {
  //Serial.println(val);
  bool motor1Enabled = false;
  bool motor2Enabled = false;
  
  motor1Enabled = motor2Enabled = true;
  
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
  
  servo0 = _radioData.Analog2;

  if (servo1 > servo0) servo1 -= 2;
  if (servo1 < servo0) servo1 += 2;
   
  if (servo2 > servo0) servo2 -= 1.25;
  if (servo2 < servo0) servo2 += 1.25;
 
  int s0 = map(servo0, 0, 1023, 230, 410);
  int s1 = map(servo1, 0, 1023, 255, 420);
  int s2 = map(servo2, 0, 1023, 190, 355);
  
  pwmController.setChannelPWM(0, s0);
  pwmController.setChannelPWM(1, s1);
  pwmController.setChannelPWM(2, s2);
}
