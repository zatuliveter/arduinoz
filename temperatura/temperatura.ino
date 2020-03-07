#include "DHT.h"

DHT dht(2, DHT11);

void setup() 
{
   dht.begin();
   Serial.begin(9600);
}

void loop() 
{
   float h = dht.readHumidity();
   float t = dht.readTemperature();

   Serial.print("Humidite:");
   Serial.print(h);
   Serial.print(",   Temperature:");
   Serial.println(t);

   delay(1000);
}
