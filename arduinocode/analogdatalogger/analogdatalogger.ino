#include <SPI.h>
#include <SD.h>

const int chipSelect = 10;

void setup() 
{
  Serial.begin(9600);
  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) 
  {
    Serial.println("Card failed, or not present");
    return;
  }
  Serial.println("card initialized.");
}

void loop() {
  // make a string for assembling the data to log:
  String dataString = "";

  // read three sensors and append to the string:
  for (int analogPin = 0; analogPin <= 5; analogPin++) 
  {
    int sensor = analogRead(analogPin);
    dataString += String(sensor);
    if (analogPin < 5) 
    {
      dataString += ",";
    }
  }
  delay(1000);
  // open the file.
  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) 
  {
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
    Serial.println(dataString);
  }
  // if the file isn't open, pop up an error:
  else 
  {
    Serial.println("error opening datalog.txt");
  }
}
