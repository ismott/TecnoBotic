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
bool pretoA = false;
bool pretoB = false;

void setup() {
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

  Serial.begin(9600);

}

void loop() {
  detectaCor();
  Serial.println(brancoA);
  Serial.println(brancoB);
  Serial.println();
  delay(1000);
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
  if((vermelhoA >= 10) && (vermelhoA <= 21) && (verdeA >= 10) && (verdeA <= 21) && (azulA <= vermelhoA)){//verificação sensor A
    pretoA = true;
  } else {
    pretoA = false;
  }
  if((vermelhoB >= 10) && (vermelhoB <= 21) && (verdeB >= 10) && (verdeB <= 21) && (azulB <= vermelhoB)){//verificação sensor A
    pretoB = true;
  } else {
    pretoB = false;
  }
}
