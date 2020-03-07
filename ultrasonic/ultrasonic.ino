
#include <NewPing.h>
 
#define TRIGGER_PIN 3
#define ECHO_PIN 2
#define MAX_DISTANCE 50

#define R 5
#define G 6
#define B 7

// настройка объекта NewPing: контакты и максимальная дистанция
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
 
void setup() 
{
  //Serial.begin(9600);  
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);
}
 
void loop() 
{
  int s = sonar.ping_cm();
  //Serial.println(s);

  digitalWrite(R, LOW);
  digitalWrite(G, LOW);
  digitalWrite(B, LOW);
  
  if (s < 10)
  {
    digitalWrite(R, HIGH);
  }  
  else if (s < 20)  
  {
    digitalWrite(G, HIGH);
  }
  else if (s < 30)
  {
    digitalWrite(B, HIGH);
  }

  delay(100);    
}
