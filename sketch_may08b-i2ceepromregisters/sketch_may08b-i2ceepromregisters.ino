
#include <Wire.h>
uint8_t registerBuffer[32];
void setup()
{
Wire.begin();
Serial.begin(9600); 
}
void loop()
{
 if(getBlockOfRegisters(0x50, 12, 32, registerBuffer))
 {
   // do stuff with the data
 }
 delay(500);
}

boolean getBlockOfRegisters(int i2c_addr, int firstRegister, int numRegisters, uint8_t *buffer)
{
 int error_code;
 boolean data_valid = false;
   Wire.beginTransmission(i2c_addr);                              
   Wire.write(firstRegister);               
   error_code  = Wire.endTransmission();    
   if ( error_code )
   {
        Serial.print( "i2c set register error : " );
        Serial.println(error_code);
   } 
   Wire.requestFrom(i2c_addr, numRegisters);
   if(Wire.available() == numRegisters)    
   { 
      data_valid = true;
      for(int i = numRegisters-1 ; i >= 0 ; i--)
       { buffer[i] = Wire.read();}   
   }    
   else
   { 
       Serial.print( "i2c data invalid: " ); 
       Serial.print( Wire.available());
       Serial.print(" received instead of ");
       Serial.print(numRegisters);
   } 
   return ( data_valid );
}
