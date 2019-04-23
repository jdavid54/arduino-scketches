/*
  LCD Display with I2C Interface and DHT-11 Temp/Humid Sensor
  lcd-i2c-temp-humid.ino
  Use NewLiquidCrystal Library
  Use DHT Libraries from Adafruit
  DroneBot Workshop 2018
  https://dronebotworkshop.com
*/

// Include Wire Library for I2C
#include <Wire.h>
// Include NewLiquidCrystal Library for I2C
#include <LiquidCrystal_I2C.h>

// Include DHT Libraries from Adafruit
// Dependant upon Adafruit_Sensors Library
#include "DHT.h";

// Define LCD pinout
const int  en = 2, rw = 1, rs = 0, d4 = 4, d5 = 5, d6 = 6, d7 = 7, bl = 3;

// Define I2C Address - change if reqiuired
const int i2c_addr = 0x3F;

// DHT-22
#define DHTPIN 7       // DHT-22 Output Pin connection
#define DHTTYPE DHT11   // DHT Type is DHT 22 (AM2302)

// Define LCD display connections
LiquidCrystal_I2C lcd(i2c_addr, en, rw, rs, d4, d5, d6, d7, bl, POSITIVE);

// Define Variables
float hum;    // Stores humidity value in percent
float temp;   // Stores temperature value in Celcius
byte degree_symbol[8] = 
              {
                B00111,
                B00101,
                B00111,
                B00000,
                B00000,
                B00000,
                B00000,
                B00000
              };
byte heart_h[8] = {
  B00000,
  B00000,
  B01010,
  B10101,
  B10001,
  B01010,
  B00100,  
  B00000
}; 
byte heart_f[8] = {
  B00000,
  B00000,
  B01010,
  B11111,
  B11111,
  B01110,
  B00100,  
  B00000
}; 
// Setup DHT sensor for normal 16mhz Arduino
DHT dht(DHTPIN, DHTTYPE);
int z=1;
void setup() {
  Serial.begin(9600);
  // Set display type as 16 char, 2 rows
  lcd.begin(20,4);
  //Serial.print(degree_symbol);
  // Initialize DHT-22
  dht.begin();
  lcd.createChar(0, degree_symbol);
  lcd.createChar (1, heart_h);    // load  heart_h to memory 1
  lcd.createChar (2, heart_f);  // load heart_f to memory 2
    // Clear the display
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("I   Arduino");
  lcd.setCursor(0,1);
  lcd.print("Temp:       ");
  lcd.print(char(0));
  lcd.print("C");
  lcd.setCursor(0,2);
  lcd.print("Humid:      ");
  lcd.print(" %");
}

void loop()
{
  delay(500);  // Delay so DHT-11 sensor can stabalize
  z = z+1;
  hum = dht.readHumidity();  // Get Humidity value
  temp= dht.readTemperature();  // Get Temperature value
  // Print the heart
  lcd.setCursor(2,0);
  lcd.print(char(z));  
    // Print temperature on second line
  lcd.setCursor(7,1);
  lcd.print(temp);
 
  // Print humidity on third line
  lcd.setCursor(7,2);
  lcd.print(hum);
  
  if (z==2) z=0;
}
