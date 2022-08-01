void setup() {
  // put your setup code here, to run once:

}

void loop() {
  //Se os sensores do lado identificarem branco e o central preto, seguirá em frente
  if((sensor1 == *branco*) && (sensor3 == *branco*) && (sensor2 == *preto*)){
    analogWrite(R1, velocidade);
    analogWrite(R2, velociade);
  }

  //programação gap
  if((sensor1 == *branco*) && (sensor3 == *branco*) && (sensor2 == *branco*)){
    while(sensor2 != *preto*){
      analogWrite(R1, velocidade);
      analogWrite(R2, velociade);
    }
  }
  
  //Analisa se algum dos sensores laterais idenficam algo além do branco enquanto o central preto
  if((sensor1 != *branco*) || (sensor3 != *branco*) && (sensor2 == *preto*)){   
    //Verifica se ambos sensores laterais identificaram diferente de branco
    if((sensor1 != *branco*) && (sensor3 != *branco*)){
      //verifica se ambos são verdes
      if((sensor1 == *verde*) && (sensor3 == *verde*)){
        //Vai em frente e dá meia volta
      } else {
        //A outra possibilidade é serem pretos, logo ele segue em frente
        analogWrite(R1, velocidade);
        analogWrite(R2, velociade);
      }

     //Verifica se o da esquerda ou direita identificam diferente de branco
     //Esquerda:
     if(sensor1 != *branco*) {
      //Verifica se identifica verde
      if(sensor1 == *verde*){
        //robo vira para o lado esquerdo
      } else {
        //Robo vai um pouco pra frente antes do código abaixo :)
        while(sensor3 != *preto*){
          analogWrite(R1, 0);
          analogWrite(R2, velociade);
        }
        while(sensor2 != *preto*){
            analogWrite(R1, velocidade);
            analogWrite(R2, 0);
        }
      }
     //Direita:
     } else {
      //Verifica se identifica verde
      if(sensor3 == *verde*){
        //robo vira para o lado direito
      } else {
        /* //Robo vai um pouco pra frente antes do código abaixo :)
         while(sensor1 != *preto*){
          analogWrite(R1, velocidade);
          analogWrite(R2, 0);
        }
        while(sensor2 != *preto*){
            analogWrite(R1, 0);
            analogWrite(R2, velocidade);
        } */
        //robo vai um pouco pra frente 
        if((sensor1 == *branco*) && (sensor3 == *branco*) && (sensor2 == *branco*)){
          //vai pra tras até o sensor do lado e central verem preto 
          //vai seguir linha somente com os sensores do lado
          while((sensor1 != *branco) && (sensor2 != *branco*)){
            analogWrite(R1, velocidade);
            analogWrite(R2, 0);
          }
        }
      }
     }
    }
  }
}
