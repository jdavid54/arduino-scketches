#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

/*
  U8glib Example Overview:
    Frame Buffer Examples: clearBuffer/sendBuffer. Fast, but may not work with all Arduino boards because of RAM consumption
    Page Buffer Examples: firstPage/nextPage. Less RAM usage, should work with all Arduino boards.
    U8x8 Text Only Example: No RAM usage, direct communication with display controller. No graphics, 8x8 Text only.
Constructor :
U8G2_R0  No rotation, landscape
U8G2_R1 90 degree clockwise rotation
U8G2_R2 180 degree clockwise rotation
U8G2_R3 270 degree clockwise rotation
U8G2_MIRROR No rotation, landscape, display content is mirrored (v2.6.x)
*/

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(/*No rotation, landscape*/U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

void setup(void) {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  
  u8g2.begin();
}

void loop(void) {
  //u8g2.clearBuffer();					// clear the internal memory
  u8g2.setFontDirection(0);
  digitalWrite(LED_BUILTIN, HIGH);
  u8g2.firstPage();
  do {
  //u8g2.setFont(u8g2_font_ncenB08_tr);	// choose a suitable font
  //u8g2.drawStr(0,10,"Hello World!");	// write something to the internal memory
  u8g2.setFont(u8g_font_unifont);
  u8g2.drawUTF8(0, 11, "26 Mai 2018"); // write something to the internal memory
  u8g2.drawUTF8(0, 24, "Convergence !");
  //Serial.println("Grève générale !");
  u8g2.drawUTF8(0, 37, "Grève générale !");
  u8g2.drawUTF8(0, 50, "Macron dehors ! ");
  u8g2.drawUTF8(0, 63, "Révolution !");
  //u8g2.sendBuffer();					// transfer internal memory to the display
  digitalWrite(LED_BUILTIN, LOW);
  } while ( u8g2.nextPage() );
  delay(1000);
}


