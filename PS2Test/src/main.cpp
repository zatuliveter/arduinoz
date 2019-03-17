#include <Arduino.h>
#include "controller.cpp"

Controller controller;

void setup(){
  Serial.begin(9600);
  delay(500); 
  controller.Setup(); 
}

void loop(){
   
   ControllerState state = controller.Read();

   Serial.print("LX=");
   Serial.print(state.LX, DEC);

   Serial.print(" LY=");
   Serial.print(state.LY, DEC);
   
   Serial.print(" RX=");
   Serial.print(state.RX, DEC);
   
   Serial.print(" RY=");
   Serial.print(state.RY, DEC);
   
   Serial.println('.');
   
   delay(50);     
}
