/*
   Created by Vasilakis Michalis // 12-12-2014 ver.1
   Project: Control RC Car via Bluetooth with Android Smartphone
   http://www.ardumotive.com/arduino-car
   More information at www.ardumotive.com
*/


//L293D
const int motorA1  = 5;  // Pino  2 do L293D
const int motorA2  = 6;  // Pino  7 do L293D
const int motorB1  = 10; // Pino 15 do L293D
const int motorB2  = 9;  // Pino 10 do L293D


// comando recebido pelo modulo bluetooth
char cmd;

int vSpeed = 255;   // Default speed, from 0 to 255

void setup() {

  // configura os pinos como OUTPUT:
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);

  // inicializa a comunicacao serial a 9600 bits por segundo:
  Serial.begin(9600);
  calibracao(200);
}

void loop() {

  //verifica o comando recebido
  if (Serial.available() > 0) {
    cmd = Serial.read();
  }

  //muda a velocidade de 0 a 4. valores sao de 0 a 255 (PWM)
  if (cmd == '0') {
    vSpeed = 0;
  }
  else if (cmd == '1') {
    vSpeed = 100;
  }
  else if (cmd == '2') {
    vSpeed = 180;
  }
  else if (cmd == '3') {
    vSpeed = 200;
  }
  else if (cmd == '4') {
    vSpeed = 255;
  }

  /***********************Forward****************************/
  //se cmd for igual a letra 'F', carro vai "forward"
  if (cmd == 'F') {
    frente(vSpeed);
  }

  /**********************Forward Left************************/
  //se cmd for igual a letra 'G', carro vai "forward left"
  else if (cmd == 'G') {
    frente_esquerda(vSpeed);
  }

  /**********************Forward Right************************/
  //se cmd for igual a letra 'I', carro vai "forward right"
  else if (cmd == 'I') {
    frente_direita(vSpeed);
  }

  /***********************Backward****************************/
  //se cmd for igual a letra 'B', carro vai "backward"
  else if (cmd == 'B') {
    tras(vSpeed);
  }

  /**********************Backward Left************************/
  //se cmd for igual a letra 'H', carro vai "backward left"
  else if (cmd == 'H') {
    tras_esquerda(vSpeed);
  }

  /**********************Backward Right************************/
  //se cmd for igual a 'J', carro vai "backward right"
  else if (cmd == 'J') {
    tras_direita(vSpeed);
  }

  /***************************Left*****************************/
  //se cmd for igual a letra 'L', carro vai "left"
  else if (cmd == 'L') {
    esquerda(vSpeed);
  }

  /***************************Right*****************************/
  //se cmd for igual a letra 'R', carro vai "right"
  else if (cmd == 'R') {
    direita(vSpeed);
  }

  /************************Stop*****************************/
  //se cmd for igual a letra 'S', carro "stop"
  else if (cmd == 'S') {
    stop_car();
  }
  Serial.println(cmd);
}


void calibracao(int velocidade) {
  direita(velocidade);
  delay(1500);
  esquerda(velocidade);
  delay(1500);
  frente(velocidade);
  delay(1000);
  tras(velocidade);
  delay(1000);
  stop_car();
}


void stop_car() {
  analogWrite(motorA1, 0);    analogWrite(motorA2, 0);
  analogWrite(motorB1, 0);    analogWrite(motorB2, 0);
}

void direita(int velocidade) {
  analogWrite(motorA1, velocidade);   analogWrite(motorA2, 0);
  analogWrite(motorB1, 0);    analogWrite(motorB2, 0);
}

void esquerda(int velocidade) {
  analogWrite(motorA1, 0);    analogWrite(motorA2, 0);
  analogWrite(motorB1, velocidade);   analogWrite(motorB2, 0);
}

void tras_direita(int velocidade) {
  analogWrite(motorA1, 0);    analogWrite(motorA2, velocidade);
  analogWrite(motorB1, 0);    analogWrite(motorB2, velocidade / 2);
}

void tras_esquerda(int velocidade) {
  analogWrite(motorA1, 0);    analogWrite(motorA2, velocidade / 2);
  analogWrite(motorB1, 0);    analogWrite(motorB2, velocidade);
}

void tras(int velocidade) {
  analogWrite(motorA1, 0);    analogWrite(motorA2, velocidade);
  analogWrite(motorB1, 0);    analogWrite(motorB2, velocidade);
}

void frente_direita(int velocidade) {
  analogWrite(motorA1, velocidade);   analogWrite(motorA2, 0);
  analogWrite(motorB1, velocidade / 2); analogWrite(motorB2, 0);
}

void frente_esquerda(int velocidade) {
  analogWrite(motorA1, velocidade / 2); analogWrite(motorA2, 0);
  analogWrite(motorB1, velocidade);   analogWrite(motorB2, 0);
}

void frente(int velocidade) {
  analogWrite(motorA1, velocidade);   analogWrite(motorA2, 0);
  analogWrite(motorB1, velocidade);   analogWrite(motorB2, 0);
}
