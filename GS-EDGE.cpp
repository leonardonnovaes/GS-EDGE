#include "HX711.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
 
#define DT A1          // Define o pino DT do HX711 conectado ao pino analógico A1 do Arduino
#define SCK A0         // Define o pino SCK do HX711 conectado ao pino analógico A0 do Arduino
#define SDA A4         // Define o pino SDA do display LCD I2C conectado ao pino analógico A4 do Arduino
#define SCL A5         // Define o pino SCL do display LCD I2C conectado ao pino analógico A5 do Arduino
int ledVerde = 2;      // Define o pino digital 2 para o LED verde
int ledVermelho = 3;   // Define o pino digital 3 para o LED vermelho

// Inicializa o display LCD com o endereço I2C (0x27) e dimensões (20 colunas e 4 linhas)
LiquidCrystal_I2C lcd(0x27, 20, 4);

// Inicializa a balança usando o módulo HX711
HX711 balance;

void setup() {
  pinMode(ledVerde, OUTPUT);       // Configura o pino do LED verde como saída
  pinMode(ledVermelho, OUTPUT);    // Configura o pino do LED vermelho como saída
  Serial.begin(115200);            // Inicializa a comunicação serial a 115200 bps
  Serial.println("Iniciando balança ...");  // Mensagem de inicialização na porta serial
  
  balance.begin(DT, SCK);          // Inicializa o módulo HX711 com os pinos DT e SCK
  Wire.begin();                    // Inicializa a comunicação I2C
  lcd.init();                      // Inicializa o display LCD
  lcd.backlight();                 // Liga a luz de fundo do display LCD
  lcd.setCursor(0, 0);             // Define o cursor na posição (0, 0) no display LCD
  lcd.print("Inciciando   O20");   // Imprime mensagem no display LCD
  lcd.setCursor(0, 1);             // Define o cursor na posição (0, 1) no display LCD
  lcd.print("Balanca: ");          // Imprime "Balanca: " no display LCD
  delay(2000);                     // Aguarda por 2 segundos
  lcd.clear();                     // Limpa o display LCD
  Serial.println("Peso: ");        // Mensagem inicial na porta serial
}

void loop() {
  float kilos = float(balance.get_units() / 420.0);  // Converte a leitura do sensor para quilogramas
  lcd.print("PESO: ");                               // Imprime "PESO: " no display LCD
  lcd.setCursor(7, 0);                               // Define o cursor na posição (7, 0) no display LCD
  lcd.print("           ");                          // Limpa a linha atual no display LCD
  lcd.setCursor(7, 0);                               // Define o cursor na posição (7, 0) no display LCD
  lcd.print(String(kilos) + " kg.");                 // Imprime o peso em quilogramas no display LCD
  Serial.println(kilos, 1);                          // Imprime o peso na porta serial com uma casa decimal
  delay(2000);                                       // Aguarda por 2 segundos

  if (kilos > 1) {                                   // Se o peso for maior que 1 kg
    digitalWrite(ledVerde, HIGH);                    // Liga o LED verde
    digitalWrite(ledVermelho, LOW);                  // Desliga o LED vermelho
    lcd.clear();                                     // Limpa o display LCD
    lcd.print("Chuveiro ");                          // Imprime "Chuveiro " no display LCD
    lcd.setCursor(0, 1);                             // Define o cursor na posição (0, 1) no display LCD
    lcd.print("Liberado ");                          // Imprime "Liberado " no display LCD
    delay(2000);                                     // Aguarda por 2 segundos
  } else {                                           // Se o peso for menor ou igual a 1 kg
    digitalWrite(ledVermelho, HIGH);                 // Liga o LED vermelho
    digitalWrite(ledVerde, LOW);                     // Desliga o LED verde
    lcd.clear();                                     // Limpa o display LCD
    lcd.print("Adicione mais ");                     // Imprime "Adicione mais " no display LCD
    lcd.setCursor(0, 1);                             // Define o cursor na posição (0, 1) no display LCD
    lcd.print("peso ");                              // Imprime "peso " no display LCD
    delay(2000);                                     // Aguarda por 2 segundos
  }
  
  delay(2000);                                       // Aguarda por 2 segundos antes de repetir o loop
  lcd.clear();                                       // Limpa o display LCD
}
