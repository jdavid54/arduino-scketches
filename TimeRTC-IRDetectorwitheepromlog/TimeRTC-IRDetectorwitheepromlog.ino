/*
 * TimeRTC.pde
 * example code illustrating Time library with Real Time Clock.
 * 
 */

#include <TimeLib.h>
#include <Wire.h>
#include <DS1307RTC.h>  // a basic DS1307 library that returns time as a time_t
#define TIME_HEADER  "T"   // Header tag for serial time sync message
#define TIME_REQUEST  7    // ASCII bell character requests a time sync message 
#include <AT24Cxx.h>
#include <EEPROM.h>

#define AT24Cxx_CTRL_ID 0x50   // adresse AT24C32 du module RTC
AT24Cxx eep(AT24Cxx_CTRL_ID,32);

// Include NewLiquidCrystal Library for I2C
#include <LiquidCrystal_I2C.h>
// LCD variables
const int  en = 2, rw = 1, rs = 0, d4 = 4, d5 = 5, d6 = 6, d7 = 7, bl = 3;
const int i2c_addr = 0x27;    // adresse LCD 16x2 : 0x27 LCD 20x4 : 0x3F
LiquidCrystal_I2C lcd(i2c_addr, en, rw, rs, d4, d5, d6, d7, bl, POSITIVE);

int iread;
byte Buffer[11];
char texte[12];
String str;

int buzzpin = 6;
int alarmpin = 11;  // blue
int detectpin = 2;
int memopin = 12;  //red
int reset = 8;    //reset button
byte alrmCount;
tmElements_t tm;
time_t mk, mt=0;
unsigned int writeLocation = 0;
unsigned int locationMem = 3000;

String weekdayname [] = {"Dimanche", "Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi"};

void saveEEPROM() {
  EEPROM.write(0, alrmCount);
  
}

void getEEPROM() {
  alrmCount = EEPROM.read(0);
  writeLocation = 11*alrmCount;
  Serial.println("Nombre alarmes en mémoire : ");
  Serial.println(alrmCount);
}

void saveLocation() {
  if (eep.isPresent()) {
    Buffer[0]=alrmCount;
    eep.WriteMem(locationMem, Buffer, 1);
    //Serial.println(alrmCount);
    //Serial.println("Saved");
  }
}

void getLocation() {
  if (eep.isPresent()) {
    eep.ReadMem(locationMem, Buffer, 1);
    alrmCount =  Buffer[0];
    writeLocation = 11*alrmCount;
    //Serial.println(writeLocation);
    //Serial.println("Get done");
  }
}

void logAlarm(unsigned int addr, unsigned long t){
  if (eep.isPresent()) {
    str=(String(t,DEC));
    str = "A"+str;
    //Serial.println(str);
    str.toCharArray(texte,str.length()+1);
    texte[11]=255;
    eep.WriteMem(addr, texte, 12);
    delay(100);
  }
}  

void logRead() {
 if (eep.isPresent()) {   
    Serial.println("Reading memory");
    for (int c=0; c<alrmCount ; c++) 
    {
      iread=eep.ReadMem(c*11, Buffer, 11);
      delay(100);
      for (int c=0; c<iread; c++) 
      {
        Serial.write(Buffer[c]);
      }
    }
  }
  Serial.println();
}

void LCDlastAlarm() {
if (alrmCount != 0){
 if (eep.isPresent()) {   
    Serial.println("Last alarm reading");
    iread=eep.ReadMem((alrmCount-1)*11, Buffer, 11);
      delay(100);
      for (int c=0; c<iread; c++) 
      {
        Serial.write(Buffer[c]);
      }
      Serial.println();
    
      for (int d=1; d<11 ; d++) 
      {
        mt = (Buffer[d]-48) + mt*10;     
      }
      lcd.setCursor(0,0);
      lcd.print("Last alarm : ");
      lcd.print(alrmCount);
      lcd.setCursor(0,1);
      lcd.print(hour(mt));
      lcd.print(":");
      lcd.print(minute(mt));
      lcd.print(":");
      lcd.print(second(mt));
      lcd.print(" ");
      //Serial.print(weekdayname[weekday()-1]);
      //lcd.print(" ");
      lcd.print(day(mt));
      lcd.print("/");
      lcd.print(month(mt));
      lcd.print("/");
      lcd.print(year(mt)-2000); 
    }
  }
  else {lcd.setCursor(0,1);
      lcd.print("Pas d'alarmes !");}
}

void showAlarm2() {
  int ptr=0;   
  if (eep.isPresent()) {
    //logRead();   
    Serial.println("Listing alarmes mémorisées");
    for (int c=0; c<alrmCount ; c++) 
    {
      iread=eep.ReadMem(c*11, Buffer, 11);
      delay(100);
      mt=0;
    
      for (int d=1; d<11 ; d++) 
      {
        mt = (Buffer[d]-48) + mt*10;     
      }
      printDigits(c+1);
      //Serial.print(mt);
      Serial.print(" ");
      printDigits(hour(mt));
      Serial.print(":");
      printDigits(minute(mt));
      Serial.print(":");
      printDigits(second(mt));
      Serial.print(" ");
      Serial.print(weekdayname[weekday(mt)-1]);
      Serial.print(" ");
      printDigits(day(mt));
      Serial.print("/");
      printDigits(month(mt));
      Serial.print("/");
      Serial.println(year(mt));
       
      ptr += 11;
    }
    if (ptr==0){ Serial.println("Pas d'alarmes");}  
  }
}

