

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Ecran LCD branché sur la backpack LCD I2C (a l'adresse 0x3F)
const int i2c_addr = 0x3F;
// Dimension de l'écran 20 caractères par ligne, 4 lignes
const int  en = 2, rw = 1, rs = 0, d4 = 4, d5 = 5, d6 = 6, d7 = 7, bl = 3;
LiquidCrystal_I2C lcd(i2c_addr, en, rw, rs, d4, d5, d6, d7, bl, POSITIVE);  
//LiquidCrystal_I2C lcd(i2c_addr, 20, 4, LCD_5x8DOTS);
void setup()
{
  // Initialize l'ecran
  lcd.begin(20,4);
  //lcd.init();
  // Affiche des messages sur l'ecran
  lcd.backlight();
  lcd.home();
  lcd.print("LCD 20x4 Blanc/Bleu");
  lcd.setCursor(0,1); // colonne, ligne
  lcd.print("Disponible chez");
  lcd.setCursor(7,2); 
  lcd.print("MC Hobby Sprl");
  lcd.setCursor(0,3);
  lcd.print("--shop.mchobby.be--");
}

void loop()
{
  delay( 1000 );
}
