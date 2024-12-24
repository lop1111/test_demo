// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009
// this code is public domain, enjoy!

#include <AFMotor.h>

AF_DCMotor motor(4);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor1(1);

int led = A0;


void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Motor test!");

  // turn on motor
  motor.setSpeed(200);
  motor.run(RELEASE);

  pinMode(led,OUTPUT);
}

void loop()
{
  char data;

  if (Serial.available() > 0)
  {
    data = Serial.read();
  }


  switch (data)
  {
    case 'a':
      Forward();
      delay(200);
      break;

    case 'b':
      Backward();
      break;

    case 'c':
      Right();
      break;

    case 'd':
      Left();
      break;

    default:
      Stop();
      Led();
      

  }



  /*
    if (data == 'a')
    {
      Forward();
      //      motor.run(RELEASE);
    }
    //  delay(1000);
    //  motor.run(RELEASE);

    if (data == 'b')
    {
      Backward();
    }

    if (data == 'c')
    {
      Right();
    }

    if (data == 'd')
    {
      Left();
    }

    if (data = 'x')
    {
        Stop();
    }
  */
}


void Forward(void)
{
  motor.setSpeed(255);
  motor1.setSpeed(255);
  motor2.setSpeed(255);
  motor3.setSpeed(255);

  motor.run(BACKWARD);
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  delay(500);
}

void Backward(void)
{
  motor.setSpeed(255);
  motor1.setSpeed(255);
  motor2.setSpeed(255);
  motor3.setSpeed(255);

  motor.run(FORWARD);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  delay(500);
}


void Right(void)
{
  motor.setSpeed(255);
  motor1.setSpeed(255);
  motor2.setSpeed(255);
  motor3.setSpeed(255);

  motor.run(BACKWARD);
  motor1.run(FORWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  delay(500);
}

void Left(void)
{
  motor.setSpeed(255);
  motor1.setSpeed(255);
  motor2.setSpeed(255);
  motor3.setSpeed(255);

  motor.run(FORWARD);
  motor1.run(BACKWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  delay(500);
}

void Stop(void)
{
  motor.run(RELEASE);
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
}



void Led(void)
{
  digitalWrite(led,HIGH);
  delay(500);
  digitalWrite(led,LOW);
  delay(500);
}

