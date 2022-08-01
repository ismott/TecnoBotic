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

int vermelhoB = 0;
int verdeB = 0;
int azulB = 0;
int brancoB = 0;

bool detectaVerdeA = false;
bool detectaVerdeA = false;

//velocidade motor
int velocidade = 150;

int valorSensor1 = 0;
int valorSensor2 = 0;
int valorSensor3 = 0;

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
}

void loop() {
  valorSensor1 = digitalRead(pinSen1);
  valorSensor2 = digitalRead(pinSen2);
  valorSensor3 = digitalRead(pinSen3);

  //armazena o valor de cada cor e verifica se detecta verde
  detectaCor();

  //Verifica se chegou em cima:

  //Verifica se tem obstáculo:

  
  //verifica se é pra seguir linha
  if((valorSensor1 == *branco*) && (valorSensor2 == *preto*) && (valorSensor3 == *branco*) //verificação infravermelhos
    && (detectaVerdeA == false) && (detectaVerdeB == false) //verificação sensor de cor
  ){
    irEmFrente();
  } else if((valorSensor1 == *preto*) && (valorSensor2 == *preto*) && (valorSensor3 == *preto*) //preto - preto - preto
    || (valorSensor1 == *preto*) && (valorSensor2 == *preto*) && (valorSensor3 == *branco*) //preto - preto - branco
    || (valorSensor1 == *branco*) && (valorSensor2 == *preto*) && (valorSensor3 == *preto*) //branco - preto - preto
  ) {
    //Robo vai um pouco pra frente
    if(valorSensor2 != *preto*){ //verifica se não tem linha preta no meio, depois do cruzamento
      //Robo volta exatamente o quanto foi pra frente
      if((valorSensor1 == *preto*) && (valorSensor2 == *preto*) && (valorSensor3 == *branco*)){ //verifica se é pra ir pra esquerda
        while(valorSensor3 == *branco){
          irPraEsquerda();
        }
        while(valorSensor2 == *branco*){
          irPraDireita();
        }
      } else { //se não é pra ir pra esquerda, irá pra a direita
        while(valorSensor1 == *branco){
          irPraDireita();
        }
        while(valorSensor2 == *branco*){
          irPraEsquerda();
        }
      }
    } else {
      //Robo vai um pouco pra frente
    }
  } else if((detectaVerdeA == true) || (detectaVerdeB == true)){ //verificação do verde
    if((detectaVerdeA == true) && (detectaVerdeB == true)){
      //ir o necessário pra frente para ao dar meia volta, ambos sensores pararem no verde
      while((verdeA > vermelhoA) && (verdeA > azulA) && (brancoA > 100)
      && (verdeB > vermelhoB) && (verdeB > azulB) && (brancoB > 100)){ //enquanto ambos sensores não identificarem verde
        darMeiaVolta();
      }
    } else if(detactaVerdeA == true){ //verifica se há verde na esquerda
      //ir um pouco pra frente passando o cruzamento
      if(valorSensor2 == *preto*){ //verifica se tem linha preta no meio
        for(int i = 0; i < 2; i++){ //vai pra esquerda até ver duas linhas pretas, a do meio, e da rota a se seguir
          while(valorSensor3 != *preto*){
            irPraEsquerda();
          }
        }
        while(valorSensor2 != *preto*){
          irPraDireita();
        }
      } else{
        while(valorSensor3 != *preto*){
          irPraEsquerda();
        }
        while(valorSensor2 != *preto*){
          irPraDireita();
        }
      }
    } else { //se não tem na esquerda, é pra ir pra direita
      //ir um pouco pra frente passando o cruzamento
      if(valorSensor2 == *preto*){ //verifica se tem linha preta no meio
        for(int i = 0; i < 2; i++){
          while(valorSensor1 != *preto*){
            irPraDireita();
          }
        }
        while(valorSensor2 != *preto*){
          irPraEsquerda();
        }
      } else{
        while(valorSensor1 != *preto*){
          irPraDireita();
        }
        while(valorSensor2 != *preto*){
          irPraEsquerda();
        }
      }
    }
  } else if ((valorSensor1 == *branco*) && (valorSensor2 == *branco*) && (valorSensor3 == *preto*)
  && (detectaVerdeA == false) && (detectaVerdeB == false)){
    while(valorSensor2 != *preto*){
      irPraDireita();
    }
  } else if ((valorSensor1 == *preto*) && (valorSensor2 == *branco*) && (valorSensor3 == *branco*)
  && (detectaVerdeA == false) && (detectaVerdeB == false)) {
     while(valorSensor2 != *preto*){
      irPraEsquerda();
    }
  } else if((valorSensor1 == *branco*) && (valorSensor2 == *branco*) && (valorSensor3 == *branco*)
  && (detectaVerdeA == false) && (detectaVerdeB == false)){ //Verificação do GAP
    while((valorSensor1 == *branco*) && (valorSensor2 == *branco*) && (valorSensor3 == *branco*)
  && (detectaVerdeA == false) && (detectaVerdeB == false)){// enquanto o GAP for verdadeiro, o robo segue em frente
      irEmFrente();
    }
    while((valorSensor1 != *branco*) && (valorSensor2 != *preto*) && (valorSensor3 != *branco*)){//enquanto condições para seguir linha não estão estabelecidas, ele procura a linha
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

// ******* Função de leitura so sensor de cor *************
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
  if((verdeA < vermelhoA) && (verdeA < azulA) && (brancoA < 100)){
    detectaVerdeA = true;
  }
  if((verdeB < vermelhoB) && (verdeB < azulB) && (brancoB < 100)){
    detectaVerdeB = true;
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
