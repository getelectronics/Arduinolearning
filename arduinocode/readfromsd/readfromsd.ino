#include <SD.h>
#include <SPI.h>

File testFile;
 
void setup()
{
  Serial.begin(9600);
  Serial.print("Initializing SD card...");
   pinMode(10, OUTPUT);
 
  if (!SD.begin(10)) 
  {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization complete.");
 
  // open the file
  testFile = SD.open("newtest.txt");
  if (testFile) 
  {
    Serial.println("newtest.txt:");
 
    //read from the file
    while (testFile.available()) 
    {
      Serial.write(testFile.read());
    }
    // close the file:
    testFile.close();
  } 
  else 
  {
    Serial.println("error opening newtest.txt");
  }
}
 
void loop()
{

}
