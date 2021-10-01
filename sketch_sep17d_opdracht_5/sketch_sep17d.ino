const int ledPin9 = 9;
const int ledPin10 = 9;
const int ledPin11 = 9;

void setup() {
  // zet 9 tot 11 pin outputs
  pinMode(ledPin9, OUTPUT);
  pinMode(ledPin10, OUTPUT);
  pinMode(ledPin11, OUTPUT);
  Serial.begin(9600); // start seriele communicatie
}

void loop() {
  // loop langs alle (rgb led felheid en kleur) mogelijkheden / combinaties
  for (int i = 0; i <= 255; i++) { // eerste kleur
    analogWrite(ledPin9, i); // zet led kleur aan met felheid i
    for (int j = 0; j <= 255; j++) { // tweede kleur
      analogWrite(ledPin10, j); // zet led kleur aan met felheid j
      for (int k = 0; k <= 255; k++) { // derde kleur
        analogWrite(ledPin11, k); // zet led kleur aan met felheid k
        
        // laat rgb waardes zien op serial monitor
        Serial.print(i);
        Serial.print(" ");
        Serial.print(j);
        Serial.print(" ");
        Serial.println(k);
      }
    }
  }
}
