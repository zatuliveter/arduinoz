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
  Serial.begin(115200);
    
  if (!_radio.init(RADIO_ID, PIN_RADIO_CE, PIN_RADIO_CSN))
  {
      Serial.println("Cannot communicate with radio");
      while (1); // Wait here forever.
  }
}

void loop() {
  while (_radio.hasData())
  {
    _radio.readData(&_radioData); // Note how '&' must be placed in front of the variable name.
    printData();
  }
}

void printData()
{
  Serial.print("b1="); Serial.print(_radioData.Button1); 
  Serial.print(", b2="); Serial.print(_radioData.Button2); 
  Serial.print(", s="); Serial.print(_radioData.Switch); 
  
  Serial.print(", a1="); Serial.print(_radioData.Analog1); 
  Serial.print(", a2="); Serial.print(_radioData.Analog2); 
  
  Serial.println("");
}
