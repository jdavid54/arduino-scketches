String longString="The starting index is inclusive (the corresponding character is included in the substring), but the optional ending index is exclusive (the corresponding character is not included in the substring). ";
char buf[81];

String permutLinebyReplace(String text){
  String line2=text.substring(20,40); //second line to change with third line
  String line3=text.substring(40,60); 
  text.replace(line2,line3); 
  return text;
}

String permutLinebyConcat(String text) {
  String line1=text.substring(0,20); 
  String line2=text.substring(20,40);
  String line3=text.substring(40,60); 
  String line4=text.substring(60,80);
  Serial.println("12345678901234567890");
  Serial.println(line1);
  Serial.println(line2);
  Serial.println(line3);
  Serial.println(line4);
  
  return line1+line3+line2+line4;
}
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
Serial.println(longString);
Serial.println(longString.substring(0,20));
longString.toCharArray(buf,21);
Serial.println(buf);
Serial.println("----------------");

String line=longString.substring(0,21);
line.toCharArray(buf,21);
Serial.println(buf);
Serial.println("----------------");

line=longString.substring(20,41);
line.toCharArray(buf,21);
Serial.println(buf);
Serial.println("----------------");

Serial.println(permutLinebyReplace(longString));
Serial.println("----------------");
Serial.println(permutLinebyConcat(longString));
Serial.println("----------------");
String textelong="Ce texte est tres long et doit s'etaler sur 4 lignes dans le bon ordre et non pas dans le desordre !";
Serial.println("12345678901234567890");
Serial.println(textelong);
Serial.println(permutLinebyConcat(textelong));
Serial.println("12345678901234567890123456789012345678901234567890123456789012345678901234567890");
}

void loop() {
  // put your main code here, to run repeatedly:

}
