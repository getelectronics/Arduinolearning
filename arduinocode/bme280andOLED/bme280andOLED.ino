#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <stdint.h>
#include "SparkFunBME280.h"

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

//Global sensor object
BME280 mySensor;

#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

void setup()   
{                
  Serial.begin(57600);
  //BME280 sensor setup
  mySensor.settings.commInterface = SPI_MODE;
  mySensor.settings.chipSelectPin = 10;

  //Operation settings
  mySensor.settings.runMode = 3; //Normal mode
  mySensor.settings.tStandby = 0;
  mySensor.settings.filter = 0;
  mySensor.settings.tempOverSample = 1;
  mySensor.settings.pressOverSample = 1;
  mySensor.settings.humidOverSample = 1;
  
  Serial.print("Starting BME280... result of .begin(): 0x");
  delay(10);  //BME280 requires 2ms to start up.
  Serial.println(mySensor.begin(), HEX);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)

}


void loop() 
{
    // Clear the buffer.
  display.clearDisplay();

  // text display tests
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("Temperature: ");
  display.print(mySensor.readTempC(), 2);
  display.print(" c");
  display.setCursor(0,10);
  display.print("Pressure: ");
  display.print(mySensor.readFloatPressure(), 2);
  display.setCursor(0,20);
  display.print("Altitude: ");
  display.print(mySensor.readFloatAltitudeMeters(), 2);
  display.print(" m");
  display.display();
  delay(2000);
}




