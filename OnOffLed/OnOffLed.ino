void setup() {
  Serial.begin(9600);
  pinMode(05, INPUT_PULLUP); //Pin D1 Entrada
  pinMode(02, OUTPUT); //Salida Pin D4

}

void loop() {
  if(digitalRead(05)==0){
    Serial.println("ENCENDIDO");
    digitalWrite(02, HIGH);
  }
  else{
    Serial.println("APAGADO");
    digitalWrite(02,LOW);
    }
    delay(100);
}
