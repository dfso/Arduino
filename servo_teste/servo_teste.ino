#include <Servo.h>

#define servoPin 12    //Definindo o hardware (servo conectado ao digital 12 do Arduino

Servo eixoZ;        //Cria um objeto para o servo motor utilizado



void setup()
{
  Serial.begin(9600);
  pinMode(servoPin, OUTPUT);

  eixoZ.attach(servoPin);    //Instancia o servo ao pino digital 12
  eixoZ.write(90);
  delay(500);
  eixoZ.detach();
  
  //teste();
}

void loop()
{
  int pos;
  String msg = ">>>Servo em ";

  if(Serial.available()) {
    pos = Serial.read();
    
    switch(pos) {
    case '0':
      posiciona(eixoZ, servoPin, 0);
      Serial.println(msg + eixoZ.read() + "°");
      break;
    case '1':
      posiciona(eixoZ, servoPin, 90);
      Serial.println(msg + eixoZ.read() + "°");
      break;
    case '2':
      posiciona(eixoZ, servoPin, 180);
      Serial.println(msg + eixoZ.read() + "°");
      break;
    default:
      Serial.println("Posicao invalida! Valores validos [0 , 1 ou 2]");
      break;
  }
  delay(500);
  }
}


void posiciona(Servo s, int pino_do_servo, int pos) {
  s.attach(pino_do_servo);
  s.write(pos);
  delay(500);
  s.detach();
}


void teste() {
  for(int pos=0; pos<=180; pos+=5) {
    posiciona(eixoZ, servoPin, pos);
    delay(100);
  } 
}


