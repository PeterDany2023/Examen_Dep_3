#include <Servo.h>
const int trigPin = 8;
const int echoPin = 9;
const int servoPin = 3;
Servo miServo;
float distanciaAnterior = 0;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  miServo.attach(servoPin);
  Serial.begin(9600); 
}

void loop() {
  // Enviar pulso al sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Leer tiempo de retorno
  long duracion = pulseIn(echoPin, HIGH);
  float distancia = duracion * 0.034 / 2;

  // Mostrar distancia (opcional)
  Serial.print("Distancia: ");
  Serial.println(distancia);

  // Detectar movimiento
  float diferencia = abs(distancia - distanciaAnterior);
  if (diferencia > 2.0) {
    Serial.println("Movimiento");
  } else {
    Serial.println("Sin movimiento");
  }
  distanciaAnterior = distancia;

  // Mover servo (opcional)
  if (distancia < 10) {
    miServo.write(0);
  } else if (distancia < 20) {
    miServo.write(90);
  } else {
    miServo.write(180);
  }

  delay(300);
}
