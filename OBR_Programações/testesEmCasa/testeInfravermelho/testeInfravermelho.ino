//definição sensores infravermelhos
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
}

void loop() {
  valorSensor3 = analogRead(pinSen3);
  // put your main code here, to run repeatedly:
  Serial.println(valorSensor3);
  delay(500);
}
