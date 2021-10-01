int ledPin = 1;
int prev = 1;
bool forward = true;

// setup code word eenmalig uitgevoerd aan het begin
void setup() {
  // zet 1 tot 8 pin outputs
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(ledPin, HIGH); // zet led lampje aan
  delay(100); // delay van 1 sec
  digitalWrite(prev, LOW); // zet led lampje uit

  // naar volgende led gebaseerd op richting
  prev = ledPin; // vorige = huidige pin
  if (forward) {
    ledPin += 1; // ga naar volgende pin/lampje
  } else {
    ledPin -= 1; // ga naar vorige pin/lampje
  }
  
  // verander van richting
  if (ledPin == 1) {
    forward = true;
  } else if (ledPin == 8) {
    forward = false;
  }
}
