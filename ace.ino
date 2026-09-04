#include <ESP32Servo.h>

const int PINO_SERVO = 18;
Servo servoFaceCima;

const int POSICAO_INICIAL = 0;
const int POSICAO_GIRADA  = 90;

const int PINO_S0 = 25;
const int PINO_S1 = 26;
const int PINO_S2 = 27;
const int PINO_S3 = 14;
const int PINO_OUT = 33;

void setup() {
  Serial.begin(115200);

  servoFaceCima.attach(PINO_SERVO);
  servoFaceCima.write(POSICAO_INICIAL);

  pinMode(PINO_S0, OUTPUT);
  pinMode(PINO_S1, OUTPUT);
  pinMode(PINO_S2, OUTPUT);
  pinMode(PINO_S3, OUTPUT);
  pinMode(PINO_OUT, INPUT);

  digitalWrite(PINO_S0, HIGH);
  digitalWrite(PINO_S1, LOW);

  Serial.println("CUBE EXPERT pronto.");
  Serial.println("Comandos: G = girar face | R = retornar | C = ler cor");
}

void loop() {
  if (Serial.available() > 0) {
    char comando = Serial.read();

    switch (comando) {
      case 'G':
      case 'g':
        girarFace();
        break;

      case 'R':
      case 'r':
        retornarFace();
        break;

      case 'C':
      case 'c':
        lerCor();
        break;
    }
  }
}

void girarFace() {
  Serial.println("Girando face...");
  servoFaceCima.write(POSICAO_GIRADA);
  delay(500); 
  Serial.println("Face girada.");
}

void retornarFace() {
  Serial.println("Retornando face...");
  servoFaceCima.write(POSICAO_INICIAL);
  delay(500);
  Serial.println("Face na posição inicial.");
}

void lerCor() {
  int vermelho, verde, azul;

  // Lê o canal vermelho
  digitalWrite(PINO_S2, LOW);
  digitalWrite(PINO_S3, LOW);
  vermelho = pulseIn(PINO_OUT, LOW);

  // Lê o canal verde
  digitalWrite(PINO_S2, HIGH);
  digitalWrite(PINO_S3, HIGH);
  verde = pulseIn(PINO_OUT, LOW);

  // Lê o canal azul
  digitalWrite(PINO_S2, LOW);
  digitalWrite(PINO_S3, HIGH);
  azul = pulseIn(PINO_OUT, LOW);

  Serial.print("Cor detectada -> R: ");
  Serial.print(vermelho);
  Serial.print(" | G: ");
  Serial.print(verde);
  Serial.print(" | B: ");
  Serial.println(azul);
}
