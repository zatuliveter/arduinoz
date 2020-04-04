#include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial Bluetooth(2, 4); // RX, TX
Servo dipperServo; 
    
int LeftMotorForward = 6;
int LeftMotorBack = 11;
int RightMotorForward = 5;
int RightMotorBack = 3;
int dipperPin = 9;

//String state = "s" ;

struct Pos
{
  int x = 0;
  int y = 0;
  int button = 0;
};

Pos pos;

void setup()
{
  Serial.begin(9600);
  dipperServo.attach(dipperPin);

  Bluetooth.begin(9600);
  Bluetooth.print("AT+NAMELego-Car");
  
  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorBack, OUTPUT);
  pinMode(RightMotorForward, OUTPUT);
  pinMode(RightMotorBack, OUTPUT);
  //pinMode(dipperPin, OUTPUT);
}


void loop()
{  
  pos = GetPos(pos);

  int m1 = map(pos.x, 100, -100, 250, -250);  
  int m2 = map(pos.y, 100, -100, -150, 150);
  
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

  
  if ( pos.button == 1 ) {    
    dipperServo.write(100);     
  }
  
  if ( pos.button == 2 ) {    
    dipperServo.write(250);     
  }
  
}

Pos GetPos(Pos pos)
{
  if (Bluetooth.available() > 0)
  {  
    String value = Bluetooth.readStringUntil('#');
    
    if (value.length() == 7)
    {
      float angle = toRadians(value.substring(0, 3).toFloat());
      
      //Serial.print("angle=");
      //Serial.println(angle);
  
      int strength = value.substring(3, 6).toInt();
      
      //Serial.print("strength=");
      //Serial.println(strength);
      
      int button = value.substring(6, 7).toInt();
      Serial.println(value);
      Serial.println(button);
         
      pos.x = strength * cos(angle);
      pos.y = strength * sin(angle);  
      pos.button = button; 
    }
  }
  
  return pos;
}

const float pi = 3.14159267;
float toRadians(float degrees) {
  return degrees / 360 * 2 * pi;
}
