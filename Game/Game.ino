  const int axisX=A1;
  const int axisY=A0;
  const int axisZ=2;
  int valX, valY, valZ = 0;

void setup()
  {
  pinMode(axisZ, INPUT_PULLUP);

  Serial.begin(9600);
 }

void loop()
{
  valX = analogRead(axisX);
  valY = analogRead(axisY);
  valZ = 1-digitalRead(axisZ);
  Serial.print("X:");Serial.print(valX, DEC);
  Serial.print(" / Y: ");Serial.print(valY, DEC);
  Serial.print(" / Z: ");Serial.println(valZ, DEC);
  delay(300);
}
