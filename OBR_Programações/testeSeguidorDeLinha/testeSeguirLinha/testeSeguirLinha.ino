//Definição direção do motor 
//OBS: talvez seja bom colocar no terminal que faz a roda ir pra frente em um pino PWM, pra controlar a velocidade
#define motor1A 5
#define motor1B 4
#define motor2A 9
#define motor2B 8
#define motor3A 2
#define motor3B 3
#define motor4A 6
#define motor4B 7
 
int velocidadeMotor = 100;

//definição sensores infravermelhos
#define pinSen1 A3
#define pinSen2 A2
#define pinSen3 A1

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
#define S2B 43
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

int verdeMin = 45;
int verdeMax = 54;
int vermelhoMin = 54;
int vermelhoMax = 62;
int azulMin = 38;
int azulMax = 48;
int brancoMin = 15;
int brancoMax = 25;

bool detectaVerdeA = false;
bool detectaVerdeB = false;
bool detectaPretoA = false;
bool detectaPretoB = false;

//variaveis sensor infravermelho
int valorSensor1;
int valorSensor2;
int valorSensor3;

int pretoInfra;
int brancoInfra;

//definições sensor ultrassônico
#include <HCSR04.h>
#define trigger 10
#define echo 11
UltraSonicDistanceSensor sensorDist(trigger, echo);
int dist;

void setup() {
  //sensorInfraVermelho:
  pinMode(pinSen1, INPUT);
  pinMode(pinSen2, INPUT);
  pinMode(pinSen3, INPUT);
  
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

  //motor
  pinMode(motor1A, OUTPUT);
  pinMode(motor1B, OUTPUT);
  pinMode(motor2A, OUTPUT);
  pinMode(motor2B, OUTPUT);
  pinMode(motor3A, OUTPUT);
  pinMode(motor3B, OUTPUT);
  pinMode(motor4A, OUTPUT);
  pinMode(motor4B, OUTPUT);

  //funcao para definir preto e branco
  //detectarPreto();
  detectarBranco();

  Serial.begin(9600);
}

void loop() {
  valorSensor1 = analogRead(pinSen1);
  valorSensor2 = analogRead(pinSen2);
  valorSensor3 = analogRead(pinSen3);

  //armazena o valor de cada cor e verifica se detecta verde
  detectaCor();

  //Verifica se chegou em cima:
   Serial.println(valorSensor2);

   /*if((valorSensor1 >= brancoInfra) || (valorSensor2 <= brancoInfra) || (valorSensor3 >= brancoInfra)
   || (detectaPretoA == true) || (detectaPretoB == true)  
   ){
     if((valorSensor1 >= brancoInfra) && (valorSensor2 <= brancoInfra) && (valorSensor3 <= brancoInfra)){
       atualizaSensores();
       while(valorSensor2 <= brancoInfra){
        atualizaSensores();
        irPraEsquerda();
       }
     } else if((valorSensor1 <= brancoInfra) && (valorSensor2 <= brancoInfra) && (valorSensor3 >= brancoInfra)){
      atualizaSensores();
       while(valorSensor2 <= brancoInfra){
        atualizaSensores();
        irPraDireita();
       }
     }
   } else {
    irEmFrente();
   }*/
   irEmFrente();
  }

void medirDist(){
  dist = sensorDist.measureDistanceCm();
}

void atualizaSensores(){
  valorSensor1 = analogRead(pinSen1);
  valorSensor2 = analogRead(pinSen2);
  valorSensor3 = analogRead(pinSen3);
  detectaCor();
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
  if((verdeA >= verdeMin) && (verdeA <= verdeMax) && (azulA >= azulMin) && (azulA <= azulMax) && (vermelhoA > vermelhoMin) && (vermelhoA < vermelhoMax) && (brancoA >= brancoMin) && (brancoA <= brancoMax)){
    detectaVerdeA = true;
  } else {
    detectaVerdeA = false;
  }
  if((verdeB >= verdeMin) && (verdeB <= verdeMax) && (azulB >= azulMin) && (azulB <= azulMax) && (vermelhoB > vermelhoMin) && (vermelhoB < vermelhoMax) && (brancoB >= brancoMin) && (brancoB <= brancoMax)){
    detectaVerdeB = true;
  } else {
    detectaVerdeB = false;
  } 
  //verificação se identificam preto
  if(brancoA >= 30){//verificação sensor A
    detectaPretoA = true;
  } else {
    detectaPretoA = false;
  }
  if(brancoB >= 30){//verificação sensor B
    detectaPretoB = true;
  } else {
    detectaPretoB = false;
  }
}

void detectarPreto(){
  pretoInfra = analogRead(pinSen2) - 50;
  delay(500);
}

void detectarBranco(){
  brancoInfra = (analogRead(pinSen1) + analogRead(pinSen3))/2 + 60;
  delay(700);
}

void umPoucoPraFrente(){
  irEmFrente();
  delay(800);
}

void irEmFrente(){
  //motores da direita:
  analogWrite(motor1A, velocidadeMotor);
  analogWrite(motor1B, 0);
  analogWrite(motor2A, velocidadeMotor);
  analogWrite(motor2B, 0);
  //motores da esquerda:
  analogWrite(motor3A, velocidadeMotor);
  analogWrite(motor3B, 0);
  analogWrite(motor4A, velocidadeMotor);
  analogWrite(motor4B, 0);
}

void irPraEsquerda(){
  //motores da direita:
  analogWrite(motor1A, velocidadeMotor);
  analogWrite(motor1B, 0);
  analogWrite(motor2A, velocidadeMotor);
  analogWrite(motor2B, 0);
  //motores da esquerda:
  analogWrite(motor3A, 0);
  analogWrite(motor3B, velocidadeMotor - 50);
  analogWrite(motor4A, 0);
  analogWrite(motor4B, velocidadeMotor - 50);
}

void irPraDireita(){
  //motores da direita:
  analogWrite(motor1A, 0);
  analogWrite(motor1B, velocidadeMotor - 50);
  analogWrite(motor2A, 0);
  analogWrite(motor2B, velocidadeMotor - 50);
  //motores da esquerda:
  analogWrite(motor3A, velocidadeMotor);
  analogWrite(motor3B, 0);
  analogWrite(motor4A, velocidadeMotor);
  analogWrite(motor4B, 0);
}

void irPraTras(){
  //motores da direita:
  analogWrite(motor1A, 0);
  analogWrite(motor1B, velocidadeMotor);
  analogWrite(motor2A, 0);
  analogWrite(motor2B, velocidadeMotor);
  //motores da esquerda:
  analogWrite(motor3A, 0);
  analogWrite(motor3B, velocidadeMotor);
  analogWrite(motor4A, 0);
  analogWrite(motor4B, velocidadeMotor);
}

void darMeiaVolta(){
  //motores da direita:
  analogWrite(motor1A, velocidadeMotor);
  analogWrite(motor1B, 0);
  analogWrite(motor2A, velocidadeMotor);
  analogWrite(motor2B, 0);
  //motores da esquerda:
  analogWrite(motor3A, 0);
  analogWrite(motor3B, velocidadeMotor);
  analogWrite(motor4A, 0);
  analogWrite(motor4B, velocidadeMotor);
}

void parar(){
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

void motorLivre(){
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
