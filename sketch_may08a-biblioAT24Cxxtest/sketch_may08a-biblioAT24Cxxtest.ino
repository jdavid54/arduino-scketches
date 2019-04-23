#include <Wire.h>
#include <AT24Cxx.h>

#define AT24Cxx_CTRL_ID 0x50

int iread;
char Buffer[200];
char texte[10]="";
String str;

// Initilaize using AT24CXX(i2c_address, size of eeprom in KB).  
AT24Cxx eep;

void clearEeprom() {
    uint8_t iAddr;
    Serial.println("Beginning Eeprom clear");
    
    for (iAddr=0; iAddr<100; iAddr++) {
      Wire.beginTransmission(AT24Cxx_CTRL_ID);
      Wire.write(iAddr>>8);   // Address MSB
      Wire.write(iAddr&0xff); // Address LSB
      Wire.write(255);delay(10);
      Wire.endTransmission();
      Serial.print(".");
    }
    
    Serial.println("\nEnd of Eeprom clear");
}

void logAlarm(uint8_t addr, unsigned long t){
  
  if (eep.isPresent()) {
    //Serial.println("logAlarm begins");
    //Serial.println(addr);
    //Serial.println(t);
    //String str;
    //char Buffer[66];
    //char texte[10]="";
    str=(String(t,DEC));
    //Serial.println(str);
    str = "A"+str;
    Serial.println(str);
    //Serial.println(str.length());
    str.toCharArray(texte,str.length()+1);
    /*for (int c=0; c<11; c++) {
      Serial.write(texte[c]);
    }*/
    //Serial.println();
    //Serial.println(sizeof(texte));
    eep.WriteMem(addr, texte, 11);
    delay(100);
    //then read
    Serial.println("Reading memory");
    iread=eep.ReadMem(0, Buffer, 200);
    delay(100);
    //Serial.println(iread);
    
    for (int c=0; c<iread; c++) {
      Serial.write(Buffer[c]);
    }
  }
  Serial.println();
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  clearEeprom();
  /*
  logAlarm(0,1525886000);
  logAlarm(11,1525886888);
  logAlarm(22,1525886333);
  logAlarm(33,1525886444);
  logAlarm(66,1525886777);
  logAlarm(55,1525886555);*/
}

void loop() {
  // put your main code here, to run repeatedly:

}
