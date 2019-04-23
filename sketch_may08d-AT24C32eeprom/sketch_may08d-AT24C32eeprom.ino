#include <Wire.h>
#define AT24C32 0x50

byte data;
word a = 0;

byte highAddressByte(word address)
{
  byte BYTE_1;
  BYTE_1 = address >> 8;
  return BYTE_1;
}

byte lowAddressByte(word address)
{
  byte BYTE_1;
  byte BYTE_2;
  BYTE_1 = address >> 8;
  BYTE_2 = address - (BYTE_1 << 8);
  return BYTE_2;
}

void setup()
{ 
 Wire.begin();
 Serial.begin(9600);
 delay(1000); 

 //WRITE!!!!*******************************
 Wire.beginTransmission(AT24C32);

 Wire.write(highAddressByte(a));      //First Word Address
 Wire.write(lowAddressByte(a));      //Second Word Address

 Wire.write(0x41);      //Write an 'A'

 delay(10);

 Wire.endTransmission();
 delay(10);

 //READ!!!!*********************************
 Wire.beginTransmission(AT24C32);
 Wire.write(highAddressByte(a));      //First Word Address
 Wire.write(lowAddressByte(a));      //Second Word Address
 Wire.endTransmission();
 delay(10);

 Wire.requestFrom(AT24C32, 1);
 delay(10);
 data = Wire.read();
 Serial.write(data);      //Read the data and print to Serial port
 Serial.println();
 delay(10);
}

void loop()
{
}
