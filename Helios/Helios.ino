
#include<SPI.h>
#include<SD.h>


int LDR = A0;

int ldr = A1;

int SD_Led = 3;

int SD_Remove_file = 2;

int SD_Manual_Start = 5;

int x = 0;

//struct data{
//  int a;
//  int b;
//}test;

//struct data D;
//test.a = 0;


/*
  #include <Wire.h>

  #include <U8g2lib.h>


  #ifdef U8X8_HAVE_HW_SPI
  #include <SPI.h>
  #endif
  #ifdef U8X8_HAVE_HW_I2C
  #include <Wire.h>
  #endif

  int LDR = A0; // LDR INPUT


  U8G2_SSD1306_128X32_UNIVISION_F_SW_I2C u8g2(U8G2_R0, SCL, SDA,  U8X8_PIN_NONE);

  void setup() {
  // put your setup code here, to run once:
  u8g2.begin();
  u8g2.clearBuffer();          // clear the internal memory
  u8g2.setFont(u8g2_font_oldwizard_tu); // choose a suitable font
  // u8g2.drawStr(10, 10, "LORD SHIVA"); // write something to the internal memory
  u8g2.drawStr(10, 10, "HELIOS");
  u8g2.sendBuffer();// transfer internal memory to the display
  delay(2000);
  u8g2.clearBuffer();

  u8g2.setFont(u8g2_font_synchronizer_nbp_tf);
  u8g2.drawStr(0, 10, "LDR-DATA: ");
  u8g2.drawStr(0, 20, "SLOAR-VOLT: ");
  u8g2.sendBuffer();

  Serial.begin(9600);

  if (!SD.begin(4))
  {
    Serial.print("CARD FAILED");
    return;
  }
  Serial.println("CARD READY");


  }*/

void setup()
{


  
  pinMode(LDR, INPUT);

  pinMode(SD_Led, OUTPUT);
  
  pinMode(SD_Remove_file, INPUT_PULLUP);

  pinMode(ldr, INPUT);

  pinMode(SD_Manual_Start, INPUT_PULLUP);

  Serial.begin(9600);

  if (!SD.begin(4))
  {
    Serial.print("CARD FAILED");
    return;
  }
  Serial.println("CARD READY");


}




void loop() {
  // put your main code here, to run repeatedly:

  float value;

  Serial.print(analogRead(ldr));

  value = analogRead(LDR);
  value = (value / 1010) * 25;
  Serial.println(value);

if (digitalRead(SD_Remove_file) == 0)
{
  SD_Erase();
}


if(digitalRead(SD_Manual_Start) == 0)
{
  SD_Start_Write(value,LDR);
}

  delay(200);
  digitalWrite(SD_Led, LOW);
}

void SD_Start_Write(int value,int value1)
{
  File file = SD.open("Helio.txt", FILE_WRITE);
  
  Serial.println(file);
  if (file)
  {
    x = x + 1;
    digitalWrite(SD_Led, HIGH);
    Serial.print(value);
    file.print(x);
    file.print("] ");
    file.print("Solar Panel Voltage:");
    file.print(" ");
    file.print(value);
    file.print(" ");
    file.println(value1);
    file.close();
  }
  else
  {
    Serial.println("Error1");
    digitalWrite(SD_Led, LOW);
    delay(150);
    digitalWrite(SD_Led, HIGH);
    delay(150);
  }
}


void SD_Erase(void)
{
  
  {
    x = 0;
    
    Serial.println("Removing Helio.txt...");

    SD.remove("Helio.txt");

    if (SD.exists("Helio.txt")) {

      Serial.println("Helio.txt exists.");

    } else {

      Serial.println("Helio.txt doesn't exist.");

    }

    digitalWrite(SD_Led, LOW);
    delay(2000);
    digitalWrite(SD_Led, HIGH);
    delay(2000);

  }
}


