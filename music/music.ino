void setup() {
  pinMode(A0, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(A1, OUTPUT);
}
void loop() {
  tone(8, 500, 450);
  delay(450);
  pinMode(A0, HIGH);
  delay(100);
  pinMode(A1, HIGH);
  
  tone(8, 0, 450);
  delay(450);
  pinMode(A1, LOW);
  delay(100);
  pinMode(A0, LOW);  
}
