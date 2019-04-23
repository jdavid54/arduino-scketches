#include <Wire.h>
#include "DS1307RTC.h"
#include <TimeLib.h>

#define DS1307_CTRL_ID 0x68

tmElements_t tm;

// PRIVATE FUNCTIONS

// Convert Decimal to Binary Coded Decimal (BCD)
uint8_t dec2bcd(uint8_t num)
{
  return ((num/10 * 16) + (num % 10));
}

// Convert Binary Coded Decimal (BCD) to Decimal
uint8_t bcd2dec(uint8_t num)
{
  return ((num/16 * 10) + (num % 16));
}

void setup()
{ 
 Wire.begin();
 Serial.begin(9600);
 delay(1000); 

  //READ!!!!*********************************
 uint8_t sec;
  Wire.beginTransmission(DS1307_CTRL_ID);

  Wire.write((uint8_t)0x00); 
 
  if (Wire.endTransmission() != 0) {
    Serial.println("Erreur écriture!");
    
  }
  //exists = true;

  // request the 7 data fields   (secs, min, hr, dow, date, mth, yr)
  Wire.requestFrom(DS1307_CTRL_ID, tmNbrFields);
  if (Wire.available() < tmNbrFields) Serial.println("Erreur quantité!");

  sec = Wire.read();
  tm.Second = bcd2dec(sec & 0x7f);   
  tm.Minute = bcd2dec(Wire.read() );
  tm.Hour =   bcd2dec(Wire.read() & 0x3f);  // mask assumes 24hr clock
  tm.Wday = bcd2dec(Wire.read() );
  
  tm.Day = bcd2dec(Wire.read() );
  tm.Month = bcd2dec(Wire.read() );
  tm.Year = y2kYearToTm((bcd2dec(Wire.read())));
  if (sec & 0x80) Serial.println("Erreur lecture!"); // clock is halted
  Serial.print(tm.Hour);
  Serial.print(":");
  Serial.print(tm.Minute);
  Serial.print(":");
  Serial.print(tm.Second);
  Serial.print("-");
  Serial.print(tm.Wday);Serial.print("-");
  Serial.print(tm.Day);Serial.print("/");
  Serial.print(tm.Month);Serial.print("/");
  Serial.println(tm.Year+1970);
}

void loop()
{
}
