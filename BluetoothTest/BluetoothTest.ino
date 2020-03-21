#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3); // RX, TX

int LED = 13;

void setup()
{
  mySerial.begin(9600);
  pinMode(LED, OUTPUT);
}

void loop()
{
  if (mySerial.available())
  {
    int val = mySerial.read();
    
    if (val == '1') digitalWrite(LED, HIGH);    
    if (val == '0') digitalWrite(LED, LOW);
  }
}
