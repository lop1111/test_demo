int variable;

int Led = 13;

void setup() {
  // put your setup code here, to run once:


  Serial.begin(9600);

  pinMode(Led, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

  Serial.print(random(100,1000));

  if (Serial.available() > 0)
  {
    char data;
    data = Serial.read();
    Serial.println(data);

    if (data == 1)
    {
      digitalWrite(Led, HIGH);
    }
    else if (data == 2)
    {
      digitalWrite(Led, LOW);

    }
  }
}
