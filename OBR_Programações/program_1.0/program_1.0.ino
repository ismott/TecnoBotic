//Pinos digitais PWM para controlar a velocidade dos motores
#define pinMotor1PWM *number*
#define pinMotor2PWM *number*
#define pinMotor3PWM *number*
#define pinMotor4PWM *number*

//Definição direção do motor 
//OBS: talvez seja bom colocar no terminal que faz a roda ir pra frente em um pino PWM, pra controlar a velocidade
#define motor1A *number*
#define motor1B *number*
#define motor2A *number*
#define motor2B *number*
#define motor3A *number*
#define motor3B *number*
#define motor4A *number*
#define motor4B *number*

//definição sensores infravermelhos
#define pinSen1 *number*
#define pinSen2 *number*
#define pinSen3 *number*

//definições sensor de cor
//Sensor da esquerda:
#define S0A *number*
#define S1A *number*
#define S2A *number*
#define S3A *number*
#define outA *number*
//Sensor da direita:
#define S0B *number*
#define S1B *number*
#define S2B *number*
#define S3B *number*
#define outB *number*

int vermelhoA = 0;
int verdeA = 0;
int azulA = 0;
int brancoA = 0;
int pretoA = 0;

int vermelhoB = 0;
int verdeB = 0;
int azulB = 0;
int brancoB = 0;
int pretoB = 0;

int verdeMin = 35;
int verdeMax = 47;
int vermelhoMin = 44;
int vermelhoMax = 57;
int azulMin = 35;
int azulMax = 47;
int brancoMin = 30;
int brancoMax = 70;

bool detectaVerdeA = false;
bool detectaVerdeB = false;

//velocidade motor
int velocidade = 150;

//variaveis sensor infravermelho
int valorSensor1 = 0;
int valorSensor2 = 0;
int valorSensor3 = 0;

int pretoInfra = 0;
int brancoInfra = 0;

//definições sensor ultrassônico
#include <HCSR04.h>
#define trigger *number*
#define echo *number*
UltraSonicDistanceSensor sensorDist(trigger, echo);
int dist;
#define distObstaculo *number*;

void setup() {
  //setup sensor de cor
  pinMode(S0A, OUTPUT);
  pinMode(S1A, OUTPUT);
  pinMode(S2A, OUTPUT);
  pinMode(S3A, OUTPUT);
  pinMode(outA, INPUT);
  pinMode(S0B, OUTPUT);
  pinMode(S1B, OUTPUT);
  pinMode(S2B, OUTPUT);
  pinMode(S3B, OUTPUT);
  pinMode(outB, INPUT);

  digitalWrite(S0A, HIGH);
  digitalWrite(S1A, LOW);
  digitalWrite(S0B, HIGH);
  digitalWrite(S1B, LOW);
  
  pinMode(pinMotor1PWM, OUTPUT);
  pinMode(pinMotor2PWM, OUTPUT);
  pinMode(pinMotor3PWM, OUTPUT);
  pinMode(pinMotor4PWM, OUTPUT);

  //funcao para definir preto e branco
  detectarPreto();
  detectarBranco();
}

