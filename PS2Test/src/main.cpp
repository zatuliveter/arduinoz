#include <Arduino.h>
#include "controller.cpp"

Controller controller;

byte LeftMotorAPin = 4;
byte LeftMotorBPin = 5;
byte LeftMotorSpeedPin = 3;

void setup()
{
  pinMode (LeftMotorAPin, OUTPUT); 
  pinMode (LeftMotorBPin, OUTPUT);
  pinMode (LeftMotorSpeedPin, OUTPUT);

  Serial.begin(9600);
  delay(500);
  
  controller.Setup(); 
}

void DispalyController(ControllerState state)
{  
   Serial.print("LX=");
   Serial.print(state.LX, DEC);

   Serial.print(" LY=");
   Serial.print(state.LY, DEC);
   
   Serial.print(" RX=");
   Serial.print(state.RX, DEC);
   
   Serial.print(" RY=");
   Serial.print(state.RY, DEC);
   
   Serial.println('.');
}

void loop()
{
  ControllerState state = controller.Read();
  DispalyController(state);

  if (state.LY > 128) {
      digitalWrite(LeftMotorAPin, 0);
      digitalWrite(LeftMotorBPin, 1);
      analogWrite(LeftMotorSpeedPin, (state.LY - 128) * 2);
  } else if (state.LY < 128) {
      digitalWrite(LeftMotorAPin, 1);
      digitalWrite(LeftMotorBPin, 0);
      analogWrite(LeftMotorSpeedPin, 250 - state.LY * 2);      
  } else {
    digitalWrite(LeftMotorAPin, 0);
    digitalWrite(LeftMotorBPin, 0);      
  }

  delay(50);
}
