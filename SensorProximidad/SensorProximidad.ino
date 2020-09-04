int trigger=2;
int echo=0 ;

void setup() {
  pinMode(trigger,OUTPUT);
  pinMode(echo,INPUT);
  Serial.begin(9600);
}

void loop() {
  long tiempo=0;
  float distancia=0;
  //Disparar Trigger para activar el sensor
    digitalWrite(trigger,HIGH);
    delayMicroseconds(20);
    digitalWrite(trigger,LOW);

    //Medimos el pulso del sensor
    tiempo=(pulseIn(echo,HIGH)/2);//Se divide entre 2 por tiempo entrada salida
    distancia=(tiempo*0.0343);
    Serial.println(distancia);
    delay(300);
}
