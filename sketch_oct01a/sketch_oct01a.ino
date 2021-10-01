#include <Servo.h>

Servo servo;
const int servoPin = 11;
const int potPin = A0;
int positie = 0;
int potmeterWaarde = 0;

void setup() {
  servo.attach(11);
  pinMode(potPin, INPUT);
}

void loop() {
  potmeterWaarde = map(analogRead(potPin), 0, 1023, 0, 180);

  for (int p = 0; p < potmeterWaarde; p += 1) {
    servo.write(p);
    delay(10);
    positie = p;
  }

  for (int p = positie; p > 0; p -= 1) {
    servo.write(p);
    delay(10);
  }
}
