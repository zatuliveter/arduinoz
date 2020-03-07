void setup()
{
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, LOW);
  
  pinMode(3, INPUT);
}

void loop()
{
  if (digitalRead(A0) == HIGH)   
  {     
    //если кнопка нажата
    digitalWrite(11, HIGH);
    delay(500);
    digitalWrite(12, HIGH);
    delay(500);
  }
  else
  {
    //если кнопка не нажата
    digitalWrite(13, LOW);
    delay(500);
    digitalWrite(12, LOW);
    delay(500);
    digitalWrite(11, LOW);
  }
}
