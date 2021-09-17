const int ledPin = 12;
const int potPin = A5;
int potmeterWaarde = 0;
int d = 0;

void setup()
{
  pinMode(ledPin, OUTPUT);
  pinMode(potPin, INPUT);
}

void loop()
{
  potmeterWaarde = analogRead(potPin);
  digitalWrite(ledPin, HIGH);
  d = potmeterWaarde / 1023 * 500;
  delay(d);
  digitalWrite(ledPin, LOW);
}
