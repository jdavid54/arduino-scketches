int dirPin = 2;
int stepPin = 3; 
int stepTimeUs = 1000;
int dir = 0;

void setup() {
  pinMode(dirPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  Serial.begin(9600);
}

void runSteps(int count) {
  if (Serial.available()) {
    stepTimeUs = Serial.parseInt();
    Serial.println(stepTimeUs);
  }
  digitalWrite(dirPin, dir);
  for(int i = 0; i < count; i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(stepTimeUs / 2);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(stepTimeUs / 2);
  }
}

void loop() {
  dir = !dir;
  runSteps(1000);
  delay(500);
}


