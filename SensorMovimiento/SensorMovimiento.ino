int led=12;//Salida D6
int sen=13;//Sensor D7
void setup() {
  Serial.begin(9600);
  pinMode(sen,INPUT);//Sensor como entrada
  pinMode(led,OUTPUT);//Led Salida

}
void loop() {
  long state = digitalRead(sen);
  delay(1000);
    if(state == HIGH){
      digitalWrite(led, HIGH);
      Serial.println("Hay Movimiento");
      }
      else{
        digitalWrite(led,LOW);
        Serial.println("Sin movimiento"); 
        }

}
