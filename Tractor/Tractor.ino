#include <SPI.h>
#include <NRFLite.h>

int LeftSpeed = 3; //PWM Pin
int LeftBack = 4;
int LeftForward = 5;

int RightSpeed = 6; //PWM Pin
int RightBack = 7;
int RightForward = 2;

const static uint8_t RADIO_ID = 0;
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

void setup()
{
  Serial.begin(115200);

  if (!_radio.init(RADIO_ID, PIN_RADIO_CE, PIN_RADIO_CSN, NRFLite::BITRATE250KBPS, 100))
  {
      Serial.println("Cannot communicate with radio");
      while (1); // Wait here forever.
  }

  pinMode(LeftSpeed, OUTPUT);
  pinMode(LeftBack, OUTPUT);
  pinMode(LeftForward, OUTPUT);
  pinMode(RightSpeed, OUTPUT);
  pinMode(RightBack, OUTPUT);
  pinMode(RightForward, OUTPUT);  
}

void loop()
{
  while (_radio.hasData())
  {
    _radio.readData(&_radioData); // Note how '&' must be placed in front of the variable name.
    //printData();
  }

  setMotors ( _radioData.Analog1, _radioData.Analog2 );
}

void setMotors(int analog1, int analog2)
{
  int motor = map(analog1, 0, 1023, -255, 255);  
  int turn  = map(analog2, 0, 1023, 220, -220);
  
  int leftMotor = motor - turn;
  int rightMotor = motor + turn;
   
  if (leftMotor > 255) leftMotor = 255;
  if (rightMotor > 255) rightMotor = 255;
  if (leftMotor < -255) leftMotor = -255;
  if (rightMotor < -255) rightMotor = -255;
  
  if ( leftMotor > 0 ) {
    analogWrite(LeftSpeed, leftMotor);  
    digitalWrite(LeftForward, 1);
    digitalWrite(LeftBack, 0);
  }
  else {    
    analogWrite(LeftSpeed, -leftMotor);  
    digitalWrite(LeftForward, 0);
    digitalWrite(LeftBack, 1); 
  }
  
  if ( rightMotor > 0 ) {
    analogWrite(RightSpeed, rightMotor);  
    digitalWrite(RightForward, 1);
    digitalWrite(RightBack, 0);
  }
  else {    
    analogWrite(RightSpeed, -rightMotor);  
    digitalWrite(RightForward, 0);
    digitalWrite(RightBack, 1); 
  }
  
}
