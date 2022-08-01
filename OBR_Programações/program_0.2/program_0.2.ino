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

int velocidade = 150;

int valorSensor1 = 0;
int valorSensor2 = 0;
int valorSensor3 = 0;

void setup() {
  pinMode(pinMotor1PWM, OUTPUT);
  pinMode(pinMotor2PWM, OUTPUT);
  pinMode(pinMotor3PWM, OUTPUT);
  pinMode(pinMotor4PWM, OUTPUT);

  pinMode(motor1A, OUTPUT);
}

void loop() {
  valorSensor1 = digitalRead(pinSen1);
  valorSensor2 = digitalRead(pinSen2);
  valorSensor3 = digitalRead(pinSen3);
  
  //verifica se é pra seguir linha
  if((valorSensor1 == *branco*) && (valorSensor2 == *preto*) && (valorSensor3 == *branco*)){
    irEmFrente();
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
