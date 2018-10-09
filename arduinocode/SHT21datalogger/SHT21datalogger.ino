#include <Wire.h>
#include <Sodaq_SHT2x.h>
#include <SPI.h>
#include <SD.h>
#include "RTClib.h"

RTC_DS1307 RTC;
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
  Serial.print("Humidity(%RH): ");
  Serial.print(SHT2x.GetHumidity());
  Serial.print("     Temperature(C): ");
  Serial.println(SHT2x.GetTemperature());
  DateTime now = RTC.now();
  //create a file
  File myFile = SD.open("sht21.txt", FILE_WRITE);
  //write to file
  if (myFile) 
  {
    Serial.print("Writing to sht21.txt...");
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
    myFile.print(SHT2x.GetHumidity());
    myFile.print(",");
    myFile.print(SHT2x.GetTemperature());
    myFile.println();
    //close the file
    myFile.close();
    Serial.println("done.");
  } 
  else 
  {
    Serial.println("error opening sht21.txt file");
  }
  delay(1000);
}

