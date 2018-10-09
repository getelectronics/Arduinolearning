#include <SPI.h>
#include <SD.h>

 
File myFile;
 
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
 
  //open the file.
  myFile = SD.open("test.txt", FILE_WRITE);
 
  //write to file
  if (myFile) 
  {
    Serial.print("Writing to test.txt...");
    myFile.println("1,2,3,4,5");
    //close the file
    myFile.close();
    Serial.println("done.");
  } 
  else 
  {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt file");
  }
}
 
void loop()
{

}
