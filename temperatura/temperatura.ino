#include "DHT.h"
#include <TM1637Display.h>

#define CLK_PIN 9
#define DIO_PIN 10
#define DHT_PIN 11

#define RED_PIN 4
#define GREEN_PIN 5
#define BLUE_PIN 6

TM1637Display display(CLK_PIN, DIO_PIN);
DHT dht(DHT_PIN, DHT11);

void setup() 
{
   dht.begin();
   Serial.begin(9600);
   display.setBrightness(0x01);
}

void loop() 
{
   float h = dht.readHumidity();
   float t = dht.readTemperature();

   Serial.print("Humidite:");
   Serial.print(h);
   Serial.print(",   Temperature:");
   Serial.println(t);

   display.showNumberDec(t, false);

   if (t < 10)
   {     
     digitalWrite(6, HIGH);
     digitalWrite(5, LOW);
     digitalWrite(4, LOW);
  }
  else
  {   
     digitalWrite(6, LOW);    
     digitalWrite(4, HIGH);
     digitalWrite(5, LOW);    
  }

  delay(500);
  
}
