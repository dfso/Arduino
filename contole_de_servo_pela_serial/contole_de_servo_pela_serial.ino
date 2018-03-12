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
    pos = Serial.parseInt();

    if(pos >= 0 && pos <= 180) {
      posiciona(eixoZ, servoPin, pos);
      Serial.println(msg + eixoZ.read() + "°");
      //Serial.println(msg + (pos) + "°");
    }
    else
      Serial.println("Valor invalido!");
 
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


