// Date and time functions using a DS1307 RTC connected via I2C and Wire lib

#include <Wire.h>
#include "RTClib.h"

DS1307 rtc;

void setup () {
  Serial.begin(57600);
#ifdef AVR
  Wire.begin();
#else
  Wire1.begin(); // Shield I2C pins connect to alt I2C bus on Arduino Due
#endif
  rtc.begin();

  if (! rtc.isrunning()) {           // bit 7 (CH) registre des secondes : RTC 1=stop, 0=running !
                                     // Attention : isrunning() renvoie !CH donc 0=running 1=stop
    Serial.println("RTC is NOT running!");       // quand le DS1307 vient d'être alimenté, CH = 1 (registres=0)
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(__DATE__, __TIME__));
  }
  Serial.println("Check the DS1307 time with the PC time and adjust"); 
  // Uncomment to adjust. Change value to add or substract from the RTC time. Then comment out.
   
  DateTime now = rtc.now();
  rtc.adjust(DateTime(now.unixtime()+1)); 
  
}

void loop () {
    DateTime now = rtc.now();
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
    delay(1000);
}
