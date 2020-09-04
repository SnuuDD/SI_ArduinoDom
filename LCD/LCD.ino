#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include "DHT.h"
#include <FirebaseArduino.h>
#define DHTTYPE DHT11 //DHT
#define dht_dpin 2 //Pin D4
#define FIREBASE_HOST "ejemplo-4ae78.firebaseio.com"
#define FIREBASE_AUTH "eblXoMob373cSKRjBQ5Sb4afqqVXjvThxeMfOAS3"
#define WIFI_SSID "Tec-IoT"
#define WIFI_PASSWORD "spotless.magnetic.bridge"
DHT dht(dht_dpin, DHTTYPE);
int seguro=0;
int trigger=0;
int echo=15;
int shake=16;
int fr=0;
int mov=14;
int rojo=12;
int verde=13;
int viento=0;
int rojoon=0; 
int asp=25;
int Dasp=10;

LiquidCrystal_I2C lcd(0x3F,20,4);//Creamos el LCD en direccion 0x3F con 20 columnas x 4 Filas

void setup() {  
  //LCD
  Serial.begin(9600);
    //FireBase
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(10);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  pinMode(trigger,OUTPUT);
  pinMode(echo,INPUT);
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  lcd.begin();
  lcd.backlight();
  //lcd.clear();
  lcd.home();
  //Boton
  pinMode(shake, INPUT);
  pinMode(rojo, OUTPUT);
  pinMode(verde, OUTPUT);
  pinMode(Dasp, OUTPUT);
  //DHT
  dht.begin();
  //Mov
  pinMode(mov,INPUT);//Sensor como entrada

}

void loop() {
      asp=Firebase.getInt("Aspersor");
     long tiempo=0;
     float distancia=0;
    lcd.clear();
    float h = dht.readHumidity();
    float t = dht.readTemperature(); 
    Firebase.setFloat("Humedad", h);
    Serial.println(h);
    Serial.println(t);
    Firebase.setFloat("Temperatura", t);
    Firebase.setInt("Viento",viento);
    Firebase.setInt("RojoOn",rojoon);
    
    Serial.println(asp);
    //Led
    if(digitalRead(shake)==0){
      asp=Firebase.getInt("Aspersor");
      int luz = analogRead(A0); //LDR en int Luz
      luz = map(luz,650,10,100,0);
      Firebase.setInt("Luz", luz);
      if(luz>20){
        rojoon=0;
        digitalWrite(rojo,LOW);
        lcd.setCursor(0,0);
        lcd.print("Luz Apagada");
                      
      }else{
        rojoon=1;
        digitalWrite(rojo,HIGH);
        lcd.setCursor(0,0);
        lcd.print("Luz Encedida");
        }
     //TemH   
     lcd.setCursor(0,1);
     lcd.print("H = ");
     lcd.setCursor(4,1);
     lcd.print(h);
     lcd.setCursor(10,1);
     lcd.print("T = ");
     lcd.setCursor(14,1);
     lcd.print(t);
     //
    digitalWrite(trigger,HIGH);
    delayMicroseconds(20);
    digitalWrite(trigger,LOW);
    tiempo=(pulseIn(echo,HIGH)/2);//Se divide entre 2 por tiempo entrada salida
    distancia=(tiempo*0.0343);
     lcd.setCursor(0,3);
     lcd.print("D = ");
     lcd.setCursor(4,3);
     lcd.print(distancia);
     Firebase.setFloat("Distancia",distancia);
     if(distancia>50){
      lcd.setCursor(12,3);
      lcd.print("SEGURO");
      seguro=0;
      Firebase.setInt("Intruso",seguro);
      }
      else{lcd.setCursor(12,3);
      lcd.print("INTRUSO");
      seguro=1;
      Firebase.setInt("Intruso",seguro);
      }
     
     //Mov
       long state = digitalRead(mov);
      if(state == HIGH){
      digitalWrite(verde, HIGH);
      viento=1;
      lcd.setCursor(0,2);
      lcd.print("Hay VIENTO");
      }
      else{
        lcd.setCursor(0,2);
        viento=0;
        digitalWrite(verde,LOW);
        lcd.print("Sin VIENTO"); 
        }
        if(asp==0){
      digitalWrite(Dasp, LOW);
      lcd.setCursor(11,2);
      lcd.print("ASPER OFF");
      }
      else{
        digitalWrite(Dasp, HIGH);
      lcd.setCursor(11,2);
      lcd.print("ASPER ON");
      } 
      }
  else{
    asp=Firebase.getInt("Aspersor");
    Serial.println("APAGADO");
    lcd.print("TEMBLANDO");
    digitalWrite(rojo,LOW);
    }
    delay(3000);
    
  
  
 
}
