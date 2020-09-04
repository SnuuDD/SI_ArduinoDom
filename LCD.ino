#include <Wire.h>
  
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include "DHT.h"
#include <FirebaseArduino.h>
#define DHTTYPE DHT11 //DHT
#define dht_dpin 10 //Pin D2


#define FIREBASE_HOST "ejemplo-4ae78.firebaseio.com"
#define FIREBASE_AUTH "eblXoMob373cSKRjBQ5Sb4afqqVXjvThxeMfOAS3"
#define WIFI_SSID "Tec-IoT"
#define WIFI_PASSWORD "spotless.magnetic.bridge"


DHT dht(dht_dpin, DHTTYPE);
int relay= D0;
int SwitchRealy = 0;

int shake=D8;
int SwitchShake = 0;

int trig=D5;
int echo=D4;
int rojo=D6;
int rojoon=0;
int mov=0;

int buzzer = 9; 

LiquidCrystal_I2C lcd(0x3F,20,4);//Creamos el LCD en direccion 0x3F con 20 columnas x 4 Filas

void setup() {  
  //BEGIN
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
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  //LCD
  lcd.begin();
  lcd.backlight();  
  lcd.home();
  //Clock
  pinMode(relay,OUTPUT); 
  //Shake
  pinMode(shake, INPUT);
  //Ultrasonico
  pinMode(echo, INPUT);
  pinMode(trig, OUTPUT);
  //Boton
  pinMode(D7, INPUT_PULLUP);
  digitalWrite(D7,LOW);
  //Buzzer
  pinMode(buzzer, OUTPUT);
  //
  pinMode(rojo, OUTPUT);
//  pinMode(verde, OUTPUT);
  //DHT
  dht.begin();
  //Mov
  pinMode(mov,INPUT);//Sensor como entrada
     //Relay 
  digitalWrite(relay,LOW);
}

void loop() {
    long state = digitalRead(mov);
    long tiempo=0;
    float distancia=0;
    float h = dht.readHumidity();
    float t = dht.readTemperature(); 
    Firebase.setFloat("Humedad", h);
    Serial.println(h);
    Serial.println(t);
    Firebase.setFloat("Temperatura", t);  
    //
     if(digitalRead(D7)==0){
      lcd.setCursor(0,1);
      lcd.print("MODO MANUAL ACTIVADO");
      rojoon=1;
      digitalWrite(rojo,HIGH);
    }
    else{
      digitalWrite(rojo,LOW);
     digitalWrite(trig,HIGH);
    delayMicroseconds(20);
    digitalWrite(trig,LOW);
    tiempo=(pulseIn(echo,HIGH)/2);
    distancia=(tiempo*0.0343);
    Firebase.setFloat("Distancia", distancia);
    if(distancia<50){
      lcd.clear();
      lcd.setCursor(1,1);
      lcd.print("INTRUSO DETECTADO");
      for(int i=0;i=4;i++){
        tone(buzzer, 1000); 
        delay(1000);        
        noTone(buzzer);
        }
    }else{
      lcd.setCursor(7,0);
      lcd.print("SIN RIESGO");
      }
      
      int luz = analogRead(A0); //LDR en int Luz
      luz = map(luz,650,10,100,0);
      Firebase.setInt("Luz", luz);
      if(luz>25){
        digitalWrite(relay,HIGH);
        lcd.setCursor(0,0);
        lcd.print("Noche");
        }
       else{
          digitalWrite(relay,HIGH);
          lcd.setCursor(0,0);
          lcd.print("DeDia");
          }
      if(digitalRead(shake)==0){
        lcd.setCursor(0,3);
        lcd.print("ESTATICO");       
        }
        else{
          lcd.setCursor(0,3);
            lcd.print("TIEMBLA ");
          }
      if(state == HIGH){
      lcd.setCursor(2,1);
      lcd.print("HAY VIENTO");
      }
      else{
      lcd.setCursor(2,1);
      lcd.print("HAY VIENTO"); 
        }
       
    }


    
   
    
    
    /*if(digitalRead(shake)==0){
      int luz = analogRead(A0); //LDR en int Luz
      luz = map(luz,650,10,100,0);
      Firebase.setInt("Luz", luz);
      if(luz>20){
        rojoon=0;
        digitalWrite(rojo,LOW);
        lcd.setCursor(0,0);
        lcd.print("Rojo Apagado");
                      
      }else{
        rojoon=1;
        digitalWrite(rojo,HIGH);
        lcd.setCursor(0,0);
        lcd.print("Rojo Encedido");
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
     lcd.setCursor(9,3);
     lcd.print("-_-");
     //Mov 
       long state = digitalRead(mov);
      if(state == HIGH){
      digitalWrite(verde, HIGH);
      verdeon=1;
      lcd.setCursor(0,2);
      lcd.print("Hay Movimiento");
      }
      else{
        lcd.setCursor(0,2);
        verdeon=0;
        digitalWrite(verde,LOW);
        lcd.print("Sin movimiento"); 
        }
        

       
      }
  else{
    Serial.println("APAGADO");
    lcd.print("TEMBLANDO");
    digitalWrite(rojo,LOW);
    }
    
    lcd.clear();*/
    delay(3000);
  
 
}
