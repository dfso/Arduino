// bibliotecas necessárias
#include <OneWire.h>
#include <DallasTemperature.h>


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
  Serial.println("Temperatura com DS18B20");

  // inicia a biblioteca
  sensors.begin();
}


void loop(void)
{
  // call sensors.requestTemperatures() to issue a global temperature
  // request to all devices on the bus
  Serial.print("Obtendo temperaturas...");
  sensors.requestTemperatures(); // Send the command to get temperatures
  Serial.println("PRONTO");
  // After we got the temperatures, we can print them here.
  // We use the function ByIndex, and as an example get the temperature from the first sensor only.
  Serial.print("Temperatura no dispositivo 1 (index 0) e': ");
  Serial.println(sensors.getTempCByIndex(0));
}
