#include <Servo.h>

Servo servo;
const int knopPin9 = 9;
const int knopPin10 = 10;
const int servoPin = 11;

int statusKnop9 = 0;
int statusKnop10 = 0;

boolean should_move = false;
int positie = 0; // van servo
float flip_delay = 1; // in ms
int flip_direction = 1; // 1 of -1
boolean wait_2sec = false;

void setup() {
  servo.attach(11);
  pinMode(knopPin9, INPUT);
  pinMode(knopPin10, INPUT);
}

void loop() {
  get_button_input();
  decide_flip_mode();
  turn();
  update_flip_direction();
  wait_flip_delay();
}

void get_button_input() {
  statusKnop9 = digitalRead(knopPin9);
  statusKnop10 = digitalRead(knopPin10);
}

void decide_flip_mode() {
  should_move = true;
  if (statusKnop9 == HIGH and statusKnop10 == HIGH) {
    flip_delay = 1000 / 120; // stapsnelheid: tijd gedeeld door stappen
    wait_2sec = true;
  } else if (statusKnop9 == HIGH) {
    flip_delay = 1000 / 120;
    wait_2sec = false;
  } else if (statusKnop10 == HIGH) {
    flip_delay = 500 / 120;
    wait_2sec = false;
  } else {
    should_move = false;
  }
}

void turn() {
  if (should_move) {
    positie += flip_direction;
    servo.write(positie);
  }
}

void update_flip_direction() {
  if (positie <= 0) {
    flip_direction = 1;
  } else if (120 <= positie) {
    flip_direction = -1;
  }
}

void wait_flip_delay() {  
  if (120 <= positie and wait_2sec) {
    delay(2000);
  } else {
    delay(flip_delay);
  }
}
