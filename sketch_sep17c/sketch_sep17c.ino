// sluit parameter aan op pin
const int tempPin = A5;
int tempMeter = 0;

void setup() {
  Serial.begin(9600); // start de seriele communicatie
}

void loop() {
  tempMeter = map(analogRead(tempPin), 0, 1023, 0, 500); // lees anlaloge waarde uit

  Serial.print("Temperatuur in graden celcius = ");
  Serial.println(tempMeter);
}
