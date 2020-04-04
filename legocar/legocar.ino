#include <SoftwareSerial.h>

SoftwareSerial Bluetooth(2, 3); // RX, TX
    
int LeftMotorForward = 10;
int LeftMotorBack = 11;
int RightMotorForward = 9;
int RightMotorBack = 6;

String state = "s" ;

struct Pos
{
  int x = 0;
  int y = 0;
};

Pos pos;

void setup()
{
  //Serial.begin(9600);

  Bluetooth.begin(9600);
  Bluetooth.print("AT+NAMELego-Car");
  
  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorBack, OUTPUT);
  pinMode(RightMotorForward, OUTPUT);
  pinMode(RightMotorBack, OUTPUT);
}


void loop()
{  
  pos = GetPos(pos);

  int m1 = map(pos.y, -40, 40, 250, -250);  
  int m2 = map(pos.x, -40, 40, -200, 200);
  
  int leftMotor = -m2;
  int rightMotor = m2;
 
  leftMotor += m1; 
  rightMotor += m1;
  
  if (leftMotor > 250) leftMotor = 250;
  if (rightMotor > 250) rightMotor = 250;
  if (leftMotor < -250) leftMotor = -250;
  if (rightMotor < -250) rightMotor = -250;
  
  if ( leftMotor > 0 ) {    
    analogWrite(LeftMotorForward, leftMotor);  
    digitalWrite(LeftMotorBack, 0);     
  }
  else {    
    analogWrite(LeftMotorBack, -leftMotor);  
    digitalWrite(LeftMotorForward, 0); 
  }
  
  if ( rightMotor > 0 ) {    
    analogWrite(RightMotorForward, rightMotor);  
    digitalWrite(RightMotorBack, 0);     
  }
  else {    
    analogWrite(RightMotorBack, -rightMotor);  
    digitalWrite(RightMotorForward, 0); 
  }
}

String fixString(String str)
{
  char validChars[] = " -0123456789";
  String res = "";
  for(int i=0; i < str.length(); i++)
  {
    char c = str.charAt(i);
    for(int j=0; j<12; j++)
    {
      if (c == validChars[j]){
        res += c;
        break;
      }
    }
  }
  return res;
}

Pos GetPos(Pos pos)
{
  char input;
  String inputStr;
  
  if (Bluetooth.available())
  {
    input = Bluetooth.read();
    //Serial.println(input);
    if (input == '$')
    {
      while(true)
      {
        input = Bluetooth.read();
        if (input == ';') break;
        inputStr = inputStr + input;
      }
      
      inputStr = fixString(inputStr);
            
      //Serial.println(inputStr);
      
      int x;
      int y;
      if (inputStr != "") 
      {
        pos.x = getValue(inputStr, ' ', 0).toInt();
        pos.y = getValue(inputStr, ' ', 1).toInt();        
      }
    }
  }
  
  return pos;
}

String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
