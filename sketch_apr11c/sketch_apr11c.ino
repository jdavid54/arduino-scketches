char Str5[8] = "arduinoturi";
char Str6[] = "arduinoturi";
char myString[] = "This is the first line"
" this is the second line"
" etcetera";
char* myStrings[]={"This is String 1", "This is String 2", "This is String 3",
"This is String 4", "This is String 5","This is String 6"};
String thisString1 = String(13);
String thisString2 = String(13, HEX);
String thisString3 = String(13, BIN);
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
Serial.println(Str5);
Serial.println(Str6);
Serial.println(myString);
for (int i = 0; i < 6; i++){
   Serial.println(myStrings[i]);
   delay(500);
   }
Serial.println(thisString1);
Serial.println(thisString2);
Serial.println(thisString3);

String stringOne = "Hello String";                                     // using a constant String
Serial.println(stringOne);
String stringOne1 =  String('a');                                          // converting a constant char into a String
Serial.println(stringOne1);
String stringTwo =  String("This is a string");                 // converting a constant string into a String object
Serial.println(stringTwo);
String stringOne2 =  String(stringTwo + " with more"); // concatenating two strings
Serial.println(stringOne2);
String stringOne3 =  String(13);                                          // using a constant integer
Serial.println(stringOne3);
String stringOne4 =  String(analogRead(0), DEC);          // using an int and a base
Serial.println(stringOne4);
String stringOne5 =  String(45, HEX);                                // using an int and a base (hexadecimal)
Serial.println(stringOne5);
String stringOne6 =  String(255, BIN);                               // using an int and a base (binary)
Serial.println(stringOne6);
String stringOne7 =  String(millis(), DEC);                        // using a long and a base
Serial.println(stringOne7);
String stringOne8 =  String(5.698, 3); 
Serial.println(stringOne8);
}

void loop() {
  // put your main code here, to run repeatedly:

}
