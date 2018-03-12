/*
 * It is assumed that the LCD module is connected to
 * the following pins using a levelshifter to get the
 * correct voltage to the module.
 *   SCLK - Pin 8
 *   MOSI - Pin 9
 *   DC   - Pin 10
 *   RST  - Pin 11
 *   SCE  - Pin 12
 */

//********************************************
// bibliotecas do DS18B20
#include <OneWire.h>
#include <DallasTemperature.h>
// biblioteca do LCD Nokia 5110
#include <LCD5110_Graph.h>
//********************************************


//***********************************************************************************
// porta digital do arduino em que o pino de dados do sensor DS18B20 está ligado
#define ONE_WIRE_BUS 7
//***********************************************************************************


//***********************************************************************************
// cria o LCD
LCD5110 my_lcd(8, 9, 10, 11, 12);

// Prepara uma instancia de oneWire para se comunicar com um dispositivo OneWire
OneWire oneWire(ONE_WIRE_BUS);

// Passa nossa referencia oneWire para Dallas Temperature. 
DallasTemperature sensors(&oneWire);
//************************************************************************************


extern unsigned char SmallFont[];
extern unsigned char MediumNumbers[];
extern uint8_t temperatureIcon[];
extern uint8_t degree_celsius_u2103_icon_10x10[];

float tempC = 0.0;


// configurações
void setup()
{   
    my_lcd.InitLCD();
    my_lcd.setFont(MediumNumbers);
    sensors.begin();
    Serial.begin(9600);
}


void loop()
{
    // envia um comando para obter a temperatura
    sensors.requestTemperatures();
    tempC = sensors.getTempCByIndex(0);
    my_lcd.clrScr();
    my_lcd.drawBitmap(-6, 0, temperatureIcon, 84, 48);
    my_lcd.printNumF(tempC, 1, 15, 20);
    my_lcd.drawBitmap(70, 15, degree_celsius_u2103_icon_10x10, 10, 10);
    
    Serial.print("Temp: ");
    Serial.print(tempC);
    Serial.println("°C");
       
    my_lcd.update();
    delay(1000);
    my_lcd.clrScr();
}

