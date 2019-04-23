/*
 PROGMEM string demo
 How to store a table of strings in program memory (flash),
 and retrieve them.

 Information summarized from:
 http://www.nongnu.org/avr-libc/user-manual/pgmspace.html

 Setting up a table (array) of strings in program memory is slightly complicated, but
 here is a good template to follow.

 Setting up the strings is a two-step process. First define the strings.
*/

//#include <avr/pgmspace.h>
const char string_0[] PROGMEM = "Allons, enfants de la Patrie,\nLe jour de gloire est arrivé!";
const char string_1[] PROGMEM = "Contre nous de la tyrannie\nL'étendard sanglant est levé, (bis)";
const char string_2[] PROGMEM = "Entendez-vous dans les campagnes\nMugir ces féroces soldats ?";
const char string_3[] PROGMEM = "Ils viennent jusque dans vos bras\nEgorger vos fils, vos compagnes!\n";
const char string_4[] PROGMEM = "Refrain :\nAux armes, citoyens,\nFormez vos bataillons,";
const char string_5[] PROGMEM = "Marchons, marchons!\nQu'un sang impur\nAbreuve nos sillons!\n";


// Then set up a table to refer to your strings.

const char* const string_table[] PROGMEM = {string_0, string_1, string_2, string_3, string_4, string_5};

char buffer[100];    // make sure this is large enough for the largest string it must hold

void setup()
{
  Serial.begin(9600);
  while(!Serial); // wait for serial port to connect. Needed for native USB
  Serial.println("OK");
}


void loop()
{
  /* Using the string table in program memory requires the use of special functions to retrieve the data.
     The strcpy_P function copies a string from program space to a string in RAM ("buffer").
     Make sure your receiving string in RAM  is large enough to hold whatever
     you are retrieving from program space. */


  for (int i = 0; i < 6; i++)
  {
    strcpy_P(buffer, (char*)pgm_read_word(&(string_table[i]))); // Necessary casts and dereferencing, just copy.
    Serial.println(buffer);
    delay(2000 );
  }
}
