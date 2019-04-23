// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

const uint8_t scroll_bar[4][8] = {
    {B11111, B11111, B00000, B01010, B10101, B01010, B10101, B01010}, //0 
    {B10101, B01010, B00000, B11111, B11111, B00000, B10101, B01010}, //1 
    {B10101, B01010, B10101, B01010, B10101, B00000, B11111, B11111}, //2
    {B10101, B01010, B10101, B01010, B10101, B01010, B10101, B01010}  //3
  };
  
//init menu level
int year=2017; //init year 2000-xxxx
int month=1; //init month 1-12
int day=1; //init month 1-31
int weekday=0; //init week day 0 - sunday
byte hour=0;
byte minute=0;
byte lev0=0; //init level-0
byte lev1=0; //init level-1
int sel_item=0; //Selected item
int first_item=0; //Selected menu first item
int last_item=0; //Selected menu last item
int qty=0; //number of menu items
byte menu_sym=0x7e; //menu symbol
int del=250; //delay
byte mcols=16; //lcd display number of cols
byte mrows=2; //lcd display number of rows
bool clr=false;
bool mstate=false;
byte brightness=255; //default brightness
byte volume=50; //default volume
long previousMillis = 0;  // здесь будет храниться время последнего изменения состояния задержки анимации
long interval = 2000;      // интервал начала скроллинга в мс и оно же время убирания функционального меню
long previousMillis2 = 0;  // здесь будет храниться время последнего изменения состояния задержки анимации
long interval2 = 40;      // интервал между буквами скроллинга в мс
bool infunc=false; //показатель что находимся внутри выполнения функции меню


void lcd_clr() {
//clear screen function
lcd.clear();
lcd.setCursor(0,0);
lcd.print("CLEAR SCREEN");
delay(1000);
lcd_menu();
}

//set Lmenu
typedef struct {
  unsigned char* itemname;
  byte level;
  byte sublevel;
  bool checked;
  bool selected;
  void (*function)();
  } Lmenu;

Lmenu lmenu[]= {
    { "ROOT MENU",   0,  0,  false,  false, zero },
    { "SET TIME >",   0,  0,  false,  false, timelevel },
    { "LEVEL 2  >",   0,  0,  false,  false, nextlevel },
    { "Brightness",   0,  0,  false,  false, set_brightness },
    { "Brighter Lcd",   0,  0,  false,  false, brighter },
    { "Darker Lcd",   0,  0,  false,  false, darker },
    { "Lcd on/off",   0,  0,  false,  false, onoff },
    { "Volume",   0,  0,  false,  false, set_volume },
    { "Lorem ipsum dolor sit amet, consectetur adipiscing elit",   0,  0,  false,  false, zero },
    { "Ed do eiusmod tempor incididunt ut labore et dolore magna aliqua",   0,  0,  false,  false, zero },
    { "Go to Level 2 menu",   0,  0,  false,  false, nextlevel }, 
    { "Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat",   0,  0,  false,  false,zero },
    { "Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur",      0,  0,  false,  false,zero },
    { "Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laboru",   0,  0,  false,  false, zero },
    { "Clear function again",   0,  0,  false,  false, lcd_clr },
    { "TOP",   0,  0,  false,  false, endlev },
    
    { "MENU 2",   0,  1,  false,  false, prevlevel }, //level 2
    { "LEVEL 3 >",   0,  1,  false,  false, nextlevel },
    { "BACK",   0,  1,  false,  false, prevlevel },
    { "TOP",   0,  1,  false,  false, endlev },
    { "ROOT",   0,  1,  false,  false, rootlev }, 
    
    { "MENU 3",   0,  2,  false,  false, prevlevel }, //level 3
    { "Lcd on/off",   0,  2,  false,  false, onoff },
    { "SET TIME >",   0,  2,  false,  false, nextlevel },
    { "BACK",   0,  2,  false,  false, prevlevel },
    { "TOP",   0,  2,  false,  false, endlev },
    { "ROOT",   0,  2,  false,  false, rootlev },
    
    { "SET TIME",   0,  3,  false,  false, prevlevel}, //level 4
    { "Year",   0,  3,  false,  false, set_year },
    { "Month",   0,  3,  false,  false, set_month },
    { "Day",   0,  3,  false,  false, set_day },
    { "Weekday",   0,  3,  false,  false, set_weekday },
    { "Hour",   0,  3,  false,  false, set_hour },
    { "Minute",   0,  3,  false,  false, set_minute },
    { "BACK",   0,  3,  false,  false, prevlevel },
    { "TOP",   0,  3,  false,  false, endlev },
    { "ROOT",   0,  3,  false,  false, rootlev }
};


void level_recount() {
int i;
int j=0;
//найдем первый элемент этого меню
for (i=0; i<(sizeof(lmenu)/sizeof(Lmenu)); i++) {
if ((lev0==lmenu[i].level)&&(lev1==lmenu[i].sublevel)) {
if(j==0) {
sel_item=i;
first_item=i;
}
last_item=i;
j++;
}
}
qty=j;
}
void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.createChar(0, (uint8_t*)scroll_bar[0]); //0
  lcd.createChar(1, (uint8_t*)scroll_bar[1]); //1
  lcd.createChar(2, (uint8_t*)scroll_bar[2]); //2
  lcd.createChar(3, (uint8_t*)scroll_bar[3]); //3
