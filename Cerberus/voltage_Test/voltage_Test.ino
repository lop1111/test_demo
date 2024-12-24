int volt_input = A0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(volt_input, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  float voltage, voltage_Battery;
  voltage = analogRead(volt_input);
  voltage_Battery = ((voltage * 25) / 1010);
  Serial.print(voltage_Battery); Serial.print("  "); Serial.print(((voltage_Battery) / 8.0) * 100); Serial.println("%");
  delay(300);

}
