#include <FirebaseArduino.h>
#include <ESP8266WiFi.h>

#define FIREBASE_HOST "ejemplo-4ae78.firebaseio.com"
#define FIREBASE_AUTH "eblXoMob373cSKRjBQ5Sb4afqqVXjvThxeMfOAS3"
#define WIFI_SSID "Tec-IoT"
#define WIFI_PASSWORD "spotless.magnetic.bridge"

int led = 12;     //salida-D6---GPIO12
int sen = 13;  //sensor-D7---GPIO13
int led2=14;

void setup() {
  pinMode(sen, INPUT);   // Declaramos el sensor como entrada
  pinMode(led, OUTPUT);  // Declaramos el led como salida
  pinMode(led2, OUTPUT);
  
  Serial.begin(9600);

  // conectamos el wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi Conectado!");
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
Firebase.setString("Led","false");
}

void loop(){
  long state = digitalRead(sen);
  if (state == LOW) {
    Firebase.setInt("Movimiento", 0);
  } else {
    Firebase.setInt("Movimiento", 1);
  }
  

if(Firebase.getString("Led").equals("true")) 
{digitalWrite(led2,HIGH);}
else{digitalWrite(led2,LOW);
}
}
