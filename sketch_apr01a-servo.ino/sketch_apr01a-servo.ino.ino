#include <Servo.h>
int pos=0;
int servoPin = 9;
int servoDelay = 25;

Servo myPointer;

void setup() {
  Serial.begin(9600);
  myPointer.attach(servoPin);

}

void loop() {
  Serial.println("Where would you like to position the servo? ");
  while (Serial.available()==0) {
  }
  pos=Serial.parseInt();
  myPointer.write(pos);
}
