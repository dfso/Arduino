/*######################################
   Pinagem
   -> Sensor DS18B20
        pino central (dados) - gpio D3
        pino vcc (direita)   - 3v3
        pino gng (esquerda)  - GND
#######################################*/

//*****************************
// bibliotecas do DS18B20
#include <OneWire.h>
#include <DallasTemperature.h>
//*****************************

// biblioteca para nodeMcu esp8266
#include <ESP8266WiFi.h>

// configuracoes da rede
const char* ssid = "dfso.network";
const char* password = "israel.1948";

// gpio D3 usado para ler os dados do ds18b20
#define ONE_WIRE_BUS D3

// Prepara uma instancia de oneWire para se comunicar com um dispositivo OneWire
OneWire oneWire(ONE_WIRE_BUS);

// Passa nossa referencia oneWire para Dallas Temperature.
DallasTemperature DS18B20(&oneWire);

// variaveis usadas para converter os valoes de temperatura float para String
char tempCString[6];
char tempFString[6];

// Servidor Web na porta 80
WiFiServer server(80);



void setup() {
  // Serial usado para propositos de debug
  Serial.begin(9600);
  delay(10);

  DS18B20.begin(); // IC Default 9 bit. If you have troubles consider upping it 12. Ups the delay giving the IC more time to process the temperature measurement

  // Conecta a rede  WiFi
  Serial.println();
  Serial.print("Conectando a ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi Conectado");

  // Inicia o Servidor Web
  server.begin();
  Serial.println("Web server running. Waiting for the ESP IP...");
  delay(10000);

  // Imprime o endereco IP para o nodeMcu
  Serial.println(WiFi.localIP());
}

void getTemperature() {
  float tempC;
  float tempF;
  do {
    DS18B20.requestTemperatures();
    tempC = DS18B20.getTempCByIndex(0);
    dtostrf(tempC, 2, 2, tempCString);
    tempF = DS18B20.getTempFByIndex(0);
    dtostrf(tempF, 3, 2, tempFString);
    delay(100);
  } while (tempC == 85.0 || tempC == (-127.0));
}


void loop() {
  // Listenning for new clients
  WiFiClient client = server.available();

  if (client) {
    Serial.println("New client");
    // bolean to locate when the http request ends
    boolean blank_line = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();

        if (c == '\n' && blank_line) {
          getTemperature();
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");
          client.println();

          // cria a pagina web
          String webpage = "";
          webpage += "<html><head><title>ds18b20 em nodeMcu</title><meta http-equiv='refresh' content='5'></head>";
          webpage += "<body><h3 style='text-align: center;'>Temperatura com nodeMcu e ds18b20</h3>";
          webpage += "<table align='center' border='1' cellpadding='1' cellspacing='1' style='width: 500px'>";
          webpage += "<tbody><tr><td>Temperatura em Celcius</td>";
          webpage += "<td>";
          webpage += tempCString;
          webpage += "&deg;C</td></tr>";

          webpage += "<tr><td>Temperatura em Farenheit</td>";
          webpage += "<td>";
          webpage += tempFString;
          webpage += "&deg;F</td></tr></tbody></table>";

          webpage += "<p>&nbsp;</p></body></html>";

          client.println(webpage);
          break;
        }
        if (c == '\n') {
          // when starts reading a new line
          blank_line = true;
        }
        else if (c != '\r') {
          // when finds a character on the current line
          blank_line = false;
        }
      }
    }
    // closing the client connection
    delay(1);
    client.stop();
    Serial.println("Client disconnected.");
  }
}
