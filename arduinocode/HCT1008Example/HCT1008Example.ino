#include <Wire.h>
#include "Adafruit_HDC1000.h"
#include <LiquidCrystal.h>

//setup for the LCD keypad shield
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// Connect Vin to 5VDC
// Connect GND to ground
// Connect SCL to A5 on UNO
// Connect SDA to A4 on UNO

Adafruit_HDC1000 hdc = Adafruit_HDC1000();

void setup() 
{
  Serial.begin(9600);
  Serial.println("HDC100x test");
  //lcd setup
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("Temp: ");
  //line 2 - humidity
  lcd.setCursor(0,1);
  lcd.print("Humidity: ");
  if (!hdc.begin()) 
  {
    Serial.println("Couldn't find sensor!");
    while (1);
  }
}


void loop() 
{
  Serial.print("Temp: "); Serial.print(hdc.readTemperature());
  Serial.print("\t\tHum: "); Serial.println(hdc.readHumidity());
  lcd.setCursor(7,0);
  lcd.print(hdc.readTemperature());
  lcd.setCursor(11,1);
  lcd.print(hdc.readHumidity());
  delay(500);
}
