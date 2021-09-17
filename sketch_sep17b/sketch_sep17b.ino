const int ledPin = 11;
const int potPin = A5;
int potmeterWaarde = 0;

void setup()
{
  pinMode(ledPin, OUTPUT);
  pinMode(potPin, INPUT);
}

void loop()
{
   potmeterWaarde = map(analogRead(potPin), 0, 1023, 0, 255);
   analogWrite(ledPin, potmeterWaarde);
}
