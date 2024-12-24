#include <SPI.h>
#include "RF24.h"

RF24 myRadio (7, 8);

struct package
{
  //  int id=0;
  //  float temperature = 0.0;
  //char  text[100] ="empty";
  int x;
  int y;
  int Button_Status;
  int Counter = 0;
  int Servo_Data;
};

byte addresses[][6] = {"0"};


typedef struct package Package;
Package data;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  myRadio.begin();
  myRadio.setChannel(115);
  //  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate( RF24_250KBPS ) ;
  myRadio.openReadingPipe(1, addresses[0]);
  myRadio.startListening();

}

void loop() {
  // put your main code here, to run repeatedly:

  if ( myRadio.available())
  {
 //   while (myRadio.available())
    {
      myRadio.read( &data, sizeof(data) );
    }
  }
 
  //Serial_Data();

  if(data.x > 100)
  {
    Serial.write('a');
  }
  else if(data.x < 50)
  {
    Serial.write('b');
  }
  else if(data.y > 100)
  {
    Serial.write('c');
  }
  else if(data.y < 50)
  {
    Serial.write('d');
  }
  else
  {
    Serial.write('0');
  }
  
  delay(25);
}

void Serial_Data(void)
{
  Serial.print(data.x); 
  Serial.print(" "); 
  Serial.print(data.y); 
  Serial.print(" "); 
  Serial.print(data.Button_Status); 
  Serial.print(" "); 
  Serial.print(data.Counter);
  Serial.print(" ");
  Serial.println(data.Servo_Data);
}

