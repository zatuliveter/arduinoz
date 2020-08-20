#define B5K A7
int val;

void setup() {
  Serial.begin(9600);
  
}

void loop() {
  val = analogRead(B5K);
  val = map(val, 0, 1023, 0, 5);
  
  if (val > 3) 
    Serial.println("Мало Вольт");
  else
    Serial.println("Достаточно");
  
  delay(30);

}
