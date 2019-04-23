#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>
#include <Adafruit_SH1106.h>
#define OLED_RESET 4
Adafruit_SH1106 sh1106(OLED_RESET);
int buzzpin = 6;
int alarmpin = 11;  // blue
int detectpin = 2;
int memopin = 12;  //red
int reset = 8;    //reset button
bool toggle = true;
const char wstring_0[] PROGMEM = "Dimanche";
const char wstring_1[] PROGMEM = "  Lundi";
const char wstring_2[] PROGMEM = "  Mardi";
const char wstring_3[] PROGMEM = "Mercredi";
const char wstring_4[] PROGMEM = "  Jeudi";
const char wstring_5[] PROGMEM = "Vendredi";
const char wstring_6[] PROGMEM = " Samedi";
const char* const weekdayname[] PROGMEM  = {wstring_0, wstring_1, wstring_2, wstring_3, wstring_4, wstring_5, wstring_6};

unsigned long previousMillis = 0;

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

const char string_0[] PROGMEM = "Allons, enfants de la Patrie,\nLe jour de gloire est arrive!";
const char string_1[] PROGMEM = "Contre nous de la    tyrannie\nL'etendard sanglant est leve, (bis)";
const char string_2[] PROGMEM = "Entendez-vous dans   les campagnes\nMugir ces feroces soldats ?";
const char string_3[] PROGMEM = "Ils viennent jusque  dans vos bras\nEgorger vos fils, vos compagnes!\n";
const char string_4[] PROGMEM = "Refrain :\n\nAux armes, citoyens,\nFormez vos bataillons,";
const char string_5[] PROGMEM = "Marchons, marchons!\nQu'un sang impur\nAbreuve nos sillons!\n";
const char* const string_table[] PROGMEM = {string_0, string_1, string_2, string_3, string_4, string_5};
char b[70];
/*
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

void message() {
  sh1106.clearDisplay();
  sh1106.setTextSize(1);
  sh1106.setTextColor(WHITE);
  sh1106.setCursor(0,0);
  sh1106.println("Hello, world!");
  sh1106.setTextColor(BLACK, WHITE); // 'inverted' text
  sh1106.println(3.141592);
  sh1106.setTextSize(2);
  sh1106.setTextColor(WHITE);
  sh1106.print("0x"); sh1106.println(0xDEADBEEF, HEX);
  sh1106.display();
  delay(5000);
}
*/
void message2() {       //jour de semaine en bas 
  strcpy_P(b, (char*)pgm_read_byte_near(&(weekdayname[weekday()-1])));
  //Serial.println(b);
  sh1106.clearDisplay();
  sh1106.setTextSize(2);
  sh1106.setTextColor(WHITE);
  sh1106.setCursor(20,10);
  printDigits(hour());sh1106.print(":");printDigits(minute());sh1106.print(":");printDigits(second()); //sh1106.println();
  sh1106.setCursor(5,30);
  printDigits(day());sh1106.print("/");printDigits(month());sh1106.print("/");sh1106.println(year());
  sh1106.setTextSize(1);
  sh1106.setCursor(40,50);
  sh1106.print(b);   //jour de semaine
  sh1106.display();
  //delay(5000);
}

void message2b() {    //jour de semaine au milieu et logo phi
  strcpy_P(b, (char*)pgm_read_byte_near(&(weekdayname[weekday()-1])));   //copie dans buffer b
  //Serial.println(b);
  sh1106.clearDisplay();
  sh1106.drawBitmap(2, 5, logo16_glcd_bmp, LOGO16_GLCD_HEIGHT, LOGO16_GLCD_WIDTH, WHITE);   //logo phi
  sh1106.setTextSize(2);
  sh1106.setTextColor(WHITE);
  sh1106.setCursor(23,5);
  printDigits(hour());sh1106.print(":");printDigits(minute());sh1106.print(":");printDigits(second()); //sh1106.println();
  sh1106.setCursor(5,40);
  printDigits(day());sh1106.print("/");printDigits(month());sh1106.print("/");sh1106.println(year());
  sh1106.setTextSize(1);
  sh1106.setCursor(40,25);
  sh1106.print(b);    //jour de semaine
  sh1106.display();
  
  //delay(5000);
}

void printDigits(int digits){
  // utility function for digital clock display: prints preceding colon and leading 0  
  if(digits < 10)
    sh1106.print('0');
  sh1106.print(digits);
}
void message3() {  // affiche marseillaise
  
  sh1106.setTextSize(1);
  sh1106.setTextColor(WHITE);
  
  for (int i = 0; i < 3; i++){   //compteur de pages
    sh1106.clearDisplay();
    sh1106.setCursor(0,0);
    for (int j = 0; j < 2; j++)   //chaque page a 2 groupes
    {
      strcpy_P(b, (char*)pgm_read_word(&(string_table[i*2+j]))); // Necessary casts and dereferencing, just copy.
      Serial.println(b);
      sh1106.println(b);
      sh1106.display();
      tempo(3000); //tempo entre deux groupes
      if (toggle) return;
    }
    
    tempo(3000);  //tempo entre page
  }
  toggle = true;digitalWrite(memopin, LOW);
}
void tempo(int t) {
  unsigned long currentMillis = millis();
  while (currentMillis - previousMillis <= t) {
    currentMillis = millis();
    bouton();if (toggle) return;
  }
  previousMillis = currentMillis;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(alarmpin, OUTPUT);
  pinMode(buzzpin, OUTPUT);
  pinMode(memopin, OUTPUT);
  pinMode(reset, INPUT_PULLUP);
  
  setSyncProvider(RTC.get);
  //for (int c=0;c<1024;c++) {Serial.print(buffer[c],HEX);Serial.write("\t"); if ((c+1)%16==0) Serial.println();}
   sh1106.begin(SH1106_SWITCHCAPVCC, 0x3C);
   sh1106.display();       //logo adafruit
   delay(2000);
  // message2();
  // Clear the buffer.
  //sh1106.clearDisplay();
  // draw a bitmap icon and 'animate' movement
  //testdrawbitmap(logo16_glcd_bmp, LOGO16_GLCD_HEIGHT, LOGO16_GLCD_WIDTH);
}
void bouton() {
  if (digitalRead(reset) == LOW) {    // si bouton de reset appuyé
    //Serial.print(toggle);
      toggle = !toggle;
      if (!toggle) {digitalWrite(memopin, HIGH);} else {digitalWrite(memopin, LOW);}
      delay(500);
    //Serial.print(toggle);
  }
}
void loop() {
  //unsigned long currentMillis = millis();
  bouton();
  // put your main code here, to run repeatedly:
  if (toggle) {message2b();}   //pendule
  else {message3(); }  //marseillaise
}
