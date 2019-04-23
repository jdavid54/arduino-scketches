#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(/*No rotation, landscape*/U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
//int v = 0x3c;
char key = 5;
//String weekdayname [] = {"Dimanche", "Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi"};

void SerialClockDisplay(){  
  Serial.print(hour());
  Serial.print(":");
  printDigits(minute());
  Serial.print(":");
  printDigits(second());
  Serial.print(" ");
  //Serial.print(weekdayname[weekday()-1]);
  Serial.print(" ");
  printDigits(day());
  Serial.print("/");
  printDigits(month());
  Serial.print("/");
  Serial.print(year()); 
  Serial.println();
}
void printDigits(int digits){
  // utility function for digital clock display: prints preceding colon and leading 0  
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}
void setup(void) {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  u8g2.enableUTF8Print();
  setSyncProvider(RTC.get);   // the function to get the time from the RTC
  /*
  if (timeStatus() != timeSet) {
     Serial.println("Unable to sync with the RTC");
     }
  else {
     Serial.println("RTC has set the system time");
     SerialClockDisplay();
     } 
  */
  //begin parameters : uint8_t menu_select_pin, uint8_t menu_next_pin, uint8_t menu_prev_pin, 
  //uint8_t menu_up_pin = U8X8_PIN_NONE, uint8_t menu_down_pin = U8X8_PIN_NONE, uint8_t menu_home_pin = U8X8_PIN_NONE
  u8g2.begin(2,3,4,U8X8_PIN_NONE,U8X8_PIN_NONE,U8X8_PIN_NONE);
  menu();
}
void rotation90() {
  u8g2.setDisplayRotation(U8G2_R1);
  key=5;
}
void menu(){
  u8g2.clearBuffer();          // clear the internal memory
  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.setFontRefHeightAll();    /* this will add some extra space for the text inside the buttons */
  key=u8g2.userInterfaceSelectionList("Menu", 1, "Horloge\nTempérature\nRelais");
  //Serial.print(key);
}
void message() {
  u8g2.clearBuffer();          // clear the internal memory
  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.setFontRefHeightAll();    /* this will add some extra space for the text inside the buttons */
  //while (u8g2.getMenuEvent()!= U8X8_MSG_GPIO_MENU_SELECT) {          }
  char b3[12];
  char b2[12];
  
  //int n;
  sprintf (b3, "%02u:%02u:%02u", hour(),minute(),second());
  //Serial.println(n);
  //Serial.print(hour());
  
  sprintf (b2, "%d/%02u/%d", day(),month(),year());
  
  /*
  char cstr[3];
  char cstr2[3];
  char cstr3[3];
  char cstr4[10];
  //char horloge[16];
  itoa(hour(), cstr, 10);
  itoa(minute(), cstr2, 10);
  itoa(second(), cstr3, 10);
  String wd=weekdayname[weekday()-1];
  wd.toCharArray(cstr4,8);
  char * sep= ":";*/
  
  key = u8g2.userInterfaceMessage( b3,"Jour", b2, "Ok");      
  //Serial.print(key);
  key=5;
}
void loop(void) {
  u8g2.firstPage();
  do {
    switch (key) {
  case 1:
    message();
    break;
  case 2:
    rotation90();
    break;
  case 3:
    u8g2.setDisplayRotation(U8G2_R0);key=5;
    break;
  default:
    menu();
}
  }while ( u8g2.nextPage() );
  
  delay(1000);
}


