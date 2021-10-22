unsigned long currentTime = 0; // huidige millis tijd
unsigned long lastTime = 0; // moment bluetooth signaal laats verzonden
boolean started = false; // hij wil direct beginnen omdat verlopen tijd aan het begin kleiner is dan 30 sec, dus zorgen dat hij pas begint bij signaal, en anders eerst knipperd

int ledPins[] = {2,3,4};
int ledStatus[] = {LOW, LOW, LOW};

const int knopPin = 6; // voor tinkercad testen

void setup() {
  Serial.begin(9600);
  
  // zet relais pinnen als output
  for (int i = ledPins[0]; i <= ledPins[2]; i++) {
    pinMode(i, OUTPUT);
  }
  pinMode(knopPin, INPUT); // voor tinkercad testen
}

void loop() {
  currentTime = millis();
  get_input();
  update_stoplicht();
}

// kijk of er een bluetooth signaal binnen komt
void get_input() {
  if (Serial.available()) {
    int value = Serial.read();
    Serial.print(value);
    if (value == 1) {
      lastTime = millis();
      started = true;
    }
  }

  // voor tinkercad testen
  if (digitalRead(knopPin) == HIGH) {
    lastTime = millis();
    started = true;
  }
}

void update_stoplicht() {
  int elapsed = currentTime - lastTime; // verlopen tijd sinds signaal
  if (started) {
    if (elapsed <= 12000) { // 12 sec rood
      set_led(2, HIGH);
    } else if (elapsed <= 18000) { // 6 sec oranje
      set_led(3, HIGH);
    } else if (elapsed <= 30000) { // 12 sec groen
      set_led(4, HIGH);
    } else {
      started = false;
    }
  } else {
    // default oranje knipperlicht
    if ((currentTime / 1000) % 2 == 0) { // als tijd gedeeld door 1 sec een even getal is, licht aan, anders uit
      set_led(3, HIGH);
    } else {
      set_led(3, LOW);
    }
  }
}

void set_led(int pin, int value) {
  // min eerste pin voor juiste index in array
  ledStatus[pin - ledPins[0]] = value;
  for (int i = ledPins[0]; i <= ledPins[2]; i++) {
    // zet alle andere relais uit, zodat er niet meerdere lichten tegelijk kunnen branden
    if (i != pin) {
      ledStatus[i - ledPins[0]] = LOW;
    }
    // geef relais waarde
    digitalWrite(i, ledStatus[i - ledPins[0]]);
  }
}
