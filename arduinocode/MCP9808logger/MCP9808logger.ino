#include <Wire.h>
#include "Adafruit_MCP9808.h"
#include <SPI.h>
#include <SD.h>
#include "RTClib.h"

RTC_DS1307 RTC;
Adafruit_MCP9808 tempsensor = Adafruit_MCP9808();
File myFile;
const int chipSelect = 10;

void setup()
{
  Wire.begin();
  Serial.begin(9600);
  RTC.begin();
  //sd setup
  if (!SD.begin(chipSelect)) 
  {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization complete.");
  //temp sensor setup
  if (!tempsensor.begin()) 
  {
    Serial.println("Couldn't find MCP9808!");
    while (1);
  }
  //RTC setup
  if (! RTC.isrunning()) 
  {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }
}

void loop()
{
  float c = tempsensor.readTempC();
  float f = c * 9.0 / 5.0 + 32;
  DateTime now = RTC.now();
  //create a file
  File myFile = SD.open("mcp9808.txt", FILE_WRITE);
  //write to file
  if (myFile) 
  {
    Serial.print("Writing to mcp9808.txt...");
    //date and time section
    if(now.hour() <10)
    {
      myFile.print("0");
    }
    myFile.print(now.hour());
    myFile.print(":");
    
    if(now.minute() < 10)
    {
      myFile.print("0");
    }
    myFile.print(now.minute());
    myFile.print(":");
    
    if(now.second() < 10)
    {
       myFile.print("0");
    }
    myFile.print(now.second());
    myFile.print(",");
    //sensor section
    myFile.print(c);
    myFile.print(",");
    myFile.print(f);
    myFile.println();
    //close the file
    myFile.close();
    Serial.println("done.");
    tempsensor.shutdown_wake(1);
    delay(2000);
    tempsensor.shutdown_wake(0);
  } 
  else 
  {
    Serial.println("error opening mcp9808.txt file");
  }
  delay(1000);
}
