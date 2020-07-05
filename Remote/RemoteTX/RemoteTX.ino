#include <SPI.h>
#include <NRFLite.h>

const bool DEBUG = false;

const static uint8_t RADIO_ID = 1;             // Our radio's id.
const static uint8_t DESTINATION_RADIO_ID = 0; // Id of the radio we will transmit to.
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
RadioPacket _sentData;

/*
Radio    Arduino
CE    -> 9
CSN   -> 10 (Hardware SPI SS)
MOSI  -> 11 (Hardware SPI MOSI)
MISO  -> 12 (Hardware SPI MISO)
SCK   -> 13 (Hardware SPI SCK)
IRQ   -> No connection
VCC   -> No more than 3.6 volts
GND   -> GND
*/

void setup() {
  if (DEBUG) Serial.begin(115200);
    
  if (!_radio.init(RADIO_ID, PIN_RADIO_CE, PIN_RADIO_CSN, NRFLite::BITRATE250KBPS, 100))
  {
      if (DEBUG) Serial.println("Cannot communicate with radio");
      while (1); // Wait here forever.
  }
  
  pinMode(A0, INPUT_PULLUP);
  pinMode(A3, INPUT_PULLUP);
  pinMode(A4, INPUT_PULLUP);
  pinMode(A5, INPUT_PULLUP);
  pinMode(3, OUTPUT);
}

void loop() {
  
  _radioData.Button1 = !digitalRead(A0);
  _radioData.Button2 = !digitalRead(A3);
  
  bool switchPos1 = digitalRead(A4);
  bool switchPos2 = digitalRead(A5);
  
  _radioData.Switch = switchPos1 ? switchPos2 ? 1 : 0 : 2;
  
  _radioData.Analog1 = analogRead(A2);
  _radioData.Analog2 = analogRead(A1);
  
  digitalWrite(3, 0);
  if (!areTheSame(_sentData, _radioData))
  {
    if (_radio.send(DESTINATION_RADIO_ID, &_radioData, sizeof(_radioData))) // Note how '&' must be placed in front of the variable name.
    {
      _sentData.Button1 = _radioData.Button1;
      _sentData.Button2 = _radioData.Button2;
      _sentData.Switch = _radioData.Switch;
      _sentData.Analog1 = _radioData.Analog1;
      _sentData.Analog2 = _radioData.Analog2;
    
      pintData(_sentData);
      
      digitalWrite(3, 1);
      
      if (DEBUG) Serial.println("...Success");
    }
    else
    {
      if (DEBUG) Serial.println("...Failed");
    }
  }
  
  delay(1);
}

bool areTheSame(RadioPacket a, RadioPacket b)
{  
  return a.Button1 == b.Button1
      && a.Button2 == b.Button2
      && a.Switch  == b.Switch
      && abs(a.Analog1 - b.Analog1) <= 5
      && abs(a.Analog2 - b.Analog2) <= 5;
}

void pintData(RadioPacket p)
{
  if (!DEBUG) return;
  
  Serial.print("b1="); Serial.print(p.Button1); 
  Serial.print(", b2="); Serial.print(p.Button2); 
  Serial.print(", s="); Serial.print(p.Switch); 
  
  Serial.print(", a1="); Serial.print(p.Analog1); 
  Serial.print(", a2="); Serial.print(p.Analog2); 
  
  Serial.println("");
}
