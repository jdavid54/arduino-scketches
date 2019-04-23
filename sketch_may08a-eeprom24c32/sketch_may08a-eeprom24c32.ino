#include <Wire.h>
#define address 0x50

int val = 100;
byte data;
void setup()
{ 
 Wire.begin();
 Serial.begin(9600);
 delay(1000); 

 //WRITE!!!!*******************************
 Serial.write(0x41);
 Wire.beginTransmission(address);
 Wire.write(0x00);      //First Word Address
 Wire.write(0x00);      //Second Word Address

 Wire.write(0x41);      //Write an 'A'

 delay(10);

 Wire.endTransmission();
 delay(10);

 //READ!!!!*********************************
 Wire.beginTransmission(address);
 Wire.write(0x00);      //First Word Address
 Wire.write(0x00);      //Second Word Address
 Wire.endTransmission();
 delay(10);

 Wire.requestFrom(address, 1);
 delay(10);
 data = Wire.read();
 Serial.print(data);
 Serial.write(data);      //Read the data and print to Serial port
 Serial.println();
 delay(10);
}

void loop()
{
}
