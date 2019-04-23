// Include IR Remote Library by Ken Shirriff
#include <IRremote.h>
#include <Wire.h>
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
int display2 =0;
// LCD variables
const int  en = 2, rw = 1, rs = 0, d4 = 4, d5 = 5, d6 = 6, d7 = 7, bl = 3;
const int i2c_addr = 0x3F;     // Set the LCD I2C address : 27(green) ou 3F(blue)
LiquidCrystal_I2C lcd(i2c_addr, en, rw, rs, d4, d5, d6, d7, bl, POSITIVE);

void updatetemp(){
    //delay(500);
    hum = dht.readHumidity();  // Get Humidity value
    temp= dht.readTemperature();  // Get Temperature value
    lcd.setCursor(7,1);
    lcd.print(temp);
    lcd.setCursor(7,2);
    lcd.print(hum);      
}

void humtempdisplay(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("RETURN to go back");
  lcd.setCursor(0,1);
  lcd.print("Temp:        C");
  lcd.setCursor(0,2);
  lcd.print("Humid:       %");
  updatetemp();
   
}


void relaymenu(){
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

void setup(){
  // Serial Monitor @ 9600 baud
  Serial.begin(9600);
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
  relaymenu();
  
}

void loop(){
  if (irrecv.decode(&results)){
        Serial.println(results.value, HEX);
        
        digitalWrite(LED_BUILTIN,HIGH);
        switch(results.value){
   
          case 0x2FD12ED: //Pink Keypad Button
        // Toggle LED On or Off
        if(togglestate1==0){
        digitalWrite(relay1, LOW);
        lcd.setCursor(0,0);
        if (display2==0) {lcd.print("Relais 1 ON ");}
        togglestate1=1;
        }
        else {
        digitalWrite(relay1, HIGH);
        lcd.setCursor(0,0);
        if (display2==0) {lcd.print("Relais 1 OFF");}
        togglestate1=0;
        }
        break;

        case 0x2FD926D: //Green Keypad Button
        // Toggle LED On or Off
        if(togglestate2==0){
        digitalWrite(relay2, LOW);
        lcd.setCursor(0,1);
        if (display2==0) {lcd.print("Relais 2 ON ");}
        togglestate2=1;
        }
        else {
        digitalWrite(relay2, HIGH);
        lcd.setCursor(0,1);
        if (display2==0) {lcd.print("Relais 2 OFF");}
        togglestate2=0;
        }
        break;
        case 0x2FD52AD: //Yellow Keypad Button
        // Toggle LED On or Off
        if(togglestate3==0){
        digitalWrite(relay3, LOW);
        lcd.setCursor(0,2);
        if (display2==0) {lcd.print("Relais 3 ON ");}
        togglestate3=1;
        }
        else {
        digitalWrite(relay3, HIGH);
        lcd.setCursor(0,2);
        if (display2==0) {lcd.print("Relais 3 OFF");}
        togglestate3=0;
        }
        break;
        case 0x2FDD22D: //Blue Keypad Button
        // Toggle LED On or Off
        if(togglestate4==0){
        digitalWrite(relay4, LOW);
        lcd.setCursor(0,3);
        if (display2==0) {lcd.print("Relais 4 ON ");}
        togglestate4=1;
        }
        else {
        digitalWrite(relay4, HIGH);
        lcd.setCursor(0,3);
        if (display2==0) {lcd.print("Relais 4 OFF");}
        togglestate4=0;
        }
        break;
        case 0x2FDE21D: //SET UP button
        display2=1;
        humtempdisplay();
        break;
        case 0x2FDC23D : //RETURN button
        if (display2==1) {relaymenu();}
        display2=0;
        
        break;
    }
    
    digitalWrite(LED_BUILTIN,LOW);
    irrecv.resume(); 
  }
  if (display2==1) {updatetemp();}
}
