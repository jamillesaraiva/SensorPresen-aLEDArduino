#include <TimeLib.h>

#define SENSOR_PIR 2
#define LED 8

bool estado_sensor = false;
bool movimento_detectado = false;

void setup() {
  pinMode(SENSOR_PIR, INPUT);
  pinMode(LED, OUTPUT);
  Serial.begin(9600);

  // Configura a hora inicial
  setTime(18, 0, 0, 1, 1, 2024); // 18h00 de 1º de janeiro de 2024
}

void loop() {
  estado_sensor = digitalRead(SENSOR_PIR);

  // Verifica se estamos dentro do horário de funcionamento
  if (hour() >= 18 || hour() < 6) {
    // Dentro do horário, verifica o movimento
    if (estado_sensor) {
      if (!movimento_detectado) {
        digitalWrite(LED, HIGH);
        Serial.println("MOVIMENTO DETECTADO");
        movimento_detectado = true;
      }
    } else {
      if (movimento_detectado) {
        digitalWrite(LED, LOW);
        Serial.println("SEM MOVIMENTO");
        movimento_detectado = false;
      }
    }
  } else {
    // Fora do horário, mantém o LED apagado
    digitalWrite(LED, LOW);
    Serial.println("FORA DO HORÁRIO");
  }

  delay(100);
}

