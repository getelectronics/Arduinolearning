// Example testing sketch for various DHT humidity/temperature sensors

#include "DHT.h"

#define DHTPIN 12    // what digital pin we're connected to
#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);
int redPin = 4;
int greenPin = 5;

void setup() 
{
  Serial.begin(9600);
  Serial.println("DHTxx test!");
  dht.begin();
  pinMode(greenPin, OUTPUT);     
  pinMode(redPin, OUTPUT);
}

void loop() 
{
  // Wait a few seconds between measurements.
  delay(2000);
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(t))
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  //if temperature is greater or equal to 27 celsius
  //switch on red led and green led off
  if(t >= 27)
  {
    digitalWrite(greenPin, LOW);
    digitalWrite(redPin, HIGH);
  }
  else
  {
    digitalWrite(greenPin, HIGH);
    digitalWrite(redPin, LOW);
  }

  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" *C ");


}
