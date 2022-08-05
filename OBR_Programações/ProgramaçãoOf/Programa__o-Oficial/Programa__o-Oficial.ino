//Programa Oficial
//Definições motores
#define motor1A 6
#define motor1B 7
#define motor2A 2
#define motor2B 3
#define motor3A 9
#define motor3B 8
#define motor4A 5
#define motor4B 4

int velocidade = 255;

//definições sensor de cor
//Sensor da esquerda:
#define S0A 50
#define S1A 51
#define S2A 53
#define S3A 52
#define outA 49
#define LED 13
//Sensor da direita:
#define S0B 44
#define S1B 45
#define S2B 42
#define S3B 46
#define outB 47

int vermelhoA = 0;
int verdeA = 0;
int azulA = 0;
int brancoA = 0;

int vermelhoB = 0;
int verdeB = 0;
int azulB = 0;
int brancoB = 0;

int verdeMin = 20;
int verdeMax = 30;
int vermelhoMin = 45;
int vermelhoMax = 55;
int azulMin = 20;
int azulMax = 30;
int brancoMin = 5;
int brancoMax = 15;

bool detectaVerdeA = false;
bool detectaVerdeB = false;
bool detectaPretoA = false;
bool detectaPretoB = false;

//definição sensores infravermelhos
#define pinSen1 A3
#define pinSen2 A2
#define pinSen3 A1
int valorSensor1;
int valorSensor2;
int valorSensor3;

int pretoInfra;
int brancoInfra;

//Definicoes sensor ultrassonico
#include <HCSR04.h>
#define trigger 10
#define echo 11
UltraSonicDistanceSensor sensorDist(trigger, echo);
int dist;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //definição motores
  pinMode(motor1A, OUTPUT);
  pinMode(motor1B, OUTPUT);
  pinMode(motor2A, OUTPUT);
  pinMode(motor2B, OUTPUT);
  pinMode(motor3A, OUTPUT);
  pinMode(motor3B, OUTPUT);
  pinMode(motor4A, OUTPUT);
  pinMode(motor4B, OUTPUT);

  //setup sensor de cor
  pinMode(S0A, OUTPUT);
  pinMode(S1A, OUTPUT);
  pinMode(S2A, OUTPUT);
  pinMode(S3A, OUTPUT);
  pinMode(outA, INPUT);
  pinMode(LED, OUTPUT);

  pinMode(S0B, OUTPUT);
  pinMode(S1B, OUTPUT);
  pinMode(S2B, OUTPUT);
  pinMode(S3B, OUTPUT);
  pinMode(outB, INPUT);

  digitalWrite(S0A, HIGH);
  digitalWrite(S1A, LOW);

  digitalWrite(S0B, HIGH);
  digitalWrite(S1B, LOW);

  //sensorInfraVermelho:
  pinMode(pinSen1, INPUT);
  pinMode(pinSen2, INPUT);
  pinMode(pinSen3, INPUT);
  detectarBranco();
}

