#include <Wire.h>
#include <LiquidCrystal_I2C.h> // include lib according to your lcd type

// Constant for my lcd size, adjust to your lcd
#define LCDWIDTH 20
#define LCDHEIGHT 4

// Used lcd: mine is 0x3F type
const int  en = 2, rw = 1, rs = 0, d4 = 4, d5 = 5, d6 = 6, d7 = 7, bl = 3;

// Define I2C Address - change if required
const int i2c_addr = 0x3F;

LiquidCrystal_I2C lcd(i2c_addr, en, rw, rs, d4, d5, d6, d7, bl, POSITIVE);

int pinnedRow = LCDHEIGHT / 2;
int scrollingRow =  LCDHEIGHT / 2 - 1;
int scrollingSpeed = 200;

void setup() {
  lcd.begin(20, 4); // initialize with your correct lcd size here
  lcd.backlight();  
}

void loop() {
  lcd.clear();  
  char * pinnedString = (char *) F("by Goet");
  char * scrollingString = (char *) F("I don't like being long-winded type of guy, so I think i'll go straight to the point: this is a very long, long text scrolling on your lcd display :)");
  pinAndScrollText(pinnedString, pinnedRow, scrollingString, scrollingRow, scrollingSpeed);
  delay(2000);
  lcd.clear();
  lcd.print(F("Wait 2s"));
  delay(2000);
}

/* This procedure pins a given text in the center of a desired row while scrolling from right to left another given text on another desired row.
    Parameters:F
    char * pinnedText: pinned char string
    int pinnedRow: desired row for pinned String
    char * scrollingText: scrolling char string
    int scrollingRow: desired row for scrolling String
    int v = scrolling speed expressed in milliseconds
*/
void pinAndScrollText(char * pinnedText, int pinnedRow, char * scrollingText, int scrollingRow, int v) {
  if (pinnedRow == scrollingRow || pinnedRow < 0 || scrollingRow < 0 || pinnedRow >= LCDHEIGHT || scrollingRow >= LCDHEIGHT || strlen(pinnedText) > LCDWIDTH || v < 0) {
    lcd.clear();
    lcd.print(F("Error"));
    while (1);
  }
  int l = strlen(pinnedText);
  int ls = strlen(scrollingText);
  int x = LCDWIDTH;
  int n = ls + x;
  int i = 0;
  int j = 0;
  char c[ls + 1];
  flashCharSubstring(pinnedText, c, 0, l);
  lcd.setCursor(l % 2 == 0 ? LCDWIDTH / 2 - (l / 2) : LCDWIDTH / 2 - (l / 2) - 1, pinnedRow);
  lcd.print(c);
  while (n > 0) {
    if (x > 0) {
      x--;
    }
    lcd.setCursor(x, scrollingRow);
    if (n > LCDWIDTH) {
      j++;
      i = (j > LCDWIDTH) ? i + 1 : 0;
      flashCharSubstring(scrollingText, c, i, j);
      lcd.print(c);
    } else {
      i = i > 0 ? i + 1 : 0;
      if (n == ls) {
        i++;
      }
      flashCharSubstring(scrollingText, c, i, j);
      lcd.print(c);
      lcd.setCursor(n - 1, scrollingRow);
      lcd.print(' ');
    }
    n--;
    if (n > 0) {
      delay(v);
    }
  }
}

/* This procedure makes a char substring based on indexes from a given char string stored in progmem.
   The caller have to set its own buffer and pass its reference
   to the procedure. The procedure will fill the buffer with
   desired substring based on given indexes. Caller buffer size have
   to be at least big as desired substring length (plus null terminating char) of course.
   As a general rule, caller buffer should be: char buf[strlen(str) + 1].
   Example:
   char * string = (char*)F("Hello world!"); // or char string[] = (char[])F("Hello world!");
   char buf[strlen(string) + 1];
   flashCharSubstring(string, buf, 0, 5);
   Serial.println(buf); // output: "Hello"
    Parameters:
    const char *str: string from where to extract the substring
    char *buf: reference of the caller buffer.
    int inf: lower bound, included
    int sup: upper bound, excluded
*/
void flashCharSubstring(const char *str, char *buf, int inf, int sup) {
  int l = sup - inf;
  for (int i = 0; i < l; i++) {
    buf[i] = pgm_read_byte_near(&str[i + inf]);
  }
  buf[l] = '\0';
}
