#include <Streaming.h>
#include <Time.h>
#include <TimeLib.h>

#define TIME_MSG_LEN  11   // time sync to PC is HEADER and unix time_t as ten ascii digits
#define TIME_HEADER  'T'-char(0) //84  Header tag "T" for serial time sync message
#define TIME_REQUEST  7    // ASCII bell character requests a time sync message 
int interval = 86400;
#define LEAP_YEAR(Y)     ( ((1970+Y)>0) && !((1970+Y)%4) && ( ((1970+Y)%100) || !((1970+Y)%400) ) )

String weekdayname [] = {"Dimanche", "Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi"};

void getPCtime() {
  Serial.println("Entering process :");
  //char header = "T";
  //Serial.println(header);
  //Serial.println(Serial.read() == TIME_HEADER);
  // if time available from serial port, sync the DateTime library
  while(Serial.available()>=  TIME_MSG_LEN){  // time message  >=  TIME_MSG_LEN 
    if(Serial.read() == TIME_HEADER ) {        
      Serial.println("Getting time message");
      time_t pctime = 0;
      for(int i=0; i < TIME_MSG_LEN -1; i++){   
        char c= Serial.read();          
        if( c >= '0' && c <= '9')   
          pctime = (10 * pctime) + (c - '0') ; // convert digits to a number            
      }   
      setTime(pctime);   // Sync DateTime clock to the time received on the serial port
    }  
  }
}
void processSyncMessage() {
  unsigned long pctime;
  const unsigned long DEFAULT_TIME = 1357041600; // Jan 1 2013

  if(Serial.find(TIME_HEADER)) {
     pctime = Serial.parseInt();
     if( pctime >= DEFAULT_TIME) { // check the integer is a valid time (greater than Jan 1 2013)
       setTime(pctime); // Sync Arduino clock to the time received on the serial port
       
     }

  }
}
void digitalClockDisplay(){
  // digital clock display of the time
  Serial.print(hour());
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

void printDigits(int digits){
  // utility function for digital clock display: prints preceding colon and leading 0  
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // setTime(iHr, iMi, iSe, iDa, iMo, iYr);
  setTime(21,27, 0, 3, 5, 2018);
  delay(100);
  Serial << now() << endl;
  //maketime
  tmElements_t myElements = {second(), minute(), hour(), weekday(), day(), month(), year()-1970 };
  time_t myTime = makeTime(myElements);
  Serial << myTime << endl;
  setSyncProvider(requestSync);  //set function to call when sync required
  setSyncInterval(interval);  // demande synchro dans un intervalle d'un jour 86400
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println(Serial.available());
  if (Serial.available()) {
    //processSyncMessage();
    getPCtime();
  }
  digitalClockDisplay();
  delay(1000);
}

time_t requestSync()
{
  Serial.write(TIME_REQUEST);
  Serial.println("Time sync request");  
  return 0; // the time will be sent later in response to serial mesg
}
