#define motor1A 6
#define motor1B 7
#define motor2A 2
#define motor2B 3
#define motor3A 9
#define motor3B 8
#define motor4A 5
#define motor4B 4

int velocidade = 255;

void setup() {
  // put your setup code here, to run once:
  pinMode(motor1A, OUTPUT);
  pinMode(motor1B, OUTPUT);
  pinMode(motor2A, OUTPUT);
  pinMode(motor2B, OUTPUT);
  pinMode(motor3A, OUTPUT);
  pinMode(motor3B, OUTPUT);
  pinMode(motor4A, OUTPUT);
  pinMode(motor4B, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(motor1A, velocidade);
  analogWrite(motor1B, 0);
  delay(500);
}

void umPoucoPraFrente(){
  irEmFrente();
  delay(800);
}

void irEmFrente(){
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

void irPraEsquerda(){
  //motores da direita:
  analogWrite(motor1A, velocidade);
  analogWrite(motor1B, 0);
  analogWrite(motor2A, velocidade);
  analogWrite(motor2B, 0);
  //motores da esquerda:
  analogWrite(motor3A, 0);
  analogWrite(motor3B, 0);
  analogWrite(motor4A, 0);
  analogWrite(motor4B, 0);
}

void irPraDireita(){
  //motores da direita:
  analogWrite(motor1A, 0);
  analogWrite(motor1B, 0);
  analogWrite(motor2A, 0);
  analogWrite(motor2B, 0);
  //motores da esquerda:
  analogWrite(motor3A, velocidade);
  analogWrite(motor3B, 0);
  analogWrite(motor4A, velocidade);
  analogWrite(motor4B, 0);
}

void irPraTras(){
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

void darMeiaVolta(){
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
