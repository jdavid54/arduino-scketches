/*

  HelloWorld.ino

  Universal 8bit Graphics Library (https://github.com/olikraus/u8g2/)

  Copyright (c) 2016, olikraus@gmail.com
  All rights reserved.

  Redistribution and use in source and binary forms, with or without modification,
  are permitted provided that the following conditions are met:

    Redistributions of source code must retain the above copyright notice, this list
    of conditions and the following disclaimer.

    Redistributions in binary form must reproduce the above copyright notice, this
    list of conditions and the following disclaimer in the documentation and/or other
    materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
  CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
  NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

/*
  U8glib Example Overview:
    Frame Buffer Examples: clearBuffer/sendBuffer. Fast, but may not work with all Arduino boards because of RAM consumption
    Page Buffer Examples: firstPage/nextPage. Less RAM usage, should work with all Arduino boards.
    U8x8 Text Only Example: No RAM usage, direct communication with display controller. No graphics, 8x8 Text only.
Constructor :
U8G2_R0  No rotation, landscape
U8G2_R1 90 degree clockwise rotation
U8G2_R2 180 degree clockwise rotation
U8G2_R3 270 degree clockwise rotation
U8G2_MIRROR No rotation, landscape, display content is mirrored (v2.6.x)
*/

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(/*No rotation, landscape*/U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
int v = 0x3c;
void setup(void) {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  u8g2.enableUTF8Print();
  //begin parameters : uint8_t menu_select_pin, uint8_t menu_next_pin, uint8_t menu_prev_pin, 
  //uint8_t menu_up_pin = U8X8_PIN_NONE, uint8_t menu_down_pin = U8X8_PIN_NONE, uint8_t menu_home_pin = U8X8_PIN_NONE
  u8g2.begin(2,3,4,U8X8_PIN_NONE,U8X8_PIN_NONE,U8X8_PIN_NONE);
}

void loop(void) {
  //u8g2.setDisplayRotation(U8G2_R1);
  u8g2.clearBuffer();					// clear the internal memory
  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.setFontRefHeightAll();    /* this will add some extra space for the text inside the buttons */
  int key=u8g2.userInterfaceMessage("Title1", "Title2", "Title3", " Ok \n Cancel ");
  Serial.print(key);
  delay(1000);
}


