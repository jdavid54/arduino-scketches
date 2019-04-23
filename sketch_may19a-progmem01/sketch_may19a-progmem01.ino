#include <Wire.h>
#include <Adafruit_SH1106.h>
#define OLED_RESET 4
Adafruit_SH1106 sh1106(OLED_RESET);

//const uint16_t charSet[]  = { 65000, 32796, 16843, 10, 11234};
//String weekdayname [] = {"Dimanche", "Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi"};
//char buffer[10]="1234567890";
#define NUMFLAKES 8
#define XPOS 0
#define YPOS 1
#define DELTAY 2


#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 
static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ B00000110, B00000000,
  B00011100, B01111000,
  B00111000, B11111100,
  B01110001, B11001110,
  B11100011, B10000111,
  B11100011, B10000011,
  B11100011, B10000011,
  B11100111, B00000111,
  B01110111, B00001110,
  B00111111, B00011100,
  B00011111, B11111000,
  B00001111, B11100000,
  B00001110, B00000000,
  B00001110, B00000000,
  B00011110, B00000000,
  B00011100, B00000000 };

void testdrawbitmap(const uint8_t *bitmap, uint8_t w, uint8_t h) {
  uint8_t icons[NUMFLAKES][3];
 
  // initialize
  for (uint8_t f=0; f< NUMFLAKES; f++) {
    icons[f][XPOS] = random(sh1106.width());
    icons[f][YPOS] = 0;
    icons[f][DELTAY] = random(5) + 1;
    
    Serial.print("x: ");
    Serial.print(icons[f][XPOS], DEC);
    Serial.print(" y: ");
    Serial.print(icons[f][YPOS], DEC);
    Serial.print(" dy: ");
    Serial.println(icons[f][DELTAY], DEC);
  }

  while (1) {
    // draw each icon
    for (uint8_t f=0; f< NUMFLAKES; f++) {
      sh1106.drawBitmap(icons[f][XPOS], icons[f][YPOS], logo16_glcd_bmp, w, h, WHITE);
    }
    sh1106.display();
    delay(200);
    
    // then erase it + move it
    for (uint8_t f=0; f< NUMFLAKES; f++) {
      sh1106.drawBitmap(icons[f][XPOS], icons[f][YPOS],  logo16_glcd_bmp, w, h, BLACK);
      // move it
      icons[f][YPOS] += icons[f][DELTAY];
      // if its gone, reinit
      if (icons[f][YPOS] > sh1106.height()) {
  icons[f][XPOS] = random(sh1106.width());
  icons[f][YPOS] = 0;
  icons[f][DELTAY] = random(5) + 1;
      }
    }
   }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //for (int c=0;c<1024;c++) {Serial.print(buffer[c],HEX);Serial.write("\t"); if ((c+1)%16==0) Serial.println();}
   sh1106.begin(SH1106_SWITCHCAPVCC, 0x3C);
   sh1106.display();
   delay(2000);

  // Clear the buffer.
  sh1106.clearDisplay();
  // draw a bitmap icon and 'animate' movement
  testdrawbitmap(logo16_glcd_bmp, LOGO16_GLCD_HEIGHT, LOGO16_GLCD_WIDTH);
}

void loop() {
  // put your main code here, to run repeatedly:

}
