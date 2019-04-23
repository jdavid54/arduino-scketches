/*
 * TimeRTCSet.pde
 * example code illustrating Time library with Real Time Clock.
 *
 * RTC clock is set in response to serial port time message 
 * A Processing example sketch to set the time is included in the download
 * On Linux, you can use "date +T%s > /dev/ttyACM0" (UTC time zone)
 */

#include <TimeLib.h>
#include <Wire.h>
#include <DS1307RTC.h>  // a basic DS1307 library that returns time as a time_t

// Include NewLiquidCrystal Library for I2C
#include <LiquidCrystal_I2C.h>
// LCD variables
const int  en = 2, rw = 1, rs = 0, d4 = 4, d5 = 5, d6 = 6, d7 = 7, bl = 3;
const int i2c_addr = 0x27;  //LCD address 16x02 : 0x27; LCD 20x4 Blue : 0x3F  Green : 0x27
LiquidCrystal_I2C lcd(i2c_addr, en, rw, rs, d4, d5, d6, d7, bl, POSITIVE);

void setup()  {
  Serial.begin(9600);
  lcd.begin(20,4);
  //lcd.begin(16,2);
  while (!Serial) ; // Needed for Leonardo only
  setSyncProvider(RTC.get);   // the function to get the time from the RTC
  if (timeStatus() != timeSet) {
     Serial.println("Unable to sync with the RTC");
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("Please set time");
     lcd.setCursor(0,1);
     lcd.print("in serial monitor"); 
     }
  else {
     Serial.println("RTC has set the system time");
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("RTC -> system time");     
     } 
}

void loop()
{
  if (Serial.available()) {
    time_t t = processSyncMessage();
    if (t != 0) {
      RTC.set(t);   // set the RTC and the system time to the received value
      setTime(t);          
    }
  }
  digitalClockDisplay();  
  delay(1000);
}

void digitalClockDisplay(){
  // digital clock display of the time
  Serial.print(hour());
  Serial.print(":");
  printDigits(minute());
  Serial.print(":");
  printDigits(second());
  Serial.print(" ");
  printDigits(day());
  Serial.print("/");
  printDigits(month());
  Serial.print("/");
  Serial.print(year()); 
  Serial.println(); 
  lcd.setCursor(0,1);
  lcd.print(hour());
  lcd.print(":");
  LCDprintDigits(minute());
  lcd.print(":");
  LCDprintDigits(second());
  lcd.setCursor(0,2);
  LCDprintDigits(day());
  lcd.print("/");
  LCDprintDigits(month());
  lcd.print("/");
  lcd.print(year());
}

void printDigits(int digits){
  // utility function for digital clock display: prints preceding colon and leading 0
  
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}

void LCDprintDigits(int digits){
  // utility function for digital clock display: prints preceding colon and leading 0
  
  if(digits < 10)
    lcd.print('0');
  lcd.print(digits);
}
/*  code to process time sync messages from the serial port   */
#define TIME_HEADER  "T"   // Header tag for serial time sync message

unsigned long processSyncMessage() {
  unsigned long pctime = 0L;
  const unsigned long DEFAULT_TIME = 1357041600; // Jan 1 2013 

  if(Serial.find(TIME_HEADER)) {
     pctime = Serial.parseInt();
     return pctime;
     if( pctime < DEFAULT_TIME) { // check the value is a valid time (greater than Jan 1 2013)
       pctime = 0L; // return 0 to indicate that the time is not valid
     }
  }
  return pctime;
}





