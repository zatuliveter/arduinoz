void setup() 
{
  pinMode(2, INPUT);
 
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
}

void loop() 
{ 
  if (digitalRead(2) == HIGH)
  {
    //если человек есть
    digitalWrite(7, HIGH);
  }
  else
  {
    //если нет человека    
    digitalWrite(7, LOW);
  }
  
  delay(50);
}
