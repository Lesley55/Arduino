#include <Servo.h>

Servo servo;

const int triggerPin = 9;
const int echoPin = 8;
const int servoPin = 6;

int positie = 0; // van servo
float time; // tijd tussen zenden en weerkaatsen geluidssignaal
float distance; // afstand die het geluid heeft afgelegd

void setup() {
  servo.attach(servoPin);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // zorg dat de ultrasoon aan het begin geen geluid uitzend
  digitalWrite(triggerPin, LOW); // zet triggerpin op low
  delayMicroseconds(2); // wacht 2 microseconden zodat hij zekerweten niets uitzend
}

void loop() {
  read_ultrasoon();
  move_servo();
  delay(100); // minimaal 50ms wachten tussen metingen voor een accuraat resultaat
}

void read_ultrasoon() {  
  digitalWrite(triggerPin, HIGH); // start zenden geluidssignaal
  delayMicroseconds(10); // wacht 10 microseconden
  digitalWrite(triggerPin, LOW); // stop met zenden van geluidssignaal

  time = pulseIn(echoPin, HIGH); // krijg de tijd die het geluid nodig heeft om via een object terug te kaatsen

  distance = time / 58; // afstand is tijd gedeeld door geluidssnelheid
}

void move_servo() {
  // alleen naar positie draaien wanneer afstand tussen 4 en 10 zit
  if (4 <= distance && distance <= 10) {
    positie = map(distance, 4, 10, 180, 0); // map afstand naar graden die de servo moet draaien
  } else {
    positie = 0; // in rust op 0 graden
  }
  servo.write(positie); // zet servo positie
}
