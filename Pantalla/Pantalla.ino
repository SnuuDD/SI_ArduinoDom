#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>

LiquidCrystal_I2C lcd(0x3F,20,4);//Creamos el LCD en direccion 0x3F con 20 columnas x 4 Filas

void setup() {
  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();
  lcd.clear();
  lcd.home();
  lcd.setCursor(2, 2);
  lcd.print("Hmmm... xd");
}

void loop() {
 
}