void loop() {
  valorSensor1 = digitalRead(pinSen1);
  valorSensor2 = digitalRead(pinSen2);
  valorSensor3 = digitalRead(pinSen3);

  //armazena o valor de cada cor e verifica se detecta verde
  detectaCor();

  //Verifica se chegou em cima:

  //Verifica se tem obstáculo:
  medirDist();
  if(dist <= distObstaculo){//verifica se identifica algum obstáculo
    //Desvia do obstáculo:
  } else 
  //verifica se é pra seguir linha
  if((valorSensor1 <= brancoInfra) && (valorSensor2 >= pretoInfra) && (valorSensor3 <= brancoInfra) //verificação infravermelhos
    && (detectaVerdeA == false) && (detectaVerdeB == false) && (pretoA != true) && (pretoB != true) //verificação sensor de cor
  ){
    irEmFrente();
  } else if(pretoA == true || pretoB == true){
    if(pretoA == true){
      while(brancoA > 35){
        irPraDireita();
      }
    } else {
      while(brancoB > 35){
        irPraEsquerda();
      }
    }
  }
  else if((valorSensor1 >= pretoInfra) && (valorSensor2 >= pretoInfra) && (valorSensor3 >= pretoInfra) //preto - preto - preto
    || (valorSensor1 == pretoInfra) && (valorSensor2 == pretoInfra) && (valorSensor3 <= brancoInfra) //preto - preto - branco
    || (valorSensor1 <= brancoInfra) && (valorSensor2 >= pretoInfra) && (valorSensor3 >= pretoInfra) //branco - preto - preto
  ) {
    //Robo vai um pouco pra frente
    if(valorSensor2 <= pretoInfra){ //verifica se não tem linha preta no meio, depois do cruzamento
      //Robo volta exatamente o quanto foi pra frente
      if((valorSensor1 >= pretoInfra) && (valorSensor2 >= pretoInfra) && (valorSensor3 <= brancoInfra)){ //verifica se é pra ir pra esquerda
        while(valorSensor3 <= brancoInfra){
          irPraEsquerda();
        }
        while(valorSensor2 <= brancoInfra){
          irPraDireita();
        }
      } else { //se não é pra ir pra esquerda, irá pra a direita
        while(valorSensor1 <= brancoInfra){
          irPraDireita();
        }
        while(valorSensor2 <= brancoInfra){
          irPraEsquerda();
        }
      }
    } else {
      //Robo vai um pouco pra frente
    }
  } else if((detectaVerdeA == true) || (detectaVerdeB == true)){ //verificação do verde
    if((detectaVerdeA == true) && (detectaVerdeB == true)){
      //ir o necessário pra frente para ao dar meia volta, ambos sensores pararem no verde
      while((verdeA <= verdeMin) || (verdeA >= verdeMax) || (azulA <= azulMin) || (azulA >= azulMax) || (vermelhoA <= vermelhoMin) || (vermelhoA >= vermelhoMax) || (brancoA >= brancoMin) || (brancoA <= brancoMax)
      || (verdeB <= verdeMin) || (verdeB >= verdeMax) || (azulB <= azulMin) || (azulB >= azulMax) || (vermelhoB <= vermelhoMin) || (vermelhoB >= vermelhoMax) || (brancoB >= brancoMin) || (brancoB <= brancoMax)){ //enquanto ambos sensores não identificarem verde OBS: mudar pra lógica atual de identificar verde
        darMeiaVolta();
      }
    } else if(detactaVerdeA == true){ //verifica se há verde na esquerda
      //ir um pouco pra frente passando o cruzamento
      if(valorSensor2 >= pretoInfra){ //verifica se tem linha preta no meio
        for(int i = 0; i < 2; i++){ //vai pra esquerda até ver duas linhas pretas, a do meio, e da rota a se seguir
          while(valorSensor3 <= pretoInfra){
            irPraEsquerda();
          }
        }
        while(valorSensor2 <= pretoInfra){
          irPraDireita();
        }
      } else{
        while(valorSensor3 <= pretoInfra){
          irPraEsquerda();
        }
        while(valorSensor2 <= pretoInfra){
          irPraDireita();
        }
      }
    } else { //se não tem na esquerda, é pra ir pra direita
      //ir um pouco pra frente passando o cruzamento
      if(valorSensor2 >= pretoInfra){ //verifica se tem linha preta no meio
        for(int i = 0; i < 2; i++){
          while(valorSensor1 <= pretoInfra){
            irPraDireita();
          }
        }
        while(valorSensor2 <= pretoInfra){
          irPraEsquerda();
        }
      } else{
        while(valorSensor1 <= pretoInfra){
          irPraDireita();
        }
        while(valorSensor2 <= pretoInfra){
          irPraEsquerda();
        }
      }
    }
  } else if ((valorSensor1 <= brancoInfra) && (valorSensor2 <= brancoInfra) && (valorSensor3 >= pretoInfra)
  && (detectaVerdeA == false) && (detectaVerdeB == false)){
    while(valorSensor2 <= pretoInfra){
      irPraDireita();
    }
  } else if ((valorSensor1 >= pretoInfra) && (valorSensor2 <= brancoInfra) && (valorSensor3 <= brancoInfra)
  && (detectaVerdeA == false) && (detectaVerdeB == false)) {
     while(valorSensor2 <= pretoInfra){
      irPraEsquerda();
    }
  } else if((valorSensor1 <= brancoInfra) && (valorSensor2 <= brancoInfra) && (valorSensor3 <= brancoInfra)
  && (detectaVerdeA == false) && (detectaVerdeB == false)){ //Verificação do GAP
    while((valorSensor1 <= brancoInfra) && (valorSensor2 <= brancoInfra) && (valorSensor3 <= brancoInfra)
  && (detectaVerdeA == false) && (detectaVerdeB == false)){// enquanto o GAP for verdadeiro, o robo segue em frente
      irEmFrente();
    }
    while((valorSensor1 >= brancoInfra) && (valorSensor2 <= pretoInfra) && (valorSensor3 >= brancoInfra)){//enquanto condições para seguir linha não estão estabelecidas, ele procura a linha
      irPraDireita();
      delay(1500);
      irPraEsquerda();
      delay(3000);
      irPraDireita();
      delay(1500);
      irEmFrente();
      delay(750);
    }
  } else {
    motorLivre();
    delay(1000);
  }
}

void medirDist(){
  dist = sensorDist.measureDistanceCm();
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
    pretoA = true;
  } else {
    pretoA = false;
  }
  if(brancoB >= 30){//verificação sensor B
    pretoB = true;
  } else {
    pretoB = false;
  }
}

void detectarPreto(){
  pretoInfra = analogRead(pinSen2) - 50;
  delay(700);
}