void loop() {
  // put your main code here, to run repeatedly:
  detectaCor();
  atualizaSensores();
  medirDist();
  Serial.println(valorSensor1);
  Serial.println(valorSensor2);
  Serial.println(valorSensor3);
  /*if ((valorSensor1 > brancoInfra) || (valorSensor2 <= brancoInfra) || (valorSensor3 > brancoInfra)
      || (detectaVerdeA == true) || (detectaVerdeB) || (detectaPretoA == true) || (detectaPretoB == true)
     ) {
    if ((detectaPretoA == true) || (detectaPretoB == true)) {
      if (detectaPretoA == true) {
        atualizaSensores();
        while (valorSensor2 < brancoInfra) {
          atualizaSensores();
          irPraEsquerda();
        }
      } else {
        atualizaSensores();
        while (valorSensor2 < brancoInfra) {
          atualizaSensores();
          irPraDireita();
        }
      }
    } else if ((valorSensor1 > brancoInfra) && (valorSensor2 > brancoInfra) && (valorSensor3 > brancoInfra)) { //preto - preto - preto
      while ((detectaPretoA == false) && (detectaPretoB == false)) {
        atualizaSensores();
        if ((detectaVerdeA == true) || (detectaVerdeB == true)) {
          detectaPretoA = true;
          detectaPretoB = true;
          if ((detectaVerdeA == true) && (detectaVerdeB == true)) {
            darMeiaVolta();
            delay(800);
            while (valorSensor2 < brancoInfra) {
              atualizaSensores();
              darMeiaVolta();
            }
          } else if (detectaVerdeA == true) {
            atualizaSensores();
            irEmFrente();
            delay(800);
            if (valorSensor2 > brancoInfra) {
              while (valorSensor3 <= brancoInfra) {
                atualizaSensores();
                irPraEsquerda();
              }
              irPraEsquerda();
              delay(400);
              while (valorSensor2 <= brancoInfra) {
                atualizaSensores();
                irPraEsquerda();
              }
            } else {
              while (valorSensor2 <= brancoInfra) {
                atualizaSensores();
                irPraEsquerda();
              }
            }
          } else {
            atualizaSensores();
            if (valorSensor2 > brancoInfra) {
              while (valorSensor1 <= brancoInfra) {
                atualizaSensores();
                irPraEsquerda();
              }
              irPraDireita();
              delay(400);
              while (valorSensor2 <= brancoInfra) {
                atualizaSensores();
                irPraDireita();
              }
            } else {
              while (valorSensor2 <= brancoInfra) {
                atualizaSensores();
                irPraEsquerda();
              }
            }
          }
          irEmFrente();
        }
      detectaPretoA = false;
      detectaPretoB = false;
    } else if ((valorSensor1 > brancoInfra) && (valorSensor2 > brancoInfra) && (valorSensor3 <= brancoInfra)) { //preto - preto - branco
      irEmFrente();
      delay(400);
      irPraEsquerda();
      delay(400);
      while (valorSensor2 <= brancoInfra) {
        atualizaSensores();
        irPraEsquerda();
      }
    } else if ((valorSensor1 <= brancoInfra) && (valorSensor2 > brancoInfra) && (valorSensor3 > brancoInfra)) { // branco - preto - preto
      irEmFrente();
      delay(400);
      irPraDireita();
      delay(400);
      while (valorSensor2 <= brancoInfra) {
        atualizaSensores();
        irPraDireita();
      }
    } else if ((valorSensor1 > brancoInfra) && (valorSensor2 <= brancoInfra) && (valorSensor3 <= brancoInfra)) { // preto - branco - branco
      while (valorSensor2 <= brancoInfra) {
        atualizaSensores();
        irPraEsquerda();
      }
    } else if ((valorSensor1 <= brancoInfra) && (valorSensor2 <= brancoInfra) && (valorSensor3 > brancoInfra)) { // branco - branco - preto
      while (valorSensor2 <= brancoInfra) {
        atualizaSensores();
        irPraDireita();
      }
    } else if ((valorSensor1 <= brancoInfra) && (valorSensor2 <= brancoInfra) && (valorSensor3 <= brancoInfra)) { // branco - branco - branco
      while ((valorSensor1 <= brancoInfra) && (valorSensor2 <= brancoInfra) && (valorSensor3 <= brancoInfra) && (detectaPretoA == false) && (detectaPretoB == false)) {
        atualizaSensores();
        irEmFrente();
      }
    }
    } else {
    irEmFrente();
    delay(10);
    } */
  
  if ((valorSensor1 > brancoInfra) || (valorSensor2 <= brancoInfra) || (valorSensor3 > brancoInfra)
      || (detectaVerdeA == true) || (detectaVerdeB) || (detectaPretoA == true) || (detectaPretoB == true)
     ) {
    if (valorSensor1 > brancoInfra) {
      while (valorSensor2 <= brancoInfra) {
        atualizaSensores();
        irPraEsquerda();
      }
    } else if (valorSensor3 > brancoInfra) {
      while (valorSensor2 <= brancoInfra) {
        atualizaSensores();
        irPraDireita();
      }
    }
  } else {
    irEmFrente();
  }
}

void detectarPreto() {
  pretoInfra = analogRead(pinSen2) - 50;
  delay(700);
}

void detectarBranco() {
  brancoInfra = (analogRead(pinSen1) + analogRead(pinSen3)) / 2 + 20;
  delay(700);
}

