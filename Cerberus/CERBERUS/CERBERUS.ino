/*
  -> LCD
  -> Voltage Sensor 1
  -> Voltage Sensor 2
  -> Blue Tooth
  -> LDR
  -> Switch 1
  -> Switch 2
  -> Relay
  -> Opto Coupler

*/

#include <Wire.h>
//#include "RTClib.h"
#include <LiquidCrystal_I2C.h>
//#include <U8g2lib.h>

//OLED Comm
#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

// LCD
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4);

// OLED
//U8G2_SSD1306_128X32_UNIVISION_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);

// RTC Chip
//RTC_DS1307 RTC;

// Light Input
int LDR = A0;  // For LDR Sensor Input

// Switch
int SW1 = 2;    // INPUT
int Switch_Count = 0; // Switch press count

int SW2_BypassSwitch = 3; // INPUT

// OUTPUT BACK LIGHT
int Back_Light = 4;

//Relay
int Relay = 7;  // OUTPUT

// Optocoupler //OUTPUT
int Opto = 6;

// Data From Bluetooth
char Blue;

// Setup and Init
void setup() {
  // put your setup code here, to run once:
  // serial Init
  Serial.begin(9600);

  // LCD Init
  lcd.init();
  lcd.backlight();

  // RTC Init
  //  Wire.begin();
  //  RTC.begin();

  // OLED Init
  // u8g2.begin();
  //  u8g2.clearBuffer();
  //  u8g2.setFont(u8g2_font_ncenB08_tr);  // choose a suitable font
  //  u8g2.drawStr(0, 10, "CERBERUS LOADING"); // write something to the internal memory
  //  u8g2.sendBuffer();

  // LDR Init
  pinMode(LDR, INPUT);

  // Switch Init
  pinMode(SW1, INPUT_PULLUP);

  // By_passSwitch Input
  pinMode(SW2_BypassSwitch, INPUT_PULLUP);

  // Back_Light
  pinMode(Back_Light, OUTPUT);

  // Relay
  pinMode (Relay, OUTPUT);

  // Opto
  pinMode(Opto, OUTPUT);

  // RTC Value Init
  //  if (! RTC.isrunning()) {
  //    Serial.println("RTC is NOT running!");
  //    RTC.adjust(DateTime(F(__DATE__), F(__TIME__)));

  // LCD Init Display
  lcd.setCursor(0, 0);
  //  lcd.print("LORD SHIVA");
  lcd.print("PROJECT : CERBERUS");
  lcd.setCursor(0, 1);
  lcd.print("Loading............");
  delay(2000);
  lcd.clear();

}
// Relay Output
// Setting as Output

int Bluetooth_Send;

void loop()
{

  /*
    if ( a > 700)
    {
      lcd.setCursor(0, 2);
      lcd.print("DAY");
      delay(100);
    }
    else
    {
      lcd.setCursor(0, 2);
      lcd.print("NIGHT");
    }
    //  lcd.setCursor(0, 2);
    //  lcd.print("     "); */
  int data; // input from the LDR
  Battery_1(); // Battery 1 Function
  Battery_2(); // Battery 2 Function
  data = Ldr(); // Output from the LDR function
  Switch(data); // Calling Switching function and passing data
  Bluetooth();  // Calling Bluetooth
}


// Battery Function Definiton
void Battery_1(void)
{
  // Variables For Battery Input
  const int voltpin = A1;
  const int maxvalue = 1010;
  const int maxvoltage = 25;
  float analogread = 0;

  // Battery Voltage Calculations
  analogread = analogRead(voltpin);
  analogread = (analogread / maxvalue) * maxvoltage;
  lcd.setCursor(0, 0);
  lcd.print("V1:");
  lcd.print(analogread);

  Bluetooth_Send = &analogread;   // Copying data to send via Bluetooth
  //  Bluetooth_Serial(analogread);

  // Battery Level Check
  if (analogread > 4)
  {
    lcd.setCursor(8, 0);
    lcd.print("B1:");
    lcd.print("F");
  }
  else if (analogread < 4)
  {
    lcd.setCursor(8, 0);
    lcd.print("B1:");
    lcd.print("L");
  }

  float Percent;    // Calculating Percentage of the battery

  Percent = (analogread / 5.0);
  lcd.setCursor(14, 0);
  lcd.print(Percent);
  lcd.print("%");

}

void Battery_2(void)            // Battery Voltage check for 2
{
  // Variables For Battery Input
  const int voltpin = A2;
  const int maxvalue = 1010;
  const int maxvoltage = 25;
  float analogread = 0;

  // Battery Voltage Calculations
  analogread = analogRead(voltpin);
  analogread = (analogread / maxvalue) * maxvoltage;
  lcd.setCursor(12, 1);
  lcd.print("V2:");
  lcd.print(analogread);

  //  Bluetooth_Send = &analogread;   // Copying data to send via Bluetooth
  //  Bluetooth_Serial(analogread);

  // Battery Level Check
  //  if (analogread > 4)
  //  {
  //    lcd.setCursor(10, 1);
  //   lcd.print("Bat:");
  //   lcd.print("F");
  //  }
  //  else if (analogread < 4)
  //  {
  //    lcd.setCursor(10, 1);
  //    lcd.print("Bat:");
  //    lcd.print("L");
  //  }

  //  float Percent;    // Calculating Percentage of the battery

  //  Percent = (analogread / 3.4);
  //  lcd.setCursor(14, 1);
  //  lcd.print(Percent);
  //  lcd.print("%");

}   // End of Function Battery_2



