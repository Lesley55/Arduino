const int ledPin = 11;
const int knopPin = 10;
int statusKnop = 0; // status van de knop: LOW of HIGH
bool light = false; // toggle of het licht aan of uit staat

void setup()
{
  // zet led pin output en knop pin input
  pinMode(ledPin, OUTPUT);
  pinMode(knopPin, INPUT);
}

void loop()
{
  statusKnop = digitalRead(knopPin); // lees knop waarde uit
  
  if (statusKnop == HIGH) { // als knop word ingedrukt
    light = !light; // toggle licht, naar aan als uit, naar uit als aan
    delay(100); // wacht 100 ms zodat de code niet direct opnieuw uitvoerd als je de knop nog niet hebt losgelaten
  }
  if (light) {
    digitalWrite(ledPin, HIGH); // zet led aan
  } else {
    digitalWrite(ledPin, LOW); // zet led uit
  }
}
