/* Chances are you don’t have an STM32F103C8T6 chip, but a Chinese clone, 
namely CS32F103C8T6 from China Key System & Integrated. That one is reported to 
use the 0x2ba01477 (as the IDcode or rather as the SW-DP tap id).

As a workaround, you can edit the file 
  ~/.platformio/packages/tool-openocd/scripts/target/stm32f1x.cfg 
and change the line:

set _CPUTAPID 0x1ba01477
to:
set _CPUTAPID 0x2ba01477

more info: https://community.platformio.org/t/cannot-upload-to-stm32-bluepill-board-over-stlink-v2/3492/13
*/

#include <Arduino.h>
#include <Servo.h>

Servo myservo1;

void setup()
{
  pinMode(PC13, OUTPUT);  
  myservo1.attach(11);
}

void loop()
{
  digitalWrite(PC13, HIGH);
  delay(300);
  
  digitalWrite(PC13, LOW);
  delay(100);

  myservo1.write(90);
  delay(500);
  myservo1.write(0);
  delay(500);  
}