//Light Detector
int Ldr (void)
{
  //Light Input RAW
  int Light_Input, a;
  Light_Input = analogRead(LDR);
  lcd.setCursor(0, 1);
  lcd.print("CON:");
  //  lcd.print(x);
  int val;
  val = digitalRead(SW2_BypassSwitch);
//  Serial.println(val);
  if (Light_Input > 900 || val == 0)
  {
    lcd.print(" NIGHT");
    a = 1;
  }
  else if (Light_Input < 200 )
  {
    lcd.print(" DAY   ");
    a = 2 ;
  }
  else
  {
    lcd.print("-");
    a = 0;
  }
  return (a);
}

void Time (void)
{
  /*
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(' ');
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
    delay(500);*/
  /*  DateTime now = RTC.now();
    lcd.setCursor(0, 0);
    lcd.print("T");
    lcd.print(now.hour(), DEC);
    lcd.print(':');
    lcd.print(now.minute(), DEC);
    lcd.print(':');
    lcd.print(now.second(), DEC);
    lcd.print("D");
    lcd.print(now.day(), DEC);
    lcd.print(':');
    lcd.print(now.month(), DEC);
    lcd.print(':');
    lcd.print(now.year(), DEC);*/
}

// Default status is LOW

void Switch(int a)
{
  lcd.setCursor(0, 2);
  lcd.print("SW-:");

  if (a == 1)  // Night Condition //
  {
    lcd.print("ON ");
    // Switch Status Read

    if (Blue == '1')  // Data Fom Bluetooth
    {
      digitalWrite(Relay, LOW);
      digitalWrite(Opto, HIGH);
    }
    else if (Blue == '2')
    {
      digitalWrite(Back_Light, HIGH);
    }
    else if (Blue == '3')
    {
      digitalWrite(Opto, LOW);
      digitalWrite(Relay, LOW);
    }
    else if (Blue == '4')
    {
      digitalWrite(Opto, HIGH);
      digitalWrite(Relay, HIGH);
    }
    else if ( Blue == '5')
    {
      digitalWrite(Back_Light, LOW);
    }


    if (digitalRead(SW1) == 0)  //  Reading the Data from the Switch //
    {
      Switch_Count = Switch_Count + 1; // Counter

      Light(Switch_Count); // Calling Light Function and passing the count

      if (Switch_Count == 6) // Resetting the counter
      {
        Switch_Count = 0;
      }

    }
    delay(100);
  }
  else if (a == 2)
  {
    lcd.print("OFF");
    lcd.setCursor(10, 2);
    lcd.print("LM- NULL");
    digitalWrite(Relay, HIGH);
    digitalWrite(Opto, HIGH);
  }
  else
  {
    lcd.setCursor(10, 2); // Clearing the Lcd Display for the Day Condition
    lcd.print("LM- NULL");

    lcd.setCursor(6, 3);  // Clearing the Opto;
    lcd.print("   ");

  }
}

// Light Function GOD HELP ME..!!

void Light(int Count) // Light  Funtion TO Trun On The Light
{
  switch (Count)        // Switch statements
  {
    case 1:
      lcd.setCursor(10, 2);
      lcd.print("LM-1    ");
      digitalWrite(Relay, LOW);
      digitalWrite(Opto, HIGH);
      break;
    case 2:
      lcd.setCursor(10, 2);
      lcd.print("LM-2    ");
      digitalWrite(Back_Light, HIGH);
      break;
    case 3:
      lcd.setCursor(10, 2);
      lcd.print("LM-3    ");
      digitalWrite(Opto, LOW);
      digitalWrite(Relay, LOW);
      break;
    case 4:
      lcd.setCursor(10, 2);
      lcd.print("LM-4    ");
      digitalWrite(Opto, HIGH);
      digitalWrite(Relay, HIGH);
      break;
    case 5:
      lcd.setCursor(10, 2);
      lcd.print("LM-5    ");
      digitalWrite(Back_Light, HIGH);
    default:
      digitalWrite(Relay, HIGH);
      digitalWrite(Opto, HIGH);
      digitalWrite(Back_Light, LOW);
  }
}

void Bluetooth(void)
{
  char Data_Bluetooth; // Varialble to receive data from Bluetooth

  lcd.setCursor(0, 3);
  lcd.print("DRIVE SAFE AND SLOW");

  if (Serial.available() > 0)  // Check if the data is available
  {
    Data_Bluetooth = Serial.read();
    Serial.write(Data_Bluetooth);
    Serial.write('\n');
    //    Serial.print(Data_Bluetooth);
    Blue = Data_Bluetooth;

    switch (Data_Bluetooth)     // Controlling Lights via Bluetooth
    {
      case '1':
        Serial.write("*****************");
        Serial.write('\n');
        Serial.write("********HALF-MODE*******");
        Serial.write('\n');
        Serial.write("******************");
        Serial.write('\n');
        break; //

      case '2':
        Serial.write("******************");
        Serial.write('\n');
        Serial.write("********BACK-LIGHT********");
        Serial.write('\n');
        Serial.write("******************");
        Serial.write('\n');
        break;
      case '3':
        Serial.write("******************");
        Serial.write('\n');
        Serial.write("********FULL-MODE*******");
        Serial.write('\n');
        Serial.write("******************");
        Serial.write('\n');
        break;
      case '4':
        Serial.write("******************");
        Serial.write('\n');
        Serial.write("********BACK-LIGHT-OFF*******");
        Serial.write('\n');
        Serial.write("******************");
        Serial.write('\n');
        break;
      case '5':
        Serial.write("******************");
        Serial.write('\n');
        Serial.write("********FULL-MODE-OFF*******");
        Serial.write('\n');
        Serial.write("******************");
        Serial.write('\n');
        break;
    }
  }
}