void detectarBranco(){
  brancoInfra = (analogRead(pinSen1) + analogRead(pinSen3))/2 + 20;
  delay(700);
}

void umPoucoPraFrente(){
  irEmFrente();
  delay(800);
}

void irPersonalizadoCm(int cm, bool sentido){
  int temp = cm*1000/ //numero cm a cada 1 seg;
  if(sentido == true){
    irEmFrente();
    delay(temp);
  } else {
    irPraTras();
    delay(temp);
  }
}

void irEmFrente(){
  //Definindo velocidade dos motores
  analogWrite(pinMotor1PWM, velocidade);
  analogWrite(pinMotor2PWM, velocidade);
  analogWrite(pinMotor3PWM, velocidade);
  analogWrite(pinMotor4PWM, velocidade);
  //motores da direita:
  digitalWrite(motor1A, HIGH);
  digitalWrite(motor1B, LOW);
  digitalWrite(motor2A, HIGH);
  digitalWrite(motor2B, LOW);
  //motores da esquerda:
  digitalWrite(motor3A, HIGH);
  digitalWrite(motor3B, LOW);
  digitalWrite(motor4A, HIGH);
  digitalWrite(motor4B, LOW);
}

void irPraEsquerda(){
  //Definindo velocidade dos motores
  analogWrite(pinMotor1PWM, velocidade);
  analogWrite(pinMotor2PWM, velocidade);
  analogWrite(pinMotor3PWM, velocidade);
  analogWrite(pinMotor4PWM, velocidade);
  //motores da direita:
  digitalWrite(motor1A, HIGH);
  digitalWrite(motor1B, LOW);
  digitalWrite(motor2A, HIGH);
  digitalWrite(motor2B, LOW);
  //motores da esquerda:
  digitalWrite(motor3A, LOW);
  digitalWrite(motor3B, LOW);
  digitalWrite(motor4A, LOW);
  digitalWrite(motor4B, LOW);
}

void irPraDireita(){
  //Definindo velocidade dos motores
  analogWrite(pinMotor1PWM, velocidade);
  analogWrite(pinMotor2PWM, velocidade);
  analogWrite(pinMotor3PWM, velocidade);
  analogWrite(pinMotor4PWM, velocidade);
  //motores da direita:
  digitalWrite(motor1A, LOW);
  digitalWrite(motor1B, LOW);
  digitalWrite(motor2A, LOW);
  digitalWrite(motor2B, LOW);
  //motores da esquerda:
  digitalWrite(motor3A, HIGH);
  digitalWrite(motor3B, LOW);
  digitalWrite(motor4A, HIGH);
  digitalWrite(motor4B, LOW);
}

void irPraTras(){
  //Definindo velocidade dos motores
  analogWrite(pinMotor1PWM, velocidade);
  analogWrite(pinMotor2PWM, velocidade);
  analogWrite(pinMotor3PWM, velocidade);
  analogWrite(pinMotor4PWM, velocidade);
  //motores da direita:
  digitalWrite(motor1A, LOW);
  digitalWrite(motor1B, HIGH);
  digitalWrite(motor2A, LOW);
  digitalWrite(motor2B, HIGH);
  //motores da esquerda:
  digitalWrite(motor3A, LOW);
  digitalWrite(motor3B, HIGH);
  digitalWrite(motor4A, LOW);
  digitalWrite(motor4B, HIGH);
}

void darMeiaVolta(){
  //Definindo velocidade dos motores
  analogWrite(pinMotor1PWM, velocidade);
  analogWrite(pinMotor2PWM, velocidade);
  analogWrite(pinMotor3PWM, velocidade);
  analogWrite(pinMotor4PWM, velocidade);
  //motores da direita:
  digitalWrite(motor1A, HIGH);
  digitalWrite(motor1B, LOW);
  digitalWrite(motor2A, HIGH);
  digitalWrite(motor2B, LOW);
  //motores da esquerda:
  digitalWrite(motor3A, LOW);
  digitalWrite(motor3B, HIGH);
  digitalWrite(motor4A, LOW);
  digitalWrite(motor4B, HIGH);
}

void parar(){
  //motores da direita:
  digitalWrite(motor1A, HIGH);
  digitalWrite(motor1B, HIGH);
  digitalWrite(motor2A, HIGH);
  digitalWrite(motor2B, HIGH);
  //motores da esquerda:
  digitalWrite(motor3A, HIGH);
  digitalWrite(motor3B, HIGH);
  digitalWrite(motor4A, HIGH);
  digitalWrite(motor4B, HIGH);
}

void motorLivre(){
  //motores da direita:
  digitalWrite(motor1A, LOW);
  digitalWrite(motor1B, LOW);
  digitalWrite(motor2A, LOW);
  digitalWrite(motor2B, LOW);
  //motores da esquerda:
  digitalWrite(motor3A, LOW);
  digitalWrite(motor3B, LOW);
  digitalWrite(motor4A, LOW);
  digitalWrite(motor4B, LOW);
}
