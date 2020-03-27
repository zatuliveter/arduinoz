#include <SoftwareSerial.h>

SoftwareSerial Bluetooth(2, 3); // RX, TX
    
int Motor1Forward = 10;
int Motor1Back = 11;
int Motor2Forward = 9;
int Motor2Back = 6;

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
  
  pinMode(Motor1Forward, OUTPUT);
  pinMode(Motor1Back, OUTPUT);
  pinMode(Motor2Forward, OUTPUT);
  pinMode(Motor2Back, OUTPUT);
}


void loop()
{  
  pos = GetPos(pos);

  int m1 = map(pos.y, -40, 40, -250, 250);
  
  if ( m1 > 0 ) {    
    analogWrite(Motor1Forward, m1); 
    analogWrite(Motor2Forward, m1); 
    digitalWrite(Motor1Back, 0); 
    digitalWrite(Motor2Back, 0);     
  }
  else {    
    analogWrite(Motor1Back, -m1); 
    analogWrite(Motor2Back, -m1);  
    digitalWrite(Motor1Forward, 0); 
    digitalWrite(Motor2Forward, 0);     
  }
  
  //int m2 = map(pos.y, -40, 40, 250, -250);
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
        x = getValue(inputStr, ' ', 0).toInt();
        y = getValue(inputStr, ' ', 1).toInt();        
      }
      
      if (x != 0) pos.x = x;
      if (y != 0) pos.y = y;      
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
