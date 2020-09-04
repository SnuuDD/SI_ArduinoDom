#include "DHT.h"
#define DHTTYPE DHT11 //DHT
#define dht_dpin 15 //Pin D8
DHT dht(dht_dpin, DHTTYPE);

void setup(void) 
{
  dht.begin();
  Serial.begin(9600);
  Serial.println("Humedad y Temperatura\n");
  delay(1000);

}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  Serial.print("Humedad = ");
  Serial.print(h);
  Serial.print("%   ");
  Serial.print("Temperatura = ");
  Serial.print(t);
  Serial.print(" C");
  Serial.print("\n");
}
