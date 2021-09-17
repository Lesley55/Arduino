const int ledPin9 = 9;
const int ledPin10 = 9;
const int ledPin11 = 9;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin9, OUTPUT);
  pinMode(ledPin10, OUTPUT);
  pinMode(ledPin11, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // loop langs alle mogelijkheden
  for (int i = 0; i <= 255; i++) {
    analogWrite(ledPin9, i);
    for (int j = 0; j <= 255; j++) {
      analogWrite(ledPin10, j);
      for (int k = 0; k <= 255; k++) {
        analogWrite(ledPin11, k);
        Serial.print(i);
        Serial.print(" ");
        Serial.print(j);
        Serial.print(" ");
        Serial.println(k);
      }
    }
  }
}
