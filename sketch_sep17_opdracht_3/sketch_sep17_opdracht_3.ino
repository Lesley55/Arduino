const int ledPin1 = 1;
const int ledPin2 = 2;
const int ledPin3 = 3;
const int ledPin4 = 4;
const int ledPin5 = 5;
const int ledPin6 = 6;
const int ledPin7 = 7;
const int potPin = A5;
int potmeterWaarde = 0; // potmeter voltage uitgedrukt tussen 0 en 1023

void setup()
{
  // zet 1 tot 7 pin outputs (had ook wel in een loopje gekund)
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);
  pinMode(ledPin5, OUTPUT);
  pinMode(ledPin6, OUTPUT);
  pinMode(ledPin7, OUTPUT);
  // zet pot pin als input
  pinMode(potPin, INPUT);
}

void loop()
{
  // lees potmeter waarde uit
  potmeterWaarde = analogRead(potPin);
  // loop door outputs van led lampjes
  for (int i = 1; i < 8; i++) {
    // verdeel maximale waarde, gedeeld door 7 lampjes, als led keer deelgroep binnen huidige waarde valt, zet led aan
    if (potmeterWaarde > 1023 / 7 * i) {
      digitalWrite(i, HIGH); // zet led aan
    } else {
      digitalWrite(i, LOW); // zet led uit
    }
  }
}
