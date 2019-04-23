/*
  *  Use the I2C bus with EEPROM 24LC64
  *  Sketch:    eeprom.ino
  *
  *  Author: hkhijhe
  *  Date: 01/10/2010
  *
  *
  */

#include <Wire.h>
bool exists = false;
bool result= false;
char buffer[30];

void i2c_eeprom_write_byte( int deviceaddress, unsigned int eeaddress, byte data ) {
    int rdata = data;
    Wire.beginTransmission(deviceaddress);
    Wire.write((int)(eeaddress >> 8)); // MSB
    Wire.write((int)(eeaddress & 0xFF)); // LSB
    Wire.write(rdata);
    Wire.endTransmission();
}

// WARNING: address is a page address, 6-bit end will wrap around
// also, data can be maximum of about 30 bytes, because the Wire library has a buffer of 32 bytes
bool i2c_eeprom_write_page( int deviceaddress, unsigned int eeaddresspage, byte* data, byte length ) {
    Wire.beginTransmission(deviceaddress);
    Serial.println("ic2-write-page");
    Wire.write((int)(eeaddresspage >> 8)); // MSB
    Wire.write((int)(eeaddresspage & 0xFF)); // LSB
    
    byte c;
    for ( c = 0; c < length; c++) {
      Serial.print(char(data[c]));
      Wire.write(data[c]);
      }
    if (Wire.endTransmission() != 0) {
    exists = false;
    Serial.println("badendtransmission-w");
    return false;
  }
  Serial.println("goodendtransmission-w");
  exists = true;
  return true;
    
}

byte i2c_eeprom_read_byte( int deviceaddress, unsigned int eeaddress ) {
    byte rdata = 0xFF;
    Wire.beginTransmission(deviceaddress);
    Wire.write((int)(eeaddress >> 8)); // MSB
    Wire.write((int)(eeaddress & 0xFF)); // LSB
    Wire.endTransmission();
    Wire.requestFrom(deviceaddress,1);
    if (Wire.available()) rdata = Wire.read();
    
    return rdata;
}

// maybe let's not read more than 30 or 32 bytes at a time!
void i2c_eeprom_read_buffer( int deviceaddress, unsigned int eeaddress, byte *buffer, int length ) {
    Wire.beginTransmission(deviceaddress);
    Wire.write((int)(eeaddress >> 8)); // MSB
    Wire.write((int)(eeaddress & 0xFF)); // LSB
    Wire.endTransmission();
    Wire.requestFrom(deviceaddress,length);
    int c = 0;
    for ( c = 0; c < length; c++ )
        if (Wire.available()) buffer[c] = Wire.read();
        Serial.write(buffer[c]);
}

void setup()
{
    char somedata[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234"; // data to write
    Wire.begin(); // initialise the connection
    Serial.begin(9600);
    Serial.println("Write begins");
    result=i2c_eeprom_write_page(0x50, 0, (byte *)somedata, sizeof(somedata)); // write to EEPROM
    Serial.println(result);
    if (exists) Serial.println("Write ends");
    delay(1000); //add a small delay

    Serial.println("Memory written");

    delay(1000);

    Serial.println("Reading begins");
    int addr=0; //first address
    byte b = i2c_eeprom_read_byte(0x50, 0); // access the first address from the memory
    Serial.write(b);
    i2c_eeprom_read_buffer(0x50, 0, buffer, sizeof(buffer)); // write to EEPROM
    int c=0;
    for ( c = 0; c < 30; c++ )
    Serial.write(buffer[c]);
    /*for ( 
    {
        Serial.write(b); //print content to serial port
        addr++; //increase address
        b = i2c_eeprom_read_byte(0x50, addr); //access an address from the memory
    }
    //Serial.println("x");
    delay(2000);
 */
}

void loop()
{
}
