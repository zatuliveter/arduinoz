const int micPin = A0;

void setup(){
  Serial.begin(9600);  
}

void loop() {
  int mv = analogRead(micPin) * 5.0 / 1024.0 * 1000.0;
  Serial.println(mv);
}
