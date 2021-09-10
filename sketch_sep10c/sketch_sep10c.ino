const int ledPin = 11;
const int knopPin = 10;
int statusKnop = 0;
bool light = false;

void setup()
{
  pinMode(ledPin, OUTPUT);
  pinMode(knopPin, INPUT);
}

void loop()
{
  statusKnop = digitalRead(knopPin);
  
  if (statusKnop == HIGH) {
    light = !light;
    delay(100);
  }
  if (light) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
}
