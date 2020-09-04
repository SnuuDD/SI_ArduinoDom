void setup() {
  Serial.begin(9600);
}

void loop() {
  int luz = analogRead(A0); //LDR en int Luz
  luz = map(luz,650,10,100,0);
  Serial.println(luz);
  delay(250);
}
