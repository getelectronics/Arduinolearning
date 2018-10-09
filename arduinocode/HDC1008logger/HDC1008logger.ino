#include <Wire.h>
#include "Adafruit_HDC1000.h"
#include <SPI.h>
#include <SD.h>
#include "RTClib.h"

RTC_DS1307 RTC;
Adafruit_HDC1000 hdc = Adafruit_HDC1000();
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
  if (!hdc.begin()) 
  {
    Serial.println("Couldn't find sensor!");
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

  DateTime now = RTC.now();
  //create a file
  File myFile = SD.open("HDC1000.csv", FILE_WRITE);
  //write to file
  if (myFile) 
  {
    Serial.print("Writing to HDC1000.csv...");
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
    myFile.print(hdc.readTemperature());
    myFile.print(",");
    myFile.print(hdc.readHumidity());
    myFile.println();
    //close the file
    myFile.close();
    Serial.println("done.");
  } 
  else 
  {
    Serial.println("error opening HDC1000.csv file");
  }
  delay(1000);
}
