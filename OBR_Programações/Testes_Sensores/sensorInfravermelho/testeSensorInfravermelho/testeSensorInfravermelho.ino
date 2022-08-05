#define pinSen1 A3
#define pinSen2 A2
#define pinSen3 A1

int valorSensor1;
int valorSensor2;
int valorSensor3;

int pretoInfra;
int brancoInfra;

void setup() {
  // put your setup code here, to run once:
  //sensorInfraVermelho:
  pinMode(pinSen1, INPUT);
  pinMode(pinSen2, INPUT);
  pinMode(pinSen3, INPUT);
  Serial.begin(9600);
  detectarPreto();
  detectarBranco();
}

void loop() {
  // put your main code here, to run repeatedly:
  valorSensor1 = analogRead(pinSen1);
   valorSensor2 = analogRead(pinSen2);
    valorSensor3 = analogRead(pinSen3); 

  Serial.println(valorSensor1);
  Serial.println(valorSensor2);
  Serial.println(valorSensor3);
  delay(800);
  
  /*if(valorSensor1 < brancoInfra){
    Serial.println("BRANCO");
  } else {
    Serial.println("PRETO");
  }
  if(valorSensor2 < brancoInfra){
    Serial.println("BRANCO");
  } else {
    Serial.println("PRETO");
  }
  if(valorSensor3 < brancoInfra){
    Serial.println("BRANCO");
  } else {
    Serial.println("PRETO");
  } 
  Serial.println();
  delay(700);*/
}

void detectarPreto(){
  pretoInfra = analogRead(pinSen2) - 50;
  delay(500);
}

void detectarBranco(){
  brancoInfra = (analogRead(pinSen1) + analogRead(pinSen3))/2 + 50;
  delay(500);
} 
