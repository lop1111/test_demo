/*
  -> Project : ORION or OLED
  -> Display : LCD 2.8"
  -> Controller : ESP8266
*/

#include <Arduino.h>
#include<Servo.h>

Servo servo1;
Servo servo2;
Servo servo3;

int inc = 2;

int sensor = 7;
int SW = 8;
//#include <U8g2lib.h>

//#ifdef U8X8_HAVE_HW_SPI
//#include <SPI.h>
//#endif
//#ifdef U8X8_HAVE_HW_I2C
//#include <Wire.h>
//#endif

//U8G2_SSD1306_128X32_UNIVISION_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);

void setup() {
  servo1.attach(3);
  servo2.attach(6);
  servo3.attach(9);

  Serial.begin(9600);

  pinMode(inc, INPUT_PULLUP);
  pinMode(SW, INPUT_PULLUP);
  pinMode(sensor, INPUT);
  // put your setup code here, to run once:
  // u8g2.begin();
  //u8g2.clearBuffer();          // clear the internal memory
  // u8g2.setFont(u8g2_font_oldwizard_tu); // choose a suitable font
  // u8g2.drawStr(20, 20, "LORD SHIVA"); // write something to the internal memory
  //  u8g2.drawStr(20, 20, "ORION");
  //  u8g2.sendBuffer();          // transfer internal memory to the display
  //  delay(1000);
  servo1.write(0);
}

int  count  = 0;
int count1 = 0;
void loop() {
  // put your main code here, to run repeatedly:


  if (digitalRead(inc) == 0)
  {
    count = count + 1;
    delay(25);
    sweep(count);
    Serial.print(count);

    if (count == 180)
    {
      count = 0;
      servo1.write(0);
      servo2.write(0);
    }
  }
  else
  {
    Serial.print(digitalRead(sensor));
  }

  if (digitalRead(SW) == 0)
  {
    if (digitalRead(inc) == 0)
    {
      count1 = count1 + 1;
      servo3.write(count1);
    }
    if (count1 == 180)
    {
      count1 = 0;
    }
  }
  else if (digitalRead(SW) == 1 )
  {
    if (digitalRead(inc) == 0)
    {
      count1 = count1 - 1;
      servo3.write(count1);
    }
    if(count1 == 0)
    {
      count1 = 180;
    }
  }

}


void sweep(int a)
{
  servo1.write(a);
  servo2.write(a);
}

