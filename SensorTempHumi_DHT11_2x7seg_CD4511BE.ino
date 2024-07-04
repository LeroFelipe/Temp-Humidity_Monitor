#include "DHT.h"
#define DHT_PIN 8
#define DHT_TYPE DHT11

DHT dht11(DHT_PIN, DHT_TYPE);

// Definir um vetor para as portas digitais 3, 4, 5 e 6
int vetorPortas[10][4] = {
  {0, 0, 0, 0}, // Representa o número 0
  {0, 0, 0, 1}, // Representa o número 1
  {0, 0, 1, 0}, // Representa o número 2
  {0, 0, 1, 1}, // Representa o número 3
  {0, 1, 0, 0}, // Representa o número 4
  {0, 1, 0, 1}, // Representa o número 5
  {0, 1, 1, 0}, // Representa o número 6
  {0, 1, 1, 1}, // Representa o número 7
  {1, 0, 0, 0}, // Representa o número 8
  {1, 0, 0, 1}  // Representa o número 9
};

// Definir os pinos de controle
const int pinDot = 2;
const int pinA = 3;
const int pinB = 4;
const int pinC = 5;
const int pinD = 6;
const int pinUnidade = 9;// Pino que controla a unidade
const int pinDezena = 10; // Pino que controla a dezena

// Função para enviar um número para o CD4511
void enviarNumeroCD4511(int numero) {    
  // Enviar os bits correspondentes ao número para os pinos A, B, C e D
  digitalWrite(pinA, vetorPortas[numero][3]);
  digitalWrite(pinB, vetorPortas[numero][2]);
  digitalWrite(pinC, vetorPortas[numero][1]);
  digitalWrite(pinD, vetorPortas[numero][0]);
}

void setup() {  
  Serial.begin(9600);
  pinMode(pinDot, OUTPUT);
  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);
  pinMode(pinC, OUTPUT);
  pinMode(pinD, OUTPUT);
  pinMode(pinUnidade, OUTPUT);
  pinMode(pinDezena, OUTPUT);
  delay(2000);
  dht11.begin();  
}

void loop() {

  int j = 0;

  // Ler humidade
  int humi  = dht11.readHumidity();
  if (humi >= 100){ humi = 99; }
  // Ler temperatura
  int temperature_C = dht11.readTemperature();
  if (temperature_C < 0){ temperature_C = 0; }
  
  // check if any reads failed
  /*if (isnan(humi) || isnan(temperature_C)) {
    Serial.println("Failed to read from DHT sensor!");
  } else {
    Serial.print("Humidity: ");
    Serial.print(humi);
    Serial.print("%");

    Serial.print("  |  "); 

    Serial.print("Temperature: ");
    Serial.print(temperature_C);
    Serial.print("°C ~ ");
    Serial.println();
  }*/

  while (j < 100){

    digitalWrite(pinDot, HIGH);

    int dezenas = temperature_C / 10;
    int unidades = temperature_C % 10;

    digitalWrite(pinUnidade, HIGH);
    digitalWrite(pinDezena, LOW);
    enviarNumeroCD4511(unidades);
    delay(10);
    
    digitalWrite(pinUnidade, LOW);
    digitalWrite(pinDezena, HIGH);
    enviarNumeroCD4511(dezenas);
    delay(10); 
    j++;
  } 

  while (j < 200){

    digitalWrite(pinDot, LOW);

    int dezenas = humi / 10;
    int unidades = humi % 10;

    digitalWrite(pinUnidade, HIGH);
    digitalWrite(pinDezena, LOW);
    enviarNumeroCD4511(unidades);
    delay(10);
    
    digitalWrite(pinUnidade, LOW);
    digitalWrite(pinDezena, HIGH);
    enviarNumeroCD4511(dezenas);
    delay(10); 
    j++;
  } 
}