void setup()  {
  Serial.begin(9600);
  
  pinMode(alarmpin, OUTPUT);
  pinMode(buzzpin, OUTPUT);
  pinMode(memopin, OUTPUT);
  pinMode(reset, INPUT_PULLUP);
    
  while (!Serial) ; // wait until Arduino Serial Monitor opens
  setSyncProvider(RTC.get);   // the function to get the time from the RTC
  
  if(timeStatus()!= timeSet){ 
     Serial.println("Unable to sync with the RTC - Status timenotset");
     Serial.println("Use RTC set to update time of the DS1307");
     digitalClockDisplay();
  }
  else {Serial.println("RTC has set the system time");digitalClockDisplay();}
  Serial.print("Taille mémoire : ");
  Serial.println(eep.length());
  //getEEPROM();
  getLocation();
  lcd.begin(16,2);
  lcd.clear();
  
  LCDlastAlarm();
  //logRead();
  showAlarm2();
}

void loop()
{
   if (timeStatus() == timeSet) {   
    if (digitalRead(reset) == LOW) {    // si bouton de reset appuyé
      digitalWrite(memopin, LOW);       // éteindre led mémo
      Serial.print("Reset Alarme à : ");
      digitalClockDisplay();
      delay(500);
      alrmCount = 0;
      writeLocation=11*alrmCount;
      //saveEEPROM();
      //getEEPROM();
      saveLocation();
      //getLocation();
      texte[0]=255;
      eep.WriteMem(0, texte, 1);
      //logRead();
      showAlarm2();
      }  
    
    if (digitalRead(detectpin) == LOW) {    // si détection
      Serial.print(++alrmCount);
      Serial.print(" Alarme à : ");
      digitalClockDisplay();      // affiche dans moiteur série
      LCDClockDisplay();
      //mettre en format 10 chiffres l'heure alarme en format avec maketime(seconde, minute, heure, wday, day, month, year-1970)
      tm.Second=second();
      tm.Minute=minute();
      tm.Hour=hour();
      tm.Wday=weekday();
      tm.Day=day();
      tm.Month=month();
      tm.Year=year()-1970;
      mk=makeTime(tm);
      //Serial.println(mk);
      //Serial.println(mk,HEX);
      String val=String(mk,DEC);
      //Serial.println(val);
      //mémoriser dans eeprom avec incrémentation de 11 octets
      // 978307200 ref 01/01/2001 à minuit
            
      logAlarm(writeLocation, mk);
      //logRead();
      //Serial.print("Next location : ");
      writeLocation=11*alrmCount;
      //Serial.println(writeLocation); //next
      //saveEEPROM();
      //getEEPROM();
      saveLocation();
      //getLocation();
      //Serial.println();
      digitalWrite(alarmpin, HIGH);digitalWrite(buzzpin, HIGH);
      delay(500);
      while (digitalRead(detectpin) == LOW) {};
      digitalWrite(alarmpin, LOW);digitalWrite(buzzpin, LOW);digitalWrite(memopin, HIGH);
      delay(500);  //attente pour permettre l'alarme suivante
      }
   }
  else {  
    if (Serial.available()) processSyncMessage(); 
  }
      
}

void digitalClockDisplay(){
  // digital clock display of the time
  printDigits(hour());
  Serial.print(":");
  printDigits(minute());
  Serial.print(":");
  printDigits(second());
  Serial.print(" ");
  Serial.print(weekdayname[weekday()-1]);
  Serial.print(" ");
  printDigits(day());
  Serial.print("/");
  printDigits(month());
  Serial.print("/");
  Serial.print(year()); 
  Serial.println(); 
}
void LCDClockDisplay(){
  // digital clock display of the time
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("New alarm : ");
  lcd.print(alrmCount);
  lcd.setCursor(0,1);
  lcd.print(hour());
  lcd.print(":");
  lcd.print(minute());
  lcd.print(":");
  lcd.print(second());
  lcd.print(" ");
  //Serial.print(weekdayname[weekday()-1]);
  //lcd.print(" ");
  lcd.print(day());
  lcd.print("/");
  lcd.print(month());
  lcd.print("/");
  lcd.print(year()-2000);  
}

  
void printDigits(int digits){
  // utility function for digital clock display: prints preceding colon and leading 0  
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}

void processSyncMessage() {
  unsigned long pctime;
  const unsigned long DEFAULT_TIME = 1357041600; // Jan 1 2013

  if(Serial.find(TIME_HEADER)) {
     pctime = Serial.parseInt();
     if( pctime >= DEFAULT_TIME) { // check the integer is a valid time (greater than Jan 1 2013)
       setTime(pctime); // Sync Arduino clock to the time received on the serial port
       //Serial.print(epoch2string(pctime));
     }

  }
}

