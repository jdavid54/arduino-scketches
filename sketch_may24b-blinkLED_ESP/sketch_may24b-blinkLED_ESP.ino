/*
  ESP 32 Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
  The ESP32 has an internal blue LED at D2 (GPIO 02)
*/

int LED_BUILTIN2 = 2;

void setup() 
{
  Serial.begin(115200);
  pinMode(LED_BUILTIN2, OUTPUT);
}

void loop() 
{
  Serial.println("LED allumé");
  digitalWrite(LED_BUILTIN2, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);    // wait for a second
  Serial.println("LED éteint");
  digitalWrite(LED_BUILTIN2, LOW);    // turn the LED off by making the voltage LOW
  delay(500);                       // wait for a second
}
