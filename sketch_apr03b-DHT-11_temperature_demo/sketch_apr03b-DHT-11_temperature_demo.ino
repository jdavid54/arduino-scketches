/*
  LCD Display with I2C Interface and DHT-11 Temp/Humid Sensor
  lcd-i2c-temp-humid.ino
  Use NewLiquidCrystal Library
  Use DHT from dht11.zip
  DroneBot Workshop 2018
  https://dronebotworkshop.com
*/

// Include Wire Library for I2C
#include <Wire.h>
// Include NewLiquidCrystal Library for I2C
#include <LiquidCrystal_I2C.h>

// Include DHT Libraries from Adafruit
// Dependant upon Adafruit_Sensors Library
#include "dht11.h";
dht11 DHT;
// Define LCD pinout
const int  en = 2, rw = 1, rs = 0, d4 = 4, d5 = 5, d6 = 6, d7 = 7, bl = 3;

// Define I2C Address - change if required
const int i2c_addr = 0x3F;

// DHT-11
#define DHTPIN 7       // DHT-11 Output Pin connection


// Define LCD display connections
LiquidCrystal_I2C lcd(i2c_addr, en, rw, rs, d4, d5, d6, d7, bl, POSITIVE);

// Define Variables
float hum;    // Stores humidity value in percent
float temp;   // Stores temperature value in Celcius

void setup() {
  
  // Set display type as 20 char, 4 rows
  lcd.begin(20,4);

}

void loop()
{
  delay(2000);  // Delay so DHT-22 sensor can stabalize
  
  //hum = dht.readHumidity();  // Get Humidity value
    //temp= dht.readTemperature();  // Get Temperature value
  DHT.read(DHTPIN);
  temp=DHT.temperature;
  hum=DHT.humidity;
    
    // Clear the display
    lcd.clear();
    
    // Print temperature on top line
    lcd.setCursor(0,0);
  lcd.print("Temp:  ");
  lcd.print(temp);
  lcd.print(" C");
  
  // Print humidity on bottom line
  lcd.setCursor(0,1);
  lcd.print("Humid: ");
  lcd.print(hum);
  lcd.print(" %");

}
