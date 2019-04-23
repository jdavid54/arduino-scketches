/*
  LCD Display with I2C Interface Demo
  lcd-i2c-demo.ino
  Use NewLiquidCrystal Library
  DroneBot Workshop 2018
  https://dronebotworkshop.com
*/

// Include Wire Library for I2C
#include <Wire.h>
// Include NewLiquidCrystal Library for I2C
#include <LiquidCrystal_I2C.h>

// Define LCD pinout
const int  en = 2, rw = 1, rs = 0, d4 = 4, d5 = 5, d6 = 6, d7 = 7, bl = 3;

// Define I2C Address - change if reqiuired
const int i2c_addr = 0x3F;

LiquidCrystal_I2C lcd(i2c_addr, en, rw, rs, d4, d5, d6, d7, bl, POSITIVE);

void setup()
{

  // Set display type as 16 char, 2 rows
  lcd.begin(20,4);
  
  // Print on first row
  lcd.setCursor(0,0);
  lcd.print("Hello world!");
  
  // Wait 1 second
  delay(1000);
  
  // Print on second row
  lcd.setCursor(0,1);
  lcd.print("How are you?");
  
  // Wait 8 seconds
  delay(3000);
  
  // Clear the display
  lcd.clear();
  // Envoi du message
 lcd.setCursor(0, 0);
 lcd.print("3 avril 2018");
 lcd.setCursor(0,1);
 lcd.print("La greve a commence!");
 delay(1000);
 lcd.setCursor(0, 2);
 lcd.print("Macron, t'es foutu!");
 delay(1000);
 lcd.setCursor(0, 3);
 lcd.print("On est dans la rue!");
 delay(1000);

}


void loop()
{
 
 //lcd.autoscroll();
 

 
 //delay(300);
  for (int scrollCounter = 0; scrollCounter < 20; scrollCounter+=2) 
  { 

    lcd.scrollDisplayLeft(); 

    delay(350);
  }

}
