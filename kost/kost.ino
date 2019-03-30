byte btnPin = 2;

void setup() {
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);
      
  pinMode(btnPin, INPUT);

  while(true)
  {    
    bool btn = digitalRead(btnPin);    
    if (btn == 1) return;

    setRandom();
    delay(10);
  }
}

void setPins(bool p1, bool p2, bool p3, bool p4, bool p5, bool p6, bool p7)
{  
  digitalWrite(9, p1);
  digitalWrite(8, p2);
  digitalWrite(7, p3);
  digitalWrite(6, p4);
  digitalWrite(5, p5);
  digitalWrite(4, p6);
  digitalWrite(3, p7);
}

void setRandom()
{  
  int rnd = random(1, 7);
  
  if (rnd == 6) setPins(1, 1, 1, 1, 0, 1, 1);  
  if (rnd == 5) setPins(1, 1, 0, 0, 1, 1, 1);  
  if (rnd == 4) setPins(1, 1, 0, 0, 0, 1, 1);  
  if (rnd == 3) setPins(1, 0, 0, 0, 1, 0, 1);  
  if (rnd == 2) setPins(1, 0, 0, 0, 0, 0, 1);  
  if (rnd == 1) setPins(0, 0, 0, 0, 1, 0, 0);
}

void loop() 
{
  bool btn = digitalRead(btnPin);

  if (btn == 0) return;

  int cnt = random(25, 60);
  for(int i=0; i<cnt; i++)
  {
    setRandom();    
    delay(3 * i);
  }

  delay(0500);
}
