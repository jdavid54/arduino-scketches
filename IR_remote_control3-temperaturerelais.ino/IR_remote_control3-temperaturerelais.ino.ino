/*
  IR Receiver Demonstration 2
  IR-Rcv-Demo2.ino
  Determine IR codes manufacturer type with IR Receiver
  Displays results on Serial Monitor
  DroneBot Workshop 2017
  http://dronebotworkshop.com
*/

// Include IR Remote Library by Ken Shirriff
#include <IRremote.h>
#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>
// Include NewLiquidCrystal Library for I2C
#include <LiquidCrystal_I2C.h>

// Include DHT Libraries from Adafruit
// Dependant upon Adafruit_Sensors Library
#include "DHT.h";
#define DHTPIN 7       // DHT-11 Output Pin connection
#define DHTTYPE DHT11   // DHT Type is DHT 11
DHT dht(DHTPIN, DHTTYPE);


// Define Variables
float hum;    // Stores humidity value in percent
float temp;   // Stores temperature value in Celcius
float f;
float hi;     // en fahrenheit
float tmax;
float tmin;
float hmax;
float hmin;
bool RTCstatus = false;

// Define IR sensor pin
const int RECV_PIN = 4;
// Define IR Receiver and Results Objects
IRrecv irrecv(RECV_PIN);
decode_results results;
int relay1=9;         
int relay2=10;
int relay3=11;
int relay4=12;
int togglestate1=0;
int togglestate2=0;
int togglestate3=0;
int togglestate4=0;
int pdisplay=0;
int towait=500;
String weekdayname [] = {"Dimanche", "Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi"};
// LCD variables
const int  en = 2, rw = 1, rs = 0, d4 = 4, d5 = 5, d6 = 6, d7 = 7, bl = 3;
const int i2c_addr = 0x3F;
LiquidCrystal_I2C lcd(i2c_addr, en, rw, rs, d4, d5, d6, d7, bl, POSITIVE);

void updatetemp(){
    //delay(500);
    hum = dht.readHumidity();  // Get Humidity value    
    if (hum > hmax) {hmax=hum;}
    if (hum < hmin) {hmin=hum;}
    temp= dht.readTemperature();  // Get Temperature value
    if (temp > tmax) {tmax=temp;}
    if (temp < tmin) {tmin=temp;}
    f = dht.readTemperature(true);  // temp en fahrenheit
    hi = dht.computeHeatIndex(f, hum);
    lcd.setCursor(7,1);
    lcd.print(temp);
    lcd.setCursor(7,2);
    lcd.print(hum);
    lcd.setCursor(12,3);
    lcd.print(dht.convertFtoC(hi));      
}

void humtempdisplay(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("RETURN to go back");
  lcd.setCursor(0,1);
  lcd.print("Temp:        C");
  lcd.setCursor(0,2);
  lcd.print("Humid:       %");
  lcd.setCursor(0,3);
  lcd.print("T ressenti:       C");
  updatetemp();   
}

void relaydisplay(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Relais 1 ");
  if (togglestate1==1) {lcd.print("ON ");} else {lcd.print("OFF");}; 
  lcd.setCursor(0,1);
  lcd.print("Relais 2 ");
  if (togglestate2==1) {lcd.print("ON ");} else {lcd.print("OFF");};
  lcd.setCursor(0,2);
  lcd.print("Relais 3 ");
  if (togglestate3==1) {lcd.print("ON ");} else {lcd.print("OFF");};
  lcd.setCursor(0,3);
  lcd.print("Relais 4 ");
  if (togglestate4==1) {lcd.print("ON ");} else {lcd.print("OFF");};
}

void minmaxdisplay() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("RETURN to go back");
  lcd.setCursor(0,1);
  lcd.print("    Temper. Humidity");
  lcd.setCursor(0,2);
  lcd.print("max: ");
  lcd.print(tmax);
  lcd.print("   ");
  lcd.print(hmax);
  lcd.setCursor(0,3);
  lcd.print("min: ");
  lcd.print(tmin);
  lcd.print("   ");
  lcd.print(hmin);
}

void setup(){
  // Serial Monitor @ 9600 baud
  Serial.begin(9600);
  while (!Serial) ; // Needed for Leonardo only
  setSyncProvider(RTC.get);   // the function to get the time from the RTC
  if (timeStatus() != timeSet) {
     Serial.println("Unable to sync with the RTC");
     }
  else {
     Serial.println("RTC has set the system time");
     } 
  // Enable the IR Receiver
  irrecv.enableIRIn();
  dht.begin();
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, HIGH);
  lcd.begin(20,4);
  relaydisplay();  
  hum = dht.readHumidity();
  hmax=hum;
  hmin=hum;
  temp= dht.readTemperature();
  tmax=temp;
  tmin=temp;
}

void playrelay() {
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, HIGH);
  //chenillard
  digitalWrite(relay1, LOW);
  delay(towait);
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, LOW);
  delay(towait);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, LOW);
  delay(towait);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, LOW);
  delay(towait);
  digitalWrite(relay4, HIGH);
  if(togglestate1==1){digitalWrite(relay1, LOW);}
  if(togglestate2==1){digitalWrite(relay2, LOW);}
  if(togglestate3==1){digitalWrite(relay3, LOW);}
  if(togglestate4==1){digitalWrite(relay4, LOW);}
  
}
void downrelay() {
  digitalWrite(relay1, HIGH);togglestate1=0;
  digitalWrite(relay2, HIGH);togglestate2=0;
  digitalWrite(relay3, HIGH);togglestate3=0;
  digitalWrite(relay4, HIGH);togglestate4=0;
  relaydisplay();
}

