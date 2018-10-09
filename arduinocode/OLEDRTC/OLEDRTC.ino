#include <Wire.h>
#include "RTClib.h"
#include <MicroLCD.h>

LCD_SSD1306 lcd; /* for SSD1306 OLED module */
 
RTC_DS1307 RTC;
 
void setup () 
{
    Serial.begin(57600);
    Wire.begin();
    RTC.begin();
    lcd.begin();
    lcd.clear();
  if (! RTC.isrunning()) 
  {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }
 
}
 
void loop () 
{
    DateTime now = RTC.now();
    lcd.setCursor(0, 0);
    lcd.setFontSize(FONT_SIZE_LARGE);
    //serial port debugging
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(' ');
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
    //oled display
    if(now.hour() <10)
    {
      lcd.print("0");
    }
    lcd.print(now.hour());
    lcd.print(":");
    
    if(now.minute() < 10)
    {
      lcd.print("0");
    }
    lcd.print(now.minute());
    lcd.print(":");
    
    if(now.second() < 10)
    {
       lcd.print("0");
    }
    lcd.print(now.second());
    delay(1000);
}
