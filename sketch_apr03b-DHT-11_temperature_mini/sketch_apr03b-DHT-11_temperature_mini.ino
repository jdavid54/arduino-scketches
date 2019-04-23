/*
  LCD Display with I2C Interface and DHT-11 Temp/Humid Sensor
  
  NewLiquidCrystal Library  :  https://github.com/marcmerlin/NewLiquidCrystal
  DHT Libraries from Adafruit : Adafruit Unified sensor et Adafruit AM2315

*/

// Include Wire Library for I2C
#include <Wire.h>
// Include NewLiquidCrystal Library for I2C      
#include <LiquidCrystal_I2C.h>

// Include DHT Libraries from Adafruit
// Dependant upon Adafruit_Sensors Library
#include "DHT.h";  // installe dans Sketch/Include Library/Manage Libraries les modules  : Adafruit Unified sensor et Adafruit AM2315 

// Define LCD pinout
const int  en = 2, rw = 1, rs = 0, d4 = 4, d5 = 5, d6 = 6, d7 = 7, bl = 3;

// Define I2C Address - change if reqiuired
const int i2c_addr = 0x3F;

// DHT-11
#define DHTPIN 7       // DHT-11 connecté sur pin 7
#define DHTTYPE DHT11   // DHT Type is DHT 11

// Define LCD display connections
LiquidCrystal_I2C lcd(i2c_addr, en, rw, rs, d4, d5, d6, d7, bl, POSITIVE);

// Define Variables
float hum;    // Stores humidity value in percent
float temp;   // Stores temperature value in Celcius

// Setup DHT sensor for normal 16mhz Arduino
DHT dht(DHTPIN, DHTTYPE);

void setup() {
 
  // Set display type as 20 char, 4 rows
  lcd.begin(20,4);
  
  // Initialize DHT-11
  dht.begin();
  // Clear the display
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Temp:       ");
  
  lcd.print(" C");
  lcd.setCursor(0,1);
  lcd.print("Humid:      ");
  lcd.print(" %");
}

void loop()
{
  delay(500);  // Delay so DHT-11 sensor can stabalize
  
  hum = dht.readHumidity();  // Get Humidity value
  temp= dht.readTemperature();  // Get Temperature value
 
  // Print temperature 
  lcd.setCursor(7,0);
  lcd.print(temp);
 
  // Print humidity 
  lcd.setCursor(7,1);
  lcd.print(hum);

}
