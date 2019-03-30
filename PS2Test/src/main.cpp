#include <Arduino.h>
#include "controller.cpp"
//
Controller controller;

byte LeftMotorAPin = 5;
byte LeftMotorBPin = 4;
byte LeftMotorSpeedPin = 3;

byte RightMotorAPin = 8;
byte RightMotorBPin = 7;
byte RightMotorSpeedPin = 9;

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

  if (state.RY > 128) {
      digitalWrite(RightMotorAPin, 0);
      digitalWrite(RightMotorBPin, 1);
      analogWrite(RightMotorSpeedPin, (state.RY - 128) * 2);
  } else if (state.RY < 128) {
      digitalWrite(RightMotorAPin, 1);
      digitalWrite(RightMotorBPin, 0);
      analogWrite(RightMotorSpeedPin, 250 - state.RY * 2);      
  } else {
    digitalWrite(RightMotorAPin, 0);
    digitalWrite(RightMotorBPin, 0);      
  }

  delay(50);
}