// пример вывода: lcd.print("\0");
  analogWrite(10,brightness); //яркость на 10-м пине для DFRobot keypad shield 0-255
  lcd.clear();
  level_recount();
  lcd_menu();
}
 

byte key() {
//right 5 - 0
//up 3 - 98
//down 4 - 254
//left 2  - 408 (редко 409)
//select 1  - 640 (бывает и 642)
//rst - RESET
int val=analogRead(0);
if (val<50)  return 5; 
else if (val<150)  return 3; 
else if (val<400)  return 4; 
else if (val<500)  return 2; 
else if (val<800)  return 1; 
else   return 0; 
}

byte ncomm (byte command) {
lcd.setCursor(0,0);
switch (command) {
case 0: 
lcd.print("VOLUME"); 
break; 
case 1: 
lcd.print("BRIGHTNESS"); 
break;
case 2: 
lcd.print("YEAR"); 
break;
case 3: 
lcd.print("MONTH"); 
break;
case 4: 
lcd.print("DAY"); 
break;
case 5: 
lcd.print("WEEKDAY"); 
break;
case 6: 
lcd.print("HOUR"); 
break;
case 7: 
lcd.print("MINUTE"); 
break;
}  
}
byte scomm (byte command, byte val) {
lcd.setCursor(0,0);
switch (command) {
case 0: 
volume=val; 
break; 
case 1: 
brightness=val; 
bright(brightness);
break;
case 2: 
year=val; 
break; 
case 3: 
month=val; 
break; 
case 4: 
day=val; 
break; 
case 5: 
weekday=val; 
break; 
case 6: 
hour=val; 
break; 
case 7: 
minute=val; 
break; 
}  
}
byte set_var(byte command, int val, int maxlevel, int minlevel, int steps) {
previousMillis = millis();  // запоминаем текущее время
byte s;
lcd.clear();
ncomm(command);
infunc=true;
while(infunc==true) {
if (millis() - previousMillis > interval) {
s=key();
if((s==0)||(s==1))  {
infunc=false;
lcd_menu();
delay (500);
break;
} 
} 
lcd.setCursor(0,1);
for (s=0;s<10;s++) {
if (floor(val/(floor(maxlevel)/10))>s) { lcd.print((char)255); } else { lcd.print("\3"); }
}
if(val<10) {lcd.print(" ");}
if(val<100) {lcd.print(" ");}
if(val<1000) {lcd.print(" ");}
if(val<10000) {lcd.print(" ");}
if(val<100000) {lcd.print(" ");}
lcd.print(val);
delay(200);
switch(key()) {
case 1:
infunc=false;
lcd_menu();
delay (500);
break;
case 4:
 previousMillis = millis();  // запоминаем текущее время
 if( val>minlevel) { val-=steps; }
 scomm(command,val);
 break;
 case 2:
 previousMillis = millis();  // запоминаем текущее время
 if( val>minlevel) { val-=steps; }
 scomm(command,val);
 break;
 case 3: 
 previousMillis = millis();  // запоминаем текущее время
 if( val<maxlevel) { val+=steps; }
 scomm(command,val);
 break;
 case 5: 
 previousMillis = millis();  // запоминаем текущее время
 if( val<maxlevel) { val+=steps; }
 scomm(command,val);
 break;
}
}
return val;
}
void set_volume() {
set_var(0, volume, 100, 0, 5);
}
void set_brightness() {
set_var(1, brightness, 255, 0, 5);
}
void set_year() {
set_var(2, year, 2100, 2000, 1);
}
void set_month() {
set_var(3, month, 12, 1, 1);
}
void set_day() {
set_var(4, day, 31, 1, 1);
}
void set_weekday() {
set_var(5, weekday, 7, 1, 1);
}
void set_hour() {
set_var(6, hour, 23, 0, 1);
}
void set_minute() {
set_var(7, minute, 59, 0, 1);
}
void onoff() {
if(brightness==0){ brightness=255; } else { brightness=0; }
analogWrite(10,brightness);
delay(500);
}
void bright(byte val) {
analogWrite(10,val);
}
void brighter() {
if(brightness<255) {brightness+=1;}
bright(brightness);
delay(10);
}
void darker() {
if(brightness>=1) {brightness-=1;}
bright(brightness);
delay(10); 
}

void zero() {
//empty fuction
return;
}
void endlev() {
lcd.clear();
infunc=true;
level_recount();
sel_item=first_item;
delay(200);
infunc=false;
lcd_menu();
return;
}
void nextlevel() {
lcd.clear();
infunc=true;
lev1++;
level_recount();
delay(200);
infunc=false;
lcd_menu();
return;
}
void timelevel() {
lcd.clear();
infunc=true;
lev1=3;
level_recount();
delay(200);
infunc=false;
lcd_menu();
return;
}
void prevlevel() {
lcd.clear();
infunc=true;
if(lev1>=1) { lev1--; }
level_recount();
delay(200);
infunc=false;
lcd_menu();
return;
}

