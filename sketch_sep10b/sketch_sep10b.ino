const int ledPin11 = 11;
const int knopPin = 10;
int statusKnop = 0;

int ledPin = 1;
bool forward = true;

void setup()
{
  pinMode(ledPin11, OUTPUT);
  pinMode(knopPin, INPUT);
  
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
}

void loop()
{
  statusKnop = digitalRead(knopPin);
  
  if (statusKnop == HIGH){
    while (true) {
      digitalWrite(ledPin, HIGH); // aan
      delay(100); // delay van 1 sec
      digitalWrite(ledPin, LOW); // uit

      // naar volgende led gebaseerd op richting
      if (forward) {
        ledPin += 1;
      } else {
        ledPin -= 1;
      }
      // verander van richting
      if (ledPin == 8) {
        forward = false;
      }
      if (ledPin == 0) {
        break;
      }
    }
    digitalWrite(ledPin11, HIGH);
    delay(30000);
  } else {
    digitalWrite(ledPin11, LOW);  
  }
}
