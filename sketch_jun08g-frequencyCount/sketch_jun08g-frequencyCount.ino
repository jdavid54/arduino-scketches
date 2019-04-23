/*
 * Arduino Macro Frequency Counter
 * 
 * learnelectronics
 * 27 AUG 2017
 * 
 * www.youtube.com/c/learnelectronics
 * arduino0169@gmail.com
 * 
 * NOTES: Signal must be logic level
 *        Input pin is D5
 *        No analogWrite() on 3, 9, 10, 11
 */

#include <Wire.h>                                     //I2C library for the OLED
#include <Adafruit_SSD1306.h>                         //OLED driver
#include <FreqCount.h>                                //FreqCount library for you know...counting frequencies
                                                      //find it here: https://github.com/PaulStoffregen/FreqCount

#define OLED_RESET 4                                  //it's a thing




Adafruit_SSD1306 display(OLED_RESET);                 //create instance of the SSD1306 called display



void setup()   {                

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);          //begin the OLED @ hex addy )x3C
  display.display();                                  //show the buffer
  delay(2000);                                        //bask in the glory of LadyAda
  display.clearDisplay();                             //enough basking
  FreqCount.begin(1000);                              //start counting 1,2,3,4...

}


void loop() {

 
  if (FreqCount.available()) {                        //if the code if working
    float count = FreqCount.read();                   //create float var called count and populate it with current frequency count
    float period = (1/count);                         //create float var called period and populate it with the inverse of the frequency
  display.clearDisplay();                             //always clear the display first
  display.setTextSize(1);                             //smallest text size
  display.setTextColor(WHITE);                        //my only choice, really
  display.setCursor(0,0);                             //cursor to upper left
  display.println("Arduino Freq. Counter");           //print heading to buffer
  display.println("------- ----- -------");           //print some pretty line to buffer
  display.println("");                                //skip a line
  display.print("Freq:   ");                          //print the name of the function to buffer
  display.print(count);                               //print the actual counted frequency to buffer
  display.println("Hz");                              //print units to buffer & drop down 1 line
  display.print("Period: ");                          //print the name of the fuction to buffer
  display.print(period*1000);                         //print the period of signal in milliseconds to buffer
  display.print("mS");                                //print the units to buffer
  display.display();                                  //SHOW ME THE BUFFER!!!!
  }
  
  
  
} 