void rootlev() {
lcd.clear();
infunc=true;
lev0=0;
lev1=0;
sel_item=0;
level_recount();
delay(200); 
infunc=false;
lcd_menu();
return;
}

void loop() {
//show menu
if (millis() - previousMillis > interval) {
previousMillis = millis();  // запоминаем текущее время
mstate=true;
if(infunc==false) {
str_animate();
}
}
if(clr==false) {
switch(key()) {
  
case 0: //нет нажатий
clr==false;
break;

case 1: //Select
if(infunc==false) {
run_menu();
} else {
infunc=false;
lcd_menu();
delay(1000);
}
break;

case 2: //left
if(infunc==false) {
if(volume>5) { volume-=5; }
set_var(0, volume ,100,0, 5);
}
break;

case 3: //Up
if(infunc==false) {
sel_item--;
if(sel_item<first_item) { sel_item=first_item; }
clr=true;
}
break;

case 4: //Down
if(infunc==false) { 
if(sel_item<last_item) {  
sel_item++; 
}
clr=true;
}
break;

case 5: //right
if(infunc==false) {
if(volume<100) { volume+=5; }
set_var(0, volume ,100, 0, 5);
}
break;
}

} else {
if(infunc!=true) {
if(key()==0) {
lcd_menu();
}
}
}
}



void lcd_menu() {
mstate=false;
infunc=false;
int i;
int j;
int row=0;
clr=false;
for (i=first_item; i<=last_item; i++) {
if ((i>=sel_item)&&(row<mrows)&&(lev0==lmenu[i].level)&&(lev1==lmenu[i].sublevel)) {
lcd.setCursor(0, row);
if(i==sel_item) {
lcd.print ((char)menu_sym); 
} else {
lcd.print(" "); 
}
//sprintf(nav," %d/%d",(i+1),qty);
int procent=ceil((sel_item-first_item)*100/qty);
char* item=lmenu[i].itemname;

//обрежем название
if(strlen(item)>(mcols-2)) {mstate=true;}
for(j=0; j<strlen(item); j++) { 
if(j<(mcols-2)) {
lcd.print(item[j]);
}
}
//курсорами добьем до конца
for(j=(strlen(item)+1); j<(mcols-1); j++) { 
lcd.print(" ");
}

//сформируем navbar
if ((i==(qty-1))||(row==(mrows-1)))  { 
//низ
if(procent>=55) {
if(procent>=70) {
if(procent>=90) {
lcd.write((uint8_t)2);    
} else {
lcd.write((uint8_t)1);  
}   
} else {
lcd.write((uint8_t)0); 
}
} else {
lcd.write((uint8_t)3);   
}
} else {
if ((i==first_item)||(i==sel_item)){
//верх
if(procent<=55) {
if(procent<=35) {
if(procent<=20) {
lcd.write((uint8_t)0);   
} else{
lcd.write((uint8_t)1);   
} 
} else {
lcd.write((uint8_t)2); 
}
} else {
lcd.write((uint8_t)3);   
}
} else {
if (sel_item==qty){
//последний элемент меню на экране
lcd.write((uint8_t)2);  
} else {
//все остальное ||
lcd.write((uint8_t)3);
}

}
}
row++;
}
}

//очистка последней строки
if(row<=(mrows-1)) {
for(j=row; j<mcols; j++) {
lcd.setCursor(0, j);  
for(i=0; i<=mcols; i++) {
lcd.print(" ");
}
}
}
}

void run_menu() {
int j;
int i;
lmenu[sel_item].function();
}


void str_animate() {
int j;
int i;
if (infunc==false) {
char* item=lmenu[sel_item].itemname;
if((mstate==true)&&(strlen(item)>(mcols-2))) {
for(i=0; i<(strlen(item)+1); i++) { 
lcd.setCursor(1, 0); 
for(j=i; j<(strlen(item)+i); j++) { 
if((j<(mcols-2+i))&&(j<strlen(item))) {
lcd.print(item[j]);
if (millis() - previousMillis2 > interval2) {
previousMillis2 = millis();  // запоминаем текущее время
delay(interval2);
int val=analogRead(0);
if(val<1000) {mstate==false; return;}
}
} else {
if(j<(mcols-2+i)) {
lcd.print(" "); 
} 
}
}
}
//напечатаем строку снова
mstate=false;
lcd.setCursor(1, 0);
for(j=0; j<strlen(item); j++) { 
if(j<(mcols-2)) {
lcd.print(item[j]);
}
}
} else {
lcd.setCursor(1, 0);
for(j=0; j<strlen(item); j++) { 
if(j<(mcols-2)) {
lcd.print(item[j]);
}
}
mstate=false;
return;
}
} else {
 if (millis() - previousMillis > interval) {
previousMillis = millis();  // запоминаем текущее время
delay(interval);
infunc=false;
lcd_menu();
 } 
}
}



