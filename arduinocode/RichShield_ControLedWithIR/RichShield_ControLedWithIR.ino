/*
My remote values
FF30CF - 1
FF18E7 - 2
FF7A85 - 3
FF10EF - 4
FF38C7 - 5
FF5AA5 - 6
FF42BD - 7
FF4AB5 - 8
FF52AD - 9
FF6897 - 0
I convert these to decimal
*/
#include <IRremote.h>
 
int IR_Recv = 2;   //IR Receiver Pin 2
int redPin = 4;
int greenPin = 5;
int bluePin = 6;
int yellowPin = 7;
 
IRrecv irrecv(IR_Recv);
decode_results results;
 
void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Starts the receiver
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);    
  pinMode(yellowPin, OUTPUT);   
  pinMode(redPin, OUTPUT);      
}
 
void loop()
{
  //decodes the infrared input
  if (irrecv.decode(&results))
  {
    long int decCode = results.value;
    Serial.println(results.value);
    //switch case to use the selected button
    switch (results.value)
    {
      case 16724175: //when you press 1
        digitalWrite(yellowPin, HIGH);
        break;   
      case 16726215: //when you press 5
        digitalWrite(yellowPin, LOW);   
        break;
       case 16718055: //when you press 2
        digitalWrite(bluePin, HIGH);
        break;           
       case 16734885: //when you press 6
        digitalWrite(bluePin, LOW);
        break;       
       case 16743045: //when you press 3
        digitalWrite(greenPin, HIGH);
        break;       
       case 16728765: //when you press 7
        digitalWrite(greenPin, LOW);
        break;
     case 16716015: //when you press 4
        digitalWrite(redPin, HIGH);
        break;
     case 16730805: //when you press 8
        digitalWrite(redPin, LOW);
        break;
    }
    irrecv.resume();
  }
  delay(10);
}
