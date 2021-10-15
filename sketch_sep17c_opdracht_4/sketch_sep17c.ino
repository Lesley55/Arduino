// sluit parameter aan op pin
const int tempPin = A5;
int tempMeter = 0; // temperatuur in graden celcius

void setup() {
  Serial.begin(9600); // start de seriele communicatie
}

void loop() {
  tempMeter = map(analogRead(tempPin), 0, 1023, 0, 500); // lees analoge waarde uit temperatuurmeter

  // print tempMeter waarde naar serial monitor
  Serial.print("Temperatuur in graden celcius = ");
  Serial.println(tempMeter);
}
