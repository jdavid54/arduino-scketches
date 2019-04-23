// include the library code:
#include <LiquidCrystal.h>
#include <SimpleDHT.h>
int pinDHT11 = 22;
SimpleDHT11 dht11;
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

byte h; //humidity
byte t; //temperature
bool ok = false;

void lcd_clr() {
//clear screen function
lcd.clear();
lcd.setCursor(0,0);
lcd.print("CLEAR SCREEN");
delay(1000);
//lcd_menu();
}

void show_humtemp(byte command, byte h, byte t) { 

//lcd.clear();
delay (2000);

lcd.setCursor(0,0);
ok=dht11.read(pinDHT11, &t, &h, NULL);   // si ok=0, on a des données correctes
if (ok)lcd.print("No data !"); else lcd.print("Data OK !") ;
lcd.setCursor(0,1);
if (ok) {
  lcd.print("--");
  lcd.print("*C ");
  lcd.print("--");
  lcd.print("%");
  return;
} 
lcd.print(t);
lcd.print("*C ");
lcd.print(h);
lcd.print("%");
//delay (500);
}

void humtemp() {
show_humtemp(10, h, t);
}

void setup() {
  // put your setup code here, to run once:
    lcd.begin(16, 2);
    lcd.clear();
}

void loop() {
  // put your main code here, to run repeatedly:
  humtemp();

}
