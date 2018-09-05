#include <OneWire.h>
#include <DallasTemperature.h>

#include <OLED_I2C.h>



// Data wire no pino A1 no Arduino
#define ONE_WIRE_BUS A1

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature ds18b20(&oneWire);

// Arduino Uno/2009:
// ----------------------
// Display:  SDA pin   -> Arduino Analog 4 or the dedicated SDA pin
//           SCL pin   -> Arduino Analog 5 or the dedicated SCL pin
OLED  myOLED(SDA, SCL);

// fontes
extern uint8_t SmallFont[];
extern uint8_t MediumNumbers[];


// variaveis usadas para converter os valoes de temperatura float para String
float temp_c;

void setup(void)
{
  // start serial port
  Serial.begin(9600);
  Serial.println("Monitorando temperatura com sensor ds18b20");

  // Start up the library
  ds18b20.begin();

  // start oled display
  myOLED.begin();
  //myOLED.setFont(SmallFont);
}

void get_temp_c() {
  ds18b20.requestTemperatures();
  temp_c = ds18b20.getTempCByIndex(0);
  //dtostrf(temp_c, 2, 2, tempCString);
}

void loop(void)
{
  get_temp_c();
  Serial.print("Temperature for the device 1 (index 0) is: ");
  Serial.println(temp_c);

  int y = random(0, 56);
  int x = random(0, 16);
  myOLED.setFont(SmallFont);
  myOLED.print("Temperatura", x, y - 10);
  myOLED.setFont(MediumNumbers);
  myOLED.printNumF(temp_c, 2, x, y);
  myOLED.setFont(SmallFont);
  myOLED.drawCircle(x+64, y+5, 2);
  myOLED.print("C", x+66, y+8);
  myOLED.update();
  delay(1000);
  myOLED.clrScr();
}

