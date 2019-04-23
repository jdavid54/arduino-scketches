/* 
 * TimeSerial.pde
 * example code illustrating Time library set through serial port messages.
 *
 * Messages consist of the letter T followed by ten digit time (as seconds since Jan 1 1970)
 * you can send the text on the next line using Serial Monitor to set the clock to noon Jan 1 2013
 T1357041600  
 *
 * A Processing example sketch to automatically send the messages is included in the download
 * On Linux, you can use "date +T%s\n > /dev/ttyACM0" (UTC time zone)
 */ 
 
#include <TimeLib.h>

#define TIME_HEADER  "T"   // Header tag for serial time sync message
#define TIME_REQUEST  7    // ASCII bell character requests a time sync message 

int buzzpin = 6;
int alarmpin = 12;
int detectpin = 7;
int val;
int interval = 86400;
unsigned long nowtime;

String weekdayname [] = {"Dimanche", "Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi"};
void setup()  {
  setSyncProvider(requestSync);  //set function to call when sync required
  setSyncInterval(interval);
  //nowtime = now();
  Serial.begin(9600);
  Serial.println(Serial);
  //while (!Serial) ; // Needed for Leonardo only
  pinMode(alarmpin, OUTPUT);
  pinMode(buzzpin, OUTPUT);
  pinMode(7, INPUT);
  Serial.println(timeStatus());
  setTime(1525425257);
  Serial.println(timeStatus());
  
  Serial.println(now());
  if (timeStatus() != timeSet) {Serial.println("Waiting for sync message");}
  digitalWrite(alarmpin, HIGH);
}

void loop(){    
  if (Serial.available()) {
    processSyncMessage();
  }
  if (timeStatus()!= timeNotSet) {
    val = digitalRead(detectpin);
    if (val == LOW) {
      digitalClockDisplay();
      digitalWrite(alarmpin, HIGH);digitalWrite(buzzpin, HIGH);
      delay(800);
      digitalWrite(alarmpin, LOW);digitalWrite(buzzpin, LOW);
      }  
  }
  if (timeStatus() == timeSet) {
    digitalWrite(alarmpin, LOW); // LED off if synced
  } else {
    //Serial.println("Waiting for sync message");
    //digitalWrite(alarmpin, HIGH);  // LED on if needs refresh
  }
  
}

void digitalClockDisplay(){
  Serial.println(now());
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

time_t requestSync()
{
  Serial.write(TIME_REQUEST);
  Serial.println("Time sync request");  
  return 0; // the time will be sent later in response to serial mesg
}

