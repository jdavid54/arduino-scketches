#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// LCD variables
const int  en = 2, rw = 1, rs = 0, d4 = 4, d5 = 5, d6 = 6, d7 = 7, bl = 3;
const int i2c_addr = 0x27;           // Set the LCD I2C address : 27(green) ou 3F(blue)

LiquidCrystal_I2C lcd(i2c_addr, en, rw, rs, d4, d5, d6, d7, bl, POSITIVE);

// Creat a set of new characters
const uint8_t charBitmap[][8] = {
   { 0xc, 0x12, 0x12, 0xc, 0, 0, 0, 0 },
   { 0x6, 0x9, 0x9, 0x6, 0, 0, 0, 0 },
   { 0x0, 0x6, 0x9, 0x9, 0x6, 0, 0, 0x0 },
   { 0x0, 0xc, 0x12, 0x12, 0xc, 0, 0, 0x0 },
   { 0x0, 0x0, 0xc, 0x12, 0x12, 0xc, 0, 0x0 },
   { 0x0, 0x0, 0x6, 0x9, 0x9, 0x6, 0, 0x0 },
   { 0x0, 0x0, 0x0, 0x6, 0x9, 0x9, 0x6, 0x0 },
   { 0x0, 0x0, 0x0, 0xc, 0x12, 0x12, 0xc, 0x0 }
   
};

void setup()
{
  int charBitmapSize = (sizeof(charBitmap ) / sizeof (charBitmap[0]));
  lcd.begin(20,4);               // initialize the lcd 20x4
   for ( int i = 0; i < charBitmapSize; i++ )
   {
      lcd.createChar ( i, (uint8_t *)charBitmap[i] );
   }
  lcd.home ();                   // go home
  lcd.print("Hello, ARDUINO ");  
  lcd.setCursor ( 0, 1 );        // go to the next line
  lcd.print (" FORUM - fm   ");
  delay ( 1000 );
}

void loop()
{
   //lcd.home ();         // idem setCursor (0,0) don't clear the screen
   //lcd.clear();
   
   // Do a little animation by writing to the same location
   for ( int i = 2; i < 4; i++ )
   {
      lcd.setCursor ( 0,i );
      for ( int j = 0; j < 20; j++ )
      {
         lcd.print (char(random(7)));
      }  
   }
   delay (200);
}
