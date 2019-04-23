#include <Wire.h>
#define AT24Cxx_CTRL_ID 0x50
#include <AT24Cxx.h>
AT24Cxx eep;
byte data;
uint8_t iwrite, iread;

void clearEeprom() {
  uint8_t iAddr;
  for (iAddr=0; iAddr<4095; iAddr++) {
    Wire.beginTransmission(AT24Cxx_CTRL_ID);
    Wire.write(iAddr>>8);   // Address MSB
    Wire.write(iAddr&0xff); // Address LSB
    Wire.write(255);
    Wire.endTransmission();
  }  
}
char texte[100];
String str;


void setup()
{ 
 str = "01234567890123456789012345678901234567890123456789012345678901234567890123456789"; 
 Serial.begin(9600);
 //WRITE01!!!!*******************************
 Serial.println("Writing to EEPROM:");
 Serial.println("0         1         2         3         4         5         6         7");
 Serial.println(str);
 Serial.println(str.length()+1);
 str.toCharArray(texte,81);
 
 
 Wire.begin();
 Wire.beginTransmission(AT24Cxx_CTRL_ID);
 Wire.write(0x00);
 Wire.write(0x00);
  for(byte i=0; i<str.length(); i++){
    Wire.write(texte[i]);
    Serial.write(texte[i]);
  }
 if (Wire.endTransmission() != 0) {
    Serial.print("Erreur écriture");
  }
 Serial.println();

 //READ01!!!!*********************************
 Serial.println("Reading from EEPROM:");
 Wire.beginTransmission(AT24Cxx_CTRL_ID);
 Wire.write(0x00);
 Wire.write(0x00);
 if (Wire.endTransmission() != 0) {
    Serial.print("Erreur lecture");
  }
 delay(10);

 Wire.requestFrom(AT24Cxx_CTRL_ID, 81);   // read val bytes at address 
 delay(10);
 Serial.println("lecture");
 for(byte i=0; i<81; i++)      //Read 26 data bytes
 {
   data = Wire.read();
   
   Serial.write(data);
   
 }
 delay(10);
 Serial.println();
 //WRITE02!!!!*******************************
 
  Serial.println("Writing to EEPROM:2");
  iwrite=eep.WriteMem(0, texte, 81);
  Serial.println(iwrite);
  delay(100);

  
 //READ02!!!!*********************************
 Serial.println("Reading from EEPROM:2");
 Wire.beginTransmission(AT24Cxx_CTRL_ID);
 Wire.write(0x00);
 Wire.write(0x00);
 if (Wire.endTransmission() != 0) {
    Serial.print("Erreur lecture");
  }
 delay(10);

 iread=Wire.requestFrom(AT24Cxx_CTRL_ID, 81);   // read val bytes at address 
 delay(10);
 Serial.println("lecture2");
 Serial.println(iread);
 for(byte i=0; i<iread; i++)     
 {
   data = Wire.read();
   
   Serial.write(data);
   
 }
 delay(10);
Serial.println();
 //READ03!!!!*********************************
 Serial.println("Reading from EEPROM:3");
 iread=eep.ReadMem(0, texte, 81);
 Serial.println("lecture3");
 Serial.println(iread);
 
 for(byte i=0; i<iread; i++)      
 {
   Serial.write(texte[i]);
   //Serial.println();
 }
 delay(10);
}

void loop()
{
}
