#include <AT24Cxx.h>
#include <EEPROM.h>

#define AT24Cxx_CTRL_ID 0x50
AT24Cxx eep;

byte Buffer[200];

unsigned int alrmCount=15;
uint8_t writeLocation = 0;
uint8_t locationMem = -1;

void saveLocation() {
  if (eep.isPresent()) {
    Buffer[0]=alrmCount;
    eep.WriteMem(locationMem, Buffer, 1);
    Serial.println(alrmCount);
    Serial.println("Saved");
  }
}

void getLocation() {
  if (eep.isPresent()) {
    alrmCount = 0;
    Buffer[0]= 0;
    eep.ReadMem(locationMem, Buffer, 1);
    alrmCount =  Buffer[0];
    writeLocation = 11*alrmCount;
    Serial.println(writeLocation);
    Serial.println("Get done");
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  saveLocation();
  getLocation();
}

void loop() {
  // put your main code here, to run repeatedly:

}
