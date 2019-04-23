int value; 
unsigned long move2; // max 4294967295
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {

  while(Serial.available()==0){
              delay(100);
            }
          value = Serial.parseInt();

          //Serial.read();  //vide le buffer
 Serial.println(value);

}
