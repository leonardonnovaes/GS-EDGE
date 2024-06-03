#include "HX711.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
 
#define DT A1
#define SCK A0
#define SDA A4
#define SCL A5
int ledVerde = 2;
int ledVermelho = 3;
//often 0x3F. 0x27, 0x20, 0x38
LiquidCrystal_I2C lcd(0x27,20,4);
 
HX711 balance;
float old_grammes;
void setup() {
  // put your setup code here, to run once:
  pinMode(ledVerde, OUTPUT);
  pinMode(ledVermelho, OUTPUT);
  Serial.begin(115200);
  Serial.println("Iniciando balança ...");
  balance.begin(DT, SCK);
  Wire.begin();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Inciciando   O20");
  lcd.setCursor(0,1);
  lcd.print("Balanca: ");
  delay(2000);
  lcd.clear();
  Serial.println("Peso: ");
}
void loop() {
  float kilos = float(balance.get_units() / 420.0);
  lcd.print("PESO: ");
  lcd.setCursor(7,0);
  lcd.print("           ");
  lcd.setCursor(7,0);
  lcd.print(String(kilos)+" kg.");
  Serial.println(kilos, 1);
  delay(2000);
  if (kilos > 1){
    digitalWrite(ledVerde, HIGH);
    digitalWrite(ledVermelho, LOW);
    lcd.clear();
    lcd.print("Chuveiro ");
    lcd.setCursor(0,1);
    lcd.print("Liberado ");
    delay(2000);
  }
  else{
    digitalWrite(ledVermelho, HIGH);
    digitalWrite(ledVerde, LOW);
    lcd.clear();
    lcd.print("Adicione mais ");
    lcd.setCursor(0,1);
    lcd.print("peso ");
    delay(2000);
  }
  delay(2000);
  lcd.clear();
}
