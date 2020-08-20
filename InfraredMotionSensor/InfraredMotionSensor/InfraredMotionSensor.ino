int led = 9;
int buzzer = 8;

#define MOTION_PIN  A7

void setup()
{
  Serial.begin(9600);
  
  pinMode(MOTION_PIN, INPUT);
  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);
}

void loop()
{  
  int motionState = analogRead(MOTION_PIN);
  Serial.println(motionState);

  if(motionState > 400)
  {
    digitalWrite(led, HIGH);
    digitalWrite(buzzer, HIGH);
  }
  else
  {
    digitalWrite(led, LOW);
    digitalWrite(buzzer, LOW);
  }
   
}
