// bibliotecas necessárias
#include <OneWire.h>
#include <DallasTemperature.h>

#include <Javino.h>

Javino j;

// pino de dados ligado ao arduino
#define ONE_WIRE_BUS A1

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);


void setup(void)
{
  // inicia a comunicação serial
  Serial.begin(9600);
  //Serial.println("Temperatura com DS18B20");

  // inicia a biblioteca
  sensors.begin();
}


void loop(void)
{
  sensors.requestTemperatures(); // Send the command to get temperatures

  // envia a temperatura para o Java
  j.sendmsg(String(sensors.getTempCByIndex(0)));
           
  delay(100);
}
