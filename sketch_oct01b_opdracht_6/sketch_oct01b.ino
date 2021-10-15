#include <Servo.h> // importeer servo bibliotheek

Servo servo; // maak servo object
const int knopPin9 = 9;
const int knopPin10 = 10;
const int servoPin = 11;

// waarde van knop: LOW of HIGH
int statusKnop9 = 0;
int statusKnop10 = 0;

boolean should_move = false; // mag alleen bewegen als een knop word ingedrukt
int positie = 0; // positie van servo
float flip_delay = 1; // delay tussen het zetten van servo positie in ms
int flip_direction = 1; // veranderen draaihoek met 1 of -1 graden
boolean wait_2sec = false; // beslis of servo bij 120 graden, 2 seconden moet wachten

void setup() {
  servo.attach(servoPin); // verbind de servo met pin 11
  // zet pin 9 en 10 als input
  pinMode(knopPin9, INPUT);
  pinMode(knopPin10, INPUT);
}

void loop() {
  get_button_input(); // kijk welke knoppen zijn ingedrukt
  decide_flip_mode(); // beslis of en hoe de servo moet draaien
  turn(); // verander de positie van de servo
  update_flip_direction(); // verander servo draairichting bij begin/einde
  wait_flip_delay(); // wacht
}

void get_button_input() {
  // lees waarde van knoppen uit
  statusKnop9 = digitalRead(knopPin9);
  statusKnop10 = digitalRead(knopPin10);
}

void decide_flip_mode() {
  should_move = true; // draaien als knop ingedrukt word
  if (statusKnop9 == HIGH and statusKnop10 == HIGH) {
    flip_delay = 1000 / 120; // stapsnelheid: tijd gedeeld door stappen
    wait_2sec = true;
  } else if (statusKnop9 == HIGH) {
    flip_delay = 1000 / 120; // stapsnelheid: tijd gedeeld door stappen
    wait_2sec = false;
  } else if (statusKnop10 == HIGH) {
    flip_delay = 500 / 120; // stapsnelheid: tijd gedeeld door stappen
    wait_2sec = false;
  } else {
    should_move = false; // geen knop ingedrukt, dus servo mag niet draaien
  }
}

void turn() {
  if (should_move) { // als knop ingedrukt word
    positie += flip_direction; // verander gewilde servo positie met 1 graad
    servo.write(positie); // draai servo
  }
}

void update_flip_direction() {
  // heen en weer tussen 0 en 120 graden, komt hij op einde, verander naar tegengestelde draairichting
  if (positie <= 0) {
    flip_direction = 1; // richting: vergroot draaihoek
  } else if (120 <= positie) {
    flip_direction = -1; // richting: verklein draaihoek
  }
}

void wait_flip_delay() {
  if (120 <= positie and wait_2sec) {
    delay(2000); // als op einde (120 graden) en beide knoppen ingedrukt, wacht 2 seconden
  } else {
    delay(flip_delay); // wacht tussen draaien om snelheid aan te passen
  }
}
