#include <Wire.h> 
#include <LiquidCrystal_I2C.h>



//#define BACKLIGHT_PIN     13

//LiquidCrystal_I2C lcd(0x3F);  // Set the LCD I2C address : 27 ou 3F

//LiquidCrystal_I2C lcd(0x3F, BACKLIGHT_PIN, POSITIVE);  // Set the LCD I2C address
// LCD variables
const int  en = 2, rw = 1, rs = 0, d4 = 4, d5 = 5, d6 = 6, d7 = 7, bl = 3;
const int i2c_addr = 0x27;           // Set the LCD I2C address : 27 ou 3F
LiquidCrystal_I2C lcd(i2c_addr, en, rw, rs, d4, d5, d6, d7, bl, POSITIVE);


void setup()
{
   
  lcd.begin(20,4);               // initialize the lcd 
  lcd.clear();                   // go home
  lcd.setCursor ( 0, 0 );
  lcd.print("Hello, ARDUINO ");  
  lcd.setCursor ( 0, 1 );        // go to the next line
  lcd.print (" FORUM - fm   ");
  delay ( 1000 );
}

void loop()
{
  
}
