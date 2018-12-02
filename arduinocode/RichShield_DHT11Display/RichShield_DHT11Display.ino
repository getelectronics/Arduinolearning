#include <TM1637Display.h>
#include "DHT.h"

//this is the pin on the Rich shield
#define DHTPIN 12 
#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE); 
 
// Module connection pins (Digital Pins)
#define CLK 10
#define DIO 11
 
TM1637Display tm1637(CLK,DIO);

uint8_t data[] = {0, 0, 0, 0};
 
void setup()
{
  Serial.begin(9600);
  dht.begin(); 
}
 
void loop()
{
  // Check if any reads failed and exit early (to try again).
  int humidity = dht.readHumidity();
  int temp = dht.readTemperature();  
  if (isnan(humidity) || isnan(temp))
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  
  displayTemp(temp);
  debugDHT11(temp, humidity);
  delay(3000);
  displayHum(humidity);
  delay(3000);
}

void displayTemp(int tempValue)
{
  tm1637.setBrightness(0x0f);
  data[3] = tm1637.encodeDigit(tempValue/1 % 10);
  data[2] = tm1637.encodeDigit(tempValue/10 % 10);
  data[1] = tm1637.encodeDigit(tempValue/100 % 10);
  data[0] = tm1637.encodeDigit(tempValue/1000 % 10);
  tm1637.setSegments(data);
}

void displayHum(int humValue)
{
  tm1637.setBrightness(0x0f);
  data[3] = tm1637.encodeDigit(humValue/1 % 10);
  data[2] = tm1637.encodeDigit(humValue/10 % 10);
  data[1] = tm1637.encodeDigit(humValue/100 % 10);
  data[0] = tm1637.encodeDigit(humValue/1000 % 10);
  tm1637.setSegments(data);
}

void debugDHT11(int temp, int humidity)
{
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.println(" *C ");
}