void help() {
  lcd.setCursor(0,0);
  lcd.print("COLORsel-STOPshutAll");
  lcd.setCursor(0,1);
  lcd.print("TOPrelay-PLAYrunLed");
  lcd.setCursor(0,2);
  lcd.print("SETUP Temp/Hum");
  lcd.setCursor(0,3);
  lcd.print("DVD Min/Max Temp/Hum");
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
  //lcd.clear();
  //lcd.setCursor(0,0);
  //lcd.print("RTC -> system time");    
  lcd.setCursor(0,1);
  lcd.print(hour());
  lcd.print(":");
  LCDprintDigits(minute());
  lcd.print(":");
  LCDprintDigits(second());
  lcd.setCursor(0,2);
  lcd.print(weekdayname[weekday()-1]);
  lcd.print(" ");
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
#define TIME_HEADER  "T"   // Header tag for serial time sync message https://www.epochconverter.com/

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

void loop(){
  if (Serial.available()) {
    time_t t = processSyncMessage();
    if (t != 0) {
      RTC.set(t);   // set the RTC and the system time to the received value
      setTime(t);          
    }
  }
  if (irrecv.decode(&results)){
        Serial.println(results.value, HEX);
        
        digitalWrite(LED_BUILTIN,HIGH);
        switch(results.value){
   
        case 0x2FD12ED: //Pink Keypad Button
        //Serial.println("Pink button pressed : Relais 1");
        // Toggle LED On or Off
        if(togglestate1==0){
        digitalWrite(relay1, LOW);
        lcd.setCursor(0,0);
        if (pdisplay==0) {lcd.print("Relais 1 ON ");}
        togglestate1=1;
        }
        else {
        digitalWrite(relay1, HIGH);
        lcd.setCursor(0,0);
        if (pdisplay==0) {lcd.print("Relais 1 OFF");}
        togglestate1=0;
        }
        break;

        case 0x2FD926D: //Green Keypad Button
        //Serial.println("Green button pressed Relais 2");
        // Toggle LED On or Off
        if(togglestate2==0){
        digitalWrite(relay2, LOW);
        lcd.setCursor(0,1);
        if (pdisplay==0) {lcd.print("Relais 2 ON ");}
        togglestate2=1;
        }
        else {
        digitalWrite(relay2, HIGH);
        lcd.setCursor(0,1);
        if (pdisplay==0) {lcd.print("Relais 2 OFF");}
        togglestate2=0;
        }
        break;
        case 0x2FD52AD: //Yellow Keypad Button
        //Serial.println("Yellow button pressed : Relais 3");
        // Toggle LED On or Off
        if(togglestate3==0){
        digitalWrite(relay3, LOW);
        lcd.setCursor(0,2);
        if (pdisplay==0) {lcd.print("Relais 3 ON ");}
        togglestate3=1;
        }
        else {
        digitalWrite(relay3, HIGH);
        lcd.setCursor(0,2);
        if (pdisplay==0) {lcd.print("Relais 3 OFF");}
        togglestate3=0;
        }
        break;
        case 0x2FDD22D: //Blue Keypad Button
        //Serial.println("Blue button pressed : Relais 4");
        // Toggle LED On or Off
        if(togglestate4==0){
        digitalWrite(relay4, LOW);
        lcd.setCursor(0,3);
        if (pdisplay==0) {lcd.print("Relais 4 ON ");}
        togglestate4=1;
        }
        else {
        digitalWrite(relay4, HIGH);
        lcd.setCursor(0,3);
        if (pdisplay==0) {lcd.print("Relais 4 OFF");}
        togglestate4=0;
        }
        break;
        case 0x2FDE21D: //SET UP button
        Serial.println("SETUP button pressed : Menu Température/Humidité");
        pdisplay=1;  // affichage temp humidity
        humtempdisplay();
        break;
        case 0x2FDC23D : //RETURN button
        //Serial.println("RETURN button pressed : retour écran prédédent");
        if (pdisplay==1) {relaydisplay(); pdisplay=0;}     
        if (pdisplay==2) {humtempdisplay(); pdisplay=1;}
        if (pdisplay==3) {relaydisplay(); pdisplay=0;}
              
        break;
        case 0x2FDDA25 : //DVD MENU button
        //Serial.println("DVD MENU button pressed : Min Max menu");
        pdisplay=2;   //affichage min max
        minmaxdisplay();    
        break;

        case 0x2FDA25D : //TOP MENU button
        //Serial.println("TOP MENU button pressed : Menu Relais");
        pdisplay=0;   //affichage état relais
        relaydisplay();    
        break;

        case 0x2FD34CB : //PLAY button
        //Serial.println("PLAY button pressed : Chenillard");
        pdisplay=0;   //chenillard
        playrelay();
        relaydisplay();    
        break;

        case 0x2FDC837 : //STOP button
        //Serial.println("STOP button pressed : All relays down");
        pdisplay=0;   //All relays down
        downrelay();
        relaydisplay();    
        break;
        
        case 0x2FD6897 : //INFO button
        //Serial.println("INFO button pressed : Help menu");
        pdisplay=3;
        help();   
        break;

        case 0x2FDE817 : //TEXT button
        //Serial.println("TEXT button pressed");
        pdisplay=4;   //time display
        lcd.clear();lcd.setCursor(0,0);
        if (timeStatus() != timeSet) {
          lcd.print("Please set time");
          lcd.setCursor(0,1);
          lcd.print("in serial monitor");
          RTCstatus = false; 
          }
        else {
          lcd.print("RTC->system time OK"); 
          digitalClockDisplay();
          RTCstatus = true;    
        } 
        break;
    }
    
    digitalWrite(LED_BUILTIN,LOW);
    irrecv.resume(); 
  }
  if (pdisplay==1) {updatetemp();}
  if (pdisplay==4) {if (RTCstatus) {digitalClockDisplay();delay(1000);}}
  
}
