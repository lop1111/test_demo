int ldr = A1;

int wireless_8 = 8;
int wireless_9 = 9;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ldr, INPUT);
  pinMode(wireless_8, OUTPUT);
  pinMode(wireless_9, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int value;
  value = analogRead(ldr);
  Serial.print(value);
  delay(200);

  int value1;

  value1 = map(value, 0, 1023, 0, 180);

  Serial.println(value1);
  delay(100);

  if (value1 > 150)
  {
    Serial.print("TX");
    digitalWrite(wireless_8, LOW);
    digitalWrite(wireless_9, HIGH);
       delay(54);
  }
  else if (value1 < 150)
  {
    digitalWrite(wireless_9, LOW);
    digitalWrite(wireless_8, HIGH);
       delay(50);
  }
  else
  {
    digitalWrite(wireless_8, HIGH);
    digitalWrite(wireless_9, HIGH);
  }
}
