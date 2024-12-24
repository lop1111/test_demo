
// Fill-in information from your Blynk Template here
//#define BLYNK_TEMPLATE_ID           "TMPLxxxxxx"
//#define BLYNK_DEVICE_NAME           "Device"
#define BLYNK_TEMPLATE_ID "TMPL9W2ghkZx"
#define BLYNK_DEVICE_NAME "LED"

#include<Servo.h>

Servo myservo;

#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG

// Uncomment your board, or configure a custom board in Settings.h
//#define USE_SPARKFUN_BLYNK_BOARD
//#define USE_NODE_MCU_BOARD
//#define USE_WITTY_CLOUD_BOARD
//#define USE_WEMOS_D1_MINI

#include "BlynkEdgent.h"

BLYNK_WRITE(V0)
{
  int val1;
  int val = param.asInt();

 val1 = map (val,0,1023,0,180);
  
  myservo.write(val1);
}

BLYNK_READ(V1)
{
  Blynk.virtualWrite(V1,analogRead(12));
}

void setup()
{
  Serial.begin(115200);
  delay(100);
  myservo.attach(2);
  BlynkEdgent.begin();
}

void loop() {
  BlynkEdgent.run();
}
