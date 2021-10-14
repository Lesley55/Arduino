#include <IRremote.h>

const int RECV_PIN = 6;
const int ledPins[] = {2,3,4,5}; // led pinnen
int blinkTimes[] = {0,200,500,800}; // tijd in ms dat elk lampje moet knipperen

unsigned long currentTime = 0; // huidige millis tijd
unsigned long lastTimes[] = {0,0,0,0}; // arduino millis tijd wanneer de laatste knipper van het lampje plaatsvond
unsigned long lastInput = 0;

int ledStatus[] = {LOW, LOW, LOW, LOW};

IRrecv irrecv(RECV_PIN); // maak nieuwe instantie aan

decode_results results; // resultaat om knop code in op te slaan

// afstandsbediening hex waardes van knoppen 0 tot 9
unsigned long buttons[] = {0xFF68971,0xFF30CF,0xFF18E7,0xFF7A85,0xFF10EF,0xFF38C7,0xFF5AA5,0xFF42BD,0xFF4AB5,0xFF52AD};

int new_led = -1; // onthoud led knop die is ingedrukt, zodat 2e keer als tijd word ingedrukt, hij de knop kan veranderen

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn(); // start de ir ontvanger

  // zet leds als output
  for (int i = 0; i < sizeof(ledPins); i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  currentTime = millis();
//  Serial.println(currentTime);
  handle_input();
  update_leds();
}

void handle_input() {
  if (currentTime - lastInput >= 100) { // wacht tussen inputs voor accurate waarde
    if (irrecv.decode(&results)) { // als ir een signaal geeft, ontvang het
      int number = get_input_number(results.value); // krijg de knop waarde van de hex
      change_blinking_times(number); // pas de knipper waardes aan als er op een knop gedrukt is
      irrecv.resume(); // laat ir luisteren naar nieuwe signalen
      lastInput = currentTime;
    }
  }
}

int get_input_number(long hex) {
  // knop 1 tot 4 voor led 1 tot 4
  for (int i = 0; i < 10; i++) {
    if (hex == buttons[i]) {
      return i;
    }
  }
}

void change_blinking_times(int number) {
  // bij eerste keer klikken kies led die je wil veranderen
  if (new_led == -1 && 1 <= number && number <= 4) {
    new_led = number;
  // bij tweede keer klikken verander knipper tijd van gekozen ledje
  } else if (new_led != -1) {
    // checken dat je geen lampje uitzet als er nog maar 2 branden
    if (blinkTimes[new_led] != 0 && number == 0 && count_leds_on() <= 2) {
      return;
    } else {
      blinkTimes[new_led] = number * 100;
      new_led = -1;
    }
  }
}

int count_leds_on() {
  // tel alle leds die aan staan
  int amount = 0;
  for (int i = 0; i < sizeof(blinkTimes); i++) {
    if (blinkTimes[i] > 0) {
      amount += 1;
    }
  }
  return amount;
}

void update_leds() {
  // loop door ledjes om te kijken of hij moet veranderen
//  Serial.println(sizeof(blinkTimes)); // zegt 8 maar array is 4?
//  for (int i = 0; i < sizeof(blinkTimes); i++) {
  for (int i = 2; i <= 5; i++) {
    update_led(i);
  }
}

void update_led(int t) {
  // zet lampje uit als knipper tijd 0 is
  if (blinkTimes[t] == 0) {
    digitalWrite(ledPins[t], LOW);
  // als verstreken tijd groter is dan knipper tijd, switch led aan of uit
  } else if (currentTime - lastTimes[t] >= blinkTimes[t]) {
    lastTimes[t] = currentTime;
    ledStatus[t] = (ledStatus[t] == LOW) ? HIGH : LOW; // verander low naar high of high naar low / knipper
    digitalWrite(ledPins[t], ledStatus[t]);
  }
}
