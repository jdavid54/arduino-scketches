int relay1=9;          //Port de sortie comande
int relay2=10;
int relay3=11;
int relay4=12;


void setup() {
  // put your setup code here, to run once:
  //pinMode(LED_BUILTIN, OUTPUT);
  //digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, HIGH);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Relais 1");
  digitalWrite(relay1, LOW);  
  delay(500);
  digitalWrite(relay1, HIGH);
  delay(500);
  //digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("Relais 2");
  digitalWrite(relay2, LOW);
  delay(500);
  digitalWrite(relay2, HIGH);
  delay(500);
  //digitalWrite(LED_BUILTIN, LOW);
  Serial.println("Relais 3");
  digitalWrite(relay3, LOW);
  delay(500);
  digitalWrite(relay3, HIGH);
  delay(500);
  //digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("Relais 4");
  digitalWrite(relay4, LOW);
  delay(500);
  digitalWrite(relay4, HIGH);
  delay(500);
  //digitalWrite(LED_BUILTIN, LOW);
}
