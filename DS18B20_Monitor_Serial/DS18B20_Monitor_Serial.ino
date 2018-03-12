/*
 * Pinagem   
 * -> Sensor DS18B20
 *      pino central (dados) - Pin 7
 */

//*****************************
// bibliotecas do DS18B20
#include <OneWire.h>
#include <DallasTemperature.h>
//*****************************


//***********************************************************************************
// porta digital do arduino em que o pino de dados do sensor DS18B20 está ligado
#define ONE_WIRE_BUS 7
//***********************************************************************************

// Prepara uma instancia de oneWire para se comunicar com um dispositivo OneWire
OneWire oneWire(ONE_WIRE_BUS);
// Passa nossa referencia oneWire para Dallas Temperature. 
DallasTemperature sensors(&oneWire);
//************************************************************************************


// pra calcular a temp.
float tempC = 0.0;


void setup() {
    sensors.begin();
    Serial.begin(9600);
}


void loop() {

    // envia um comando para obter a temperatura
    sensors.requestTemperatures();
    tempC = sensors.getTempCByIndex(0);

    Serial.print(tempC);
    Serial.write(176); // simbolo de grau º
    Serial.println("C");

    delay(1000);
}
