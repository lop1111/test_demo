void setup() {
  // put your setup code here, to run once:
  pinMode(A6,INPUT);
  pinMode(A7,INPUT);

  Serial.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly:

  int x,y;

  x = analogRead(A6);
  y = analogRead(A7);

  Serial.print(x); Serial.print(" "); Serial.println(y);

  delay(100);

}
