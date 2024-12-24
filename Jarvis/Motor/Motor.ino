#include <AFMotor.h>

AF_DCMotor motor(4);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor1(1);

int led = A0;

void setup()
{

  Serial.begin(9600);
  Serial.println("Motor test!");

  motor.setSpeed(200);
  motor.run(RELEASE);

  pinMode(led, OUTPUT);

}

void loop()
{

  char data;

  if (Serial.available() > 0)
  {
    data = Serial.read();
  }

  Serial.print(data);

  if (data == 'd')
  {
    Forward();
    delay(25);
  }

  if (data == 'c')
  {
    Backward();
    delay(25);
  }

  if (data == 'a')
  {
    Right();
    delay(25);
  }

  if (data == 'b')
  {
    Left();
    delay(25);
  }

  else
  {
    Stop();
    delay(25);
  }
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
  delay(25);
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
  delay(25);
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
  delay(25);
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
  delay(25);
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
  digitalWrite(led, HIGH);
  delay(100);
  digitalWrite(led, LOW);
  delay(100);
}

