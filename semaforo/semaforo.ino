#define VD1 8
#define AM1 9
#define VM1 10

#define VD2 5
#define AM2 6
#define VM2 7

void setup() {

    pinMode(VD1, OUTPUT);
    pinMode(AM1, OUTPUT);
    pinMode(VM1, OUTPUT);

    pinMode(VD2, OUTPUT);
    pinMode(AM2, OUTPUT);
    pinMode(VM2, OUTPUT);
}

void loop() {

    digitalWrite(VD1, HIGH);
    digitalWrite(VM2, HIGH);
    delay(7000);
    digitalWrite(VD1, LOW);
    piscarVerde(VD1, 3);
    
    digitalWrite(AM1, HIGH);
    delay(5000);
    digitalWrite(AM1, LOW);
    
    digitalWrite(VM1, HIGH);
    digitalWrite(VM2, LOW);
    
    digitalWrite(VD2, HIGH);
    delay(7000);
    digitalWrite(VD2, LOW);
    piscarVerde(VD2, 3);
    
    digitalWrite(AM2, HIGH);
    delay(5000);
    digitalWrite(AM2, LOW);
    digitalWrite(VM1, LOW);
}

// faz o led piscar durante o intervalo passado como parâmetro
void piscarVerde(int pin, int seconds) {

    for(int i=0; i<seconds; i++) {
        digitalWrite(pin, HIGH);
        delay(500);
        digitalWrite(pin, LOW);
        delay(500);
    }
        
}