void detectaCor() {
  //Vermelho
  digitalWrite(S2A, LOW);
  digitalWrite(S3A, LOW);
  vermelhoA = pulseIn(outA, digitalRead(outA) == HIGH ? LOW : HIGH);
  digitalWrite(S2B, LOW);
  digitalWrite(S3B, LOW);
  vermelhoB = pulseIn(outB, digitalRead(outB) == HIGH ? LOW : HIGH);

  //Sem filtro
  digitalWrite(S2A, HIGH);
  brancoA = pulseIn(outA, digitalRead(outA) == HIGH ? LOW : HIGH);
  digitalWrite(S2B, HIGH);
  brancoB = pulseIn(outB, digitalRead(outB) == HIGH ? LOW : HIGH);

  //Azul
  digitalWrite(S2A, LOW);
  digitalWrite(S3A, HIGH);
  azulA = pulseIn(outA, digitalRead(outA) == HIGH ? LOW : HIGH);
  digitalWrite(S2B, LOW);
  digitalWrite(S3B, HIGH);
  azulB = pulseIn(outB, digitalRead(outB) == HIGH ? LOW : HIGH);

  //Verde
  digitalWrite(S2A, HIGH);
  verdeA = pulseIn(outA, digitalRead(outA) == HIGH ? LOW : HIGH);
  digitalWrite(S2B, HIGH);
  verdeB = pulseIn(outB, digitalRead(outB) == HIGH ? LOW : HIGH);

  //verificação se algum sensor de cor detecta verde
  if ((verdeA >= verdeMin) && (verdeA <= verdeMax) && (azulA >= azulMin) && (azulA <= azulMax) && (vermelhoA > vermelhoMin) && (vermelhoA < vermelhoMax) && (brancoA >= brancoMin) && (brancoA <= brancoMax)) {
    detectaVerdeA = true;
  } else {
    detectaVerdeA = false;
  }
  if ((verdeB >= verdeMin) && (verdeB <= verdeMax) && (azulB >= azulMin) && (azulB <= azulMax) && (vermelhoB > vermelhoMin) && (vermelhoB < vermelhoMax) && (brancoB >= brancoMin) && (brancoB <= brancoMax)) {
    detectaVerdeB = true;
  } else {
    detectaVerdeB = false;
  }
  //verificação se identificam preto
  if ((vermelhoA >= 10) && (vermelhoA <= 21) && (verdeA >= 10) && (verdeA <= 21) && (azulA <= vermelhoA)) { //verificação sensor A
    detectaPretoA = true;
  } else {
    detectaPretoA = false;
  }
  if ((vermelhoB >= 10) && (vermelhoB <= 21) && (verdeB >= 10) && (verdeB <= 21) && (azulB <= vermelhoB)) { //verificação sensor A
    detectaPretoB = true;
  } else {
    detectaPretoB = false;
  }
}


void medirDist() {
  dist = sensorDist.measureDistanceCm();
}

void atualizaSensores() {
  valorSensor1 = analogRead(pinSen1);
  valorSensor2 = analogRead(pinSen2);
  valorSensor3 = analogRead(pinSen3);
  detectaCor();
}

void umPoucoPraFrente() {
  irEmFrente();
  delay(800);
}

void irEmFrente() {
  //motores da direita:
  analogWrite(motor1A, velocidade);
  analogWrite(motor1B, 0);
  analogWrite(motor2A, velocidade);
  analogWrite(motor2B, 0);
  //motores da esquerda:
  analogWrite(motor3A, velocidade);
  analogWrite(motor3B, 0);
  analogWrite(motor4A, velocidade);
  analogWrite(motor4B, 0);
}

void irPraEsquerda() {
  //motores da direita:
  analogWrite(motor1A, velocidade);
  analogWrite(motor1B, 0);
  analogWrite(motor2A, velocidade);
  analogWrite(motor2B, 0);
  //motores da esquerda:
  analogWrite(motor3A, 0);
  analogWrite(motor3B, velocidade);
  analogWrite(motor4A, 0);
  analogWrite(motor4B, velocidade);
}

void irPraDireita() {
  //motores da direita:
  analogWrite(motor1A, 0);
  analogWrite(motor1B, velocidade);
  analogWrite(motor2A, 0);
  analogWrite(motor2B, velocidade);
  //motores da esquerda:
  analogWrite(motor3A, velocidade);
  analogWrite(motor3B, 0);
  analogWrite(motor4A, velocidade);
  analogWrite(motor4B, 0);
}

void irPraTras() {
  //motores da direita:
  analogWrite(motor1A, 0);
  analogWrite(motor1B, velocidade);
  analogWrite(motor2A, 0);
  analogWrite(motor2B, velocidade);
  //motores da esquerda:
  analogWrite(motor3A, 0);
  analogWrite(motor3B, velocidade);
  analogWrite(motor4A, 0);
  analogWrite(motor4B, velocidade);
}

void darMeiaVolta() {
  //motores da direita:
  analogWrite(motor1A, velocidade);
  analogWrite(motor1B, 0);
  analogWrite(motor2A, velocidade);
  analogWrite(motor2B, 0);
  //motores da esquerda:
  analogWrite(motor3A, 0);
  analogWrite(motor3B, velocidade);
  analogWrite(motor4A, 0);
  analogWrite(motor4B, velocidade);
}

void parar() {
  //motores da direita:
  analogWrite(motor1A, 255);
  analogWrite(motor1B, 255);
  analogWrite(motor2A, 255);
  analogWrite(motor2B, 255);
  //motores da esquerda:
  analogWrite(motor3A, 255);
  analogWrite(motor3B, 255);
  analogWrite(motor4A, 255);
  analogWrite(motor4B, 255);
}

void motorLivre() {
  //motores da direita:
  analogWrite(motor1A, 0);
  analogWrite(motor1B, 0);
  analogWrite(motor2A, 0);
  analogWrite(motor2B, 0);
  //motores da esquerda:
  analogWrite(motor3A, 0);
  analogWrite(motor3B, 0);
  analogWrite(motor4A, 0);
  analogWrite(motor4B, 0);
}
