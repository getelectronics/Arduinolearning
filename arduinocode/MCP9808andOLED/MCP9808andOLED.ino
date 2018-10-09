#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <stdint.h>
#include "Adafruit_MCP9808.h"


#define OLED_RESET 4

Adafruit_SSD1306 display(OLED_RESET);
Adafruit_MCP9808 tempsensor = Adafruit_MCP9808();

#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

void setup()   
{                
  Serial.begin(57600);
  if (!tempsensor.begin()) 
  {
    Serial.println("Couldn't find MCP9808!");
    while (1);
  }
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
}


void loop() 
{
  tempsensor.shutdown_wake(0); 
  float c = tempsensor.readTempC();
  float f = c * 9.0 / 5.0 + 32;
  // Clear the buffer.
  display.clearDisplay();

  // text display tests
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("Temp(c): ");
  display.print(c);
  display.print(" c");
  display.setCursor(0,10);
  display.print("Temp(f): ");
  display.print(f); 
  display.print(" f");
  delay(250);
  display.display();
  tempsensor.shutdown_wake(1);
  delay(2000);

}

