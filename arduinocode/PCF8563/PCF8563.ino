#include <Wire.h>
#include <Rtc_Pcf8563.h>

//init the real time clock
Rtc_Pcf8563 rtc;

void setup()
{
  //clear out the registers
  rtc.initClock();
  //set a time to start with.
  //day, weekday, month, century(1=1900, 0=2000), year(0-99)
  rtc.setDate(23, 1, 11, 0, 15);
  //hr, min, sec
  rtc.setTime(14, 04, 01);
  Serial.begin(9600);
}

void loop()
{
  //both format functions call the internal getTime() so that the 
  //formatted strings are at the current time/date.
  Serial.print(rtc.formatTime());
  Serial.print(" : ");
  Serial.print(rtc.formatDate());
  Serial.println();
  delay(1000);
}




