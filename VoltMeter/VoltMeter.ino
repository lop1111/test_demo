#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

int Volt_Input = A0;

void setup() {

  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  pinMode(Volt_Input, INPUT);
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.setCursor(0, 0);
  lcd.print("Lord Shiva");

  Voltage();

}


void Voltage(void)
{
  float volt, Voltage_Value;

  volt = analogRead(Volt_Input);
  volt = (volt / 1010) * 25;
  lcd.setCursor(10,1);
  lcd.print(volt);
  Serial.print(volt);
  Serial.print(" ");
  Serial.println(volt);
  delay(100);
}

