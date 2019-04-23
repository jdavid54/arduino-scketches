// Include IR Remote Library by Ken Shirriff
#include <IRremote.h>

// Define sensor pin
const int RECV_PIN = 4;

// Define IR Receiver and Results Objects
IRrecv irrecv(RECV_PIN);
decode_results results;
int relay1=9;         
int relay2=10;
int relay3=11;
int relay4=12;
int togglestate1=0;
int togglestate2=0;
int togglestate3=0;
int togglestate4=0;

void setup(){
  // Serial Monitor @ 9600 baud
  Serial.begin(9600);
  // Enable the IR Receiver
  irrecv.enableIRIn();
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, HIGH);
}

void loop(){
  if (irrecv.decode(&results)){
        Serial.println(results.value, HEX);
        switch (results.decode_type){
            case NEC: 
              Serial.println("NEC"); 
              break;
            case SONY: 
              Serial.println("SONY"); 
              break;
            case RC5: 
              Serial.println("RC5"); 
              break;
            case RC6: 
              Serial.println("RC6"); 
              break;
            case DISH: 
              Serial.println("DISH"); 
              break;
            case SHARP: 
              Serial.println("SHARP"); 
              break;
            case JVC: 
              Serial.println("JVC"); 
              break;
            case SANYO: 
              Serial.println("SANYO"); 
              break;
            case MITSUBISHI: 
              Serial.println("MITSUBISHI"); 
              break;
            case SAMSUNG: 
              Serial.println("SAMSUNG"); 
              break;
            case LG: 
              Serial.println("LG"); 
              break;
            case WHYNTER: 
              Serial.println("WHYNTER"); 
              break;
            case AIWA_RC_T501: 
              Serial.println("AIWA_RC_T501"); 
              break;
            case PANASONIC: 
              Serial.println("PANASONIC"); 
              break;
            case DENON: 
              Serial.println("DENON"); 
              break;
          default:
            case UNKNOWN: 
              Serial.println("UNKNOWN"); 
              break;
          }
        digitalWrite(LED_BUILTIN,HIGH);
        switch(results.value){
   
          case 0x2FD12ED: //Pink Keypad Button
        // Toggle LED On or Off
        if(togglestate1==0){
        digitalWrite(relay1, LOW);
        togglestate1=1;
        }
        else {
        digitalWrite(relay1, HIGH);
        togglestate1=0;
        }
        break;

        case 0x2FD926D: //Green Keypad Button
        // Toggle LED On or Off
        if(togglestate2==0){
        digitalWrite(relay2, LOW);
        togglestate2=1;
        }
        else {
        digitalWrite(relay2, HIGH);
        togglestate2=0;
        }
        break;
        case 0x2FD52AD: //Yellow Keypad Button
        // Toggle LED On or Off
        if(togglestate3==0){
        digitalWrite(relay3, LOW);
        togglestate3=1;
        }
        else {
        digitalWrite(relay3, HIGH);
        togglestate3=0;
        }
        break;
        case 0x2FDD22D: //Blue Keypad Button
        // Toggle LED On or Off
        if(togglestate4==0){
        digitalWrite(relay4, LOW);
        togglestate4=1;
        }
        else {
        digitalWrite(relay4, HIGH);
        togglestate4=0;
        }
        break;
        digitalWrite(LED_BUILTIN,LOW);
    }
    irrecv.resume(); 
  }
}
