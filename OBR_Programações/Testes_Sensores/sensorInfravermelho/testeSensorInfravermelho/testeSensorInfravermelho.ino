#define pinSen1 A1
#define pinSen2 A2
#define pinSen3 A3

int valorSensor1;
int valorSensor2;
int valorSensor3;

int pretoInfra = 0;
int brancoInfra = 0;

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
  if((valorSensor1 <= brancoInfra)){
    Serial.print("1-Branco");
  } else if(valorSensor1 >= pretoInfra){
    Serial.print("1-Preto");
  } else {
    Serial.print("1-Nada");
  }
  Serial.println();
  if((valorSensor2 <= brancoInfra)){
    Serial.print("2-Branco");
  } else if(valorSensor2 >= pretoInfra){
    Serial.print("2-Preto");
  } else {
    Serial.print("2-Nada");
  }
  Serial.println();
  if((valorSensor3 <= brancoInfra)){
    Serial.print("3-Branco");
  } else if(valorSensor3 >= pretoInfra){
    Serial.print("3-Preto");
  } else {
    Serial.print("3-Nada");
  }
  Serial.println();
  delay(1200); 
  /*Serial.println("valorSensor1:");
  Serial.println(valorSensor1);
  Serial.println("valorSensor2:");
  Serial.println(valorSensor2);
  Serial.println("valorSensor3:");
  Serial.println(valorSensor3);
  Serial.println();*/
}

void detectarPreto(){
  pretoInfra = analogRead(pinSen2) - 150;
}

void detectarBranco(){
  brancoInfra = (analogRead(pinSen1) + analogRead(pinSen3))/2 + 50;
}
