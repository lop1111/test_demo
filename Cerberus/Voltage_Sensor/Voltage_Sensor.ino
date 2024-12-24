const int voltpin = A1;
const int maxvalue = 1010;
const int maxvoltage = 25;

float analogvoltage = 0;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  analogvoltage = analogRead(voltpin);
  analogvoltage = (analogvoltage/maxvalue)*maxvoltage;
  Serial.print(analogvoltage);
  Serial.println('V');
  delay(200);
}
