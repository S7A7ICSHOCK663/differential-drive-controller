// Finite State Machine (FSM) Controller
// Uses built-in LED on Arduino Uno (pin 13)

enum State { IDLE, ACTIVE, ERROR };
State state = IDLE;

const int LED_PIN = 13;

unsigned long t0 = 0;
unsigned long lastBlink = 0;
int blinksDone = 0;

void enterState(State s) {
  state = s;
  t0 = millis();
  lastBlink = millis();
  blinksDone = 0;

  if (state == IDLE) digitalWrite(LED_PIN, LOW);
  if (state == ACTIVE) digitalWrite(LED_PIN, HIGH);
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  enterState(IDLE);
}

void loop() {
  unsigned long now = millis();

  switch (state) {
    case IDLE:
      if (now - t0 >= 2000) enterState(ACTIVE);
      break;

    case ACTIVE:
      if (now - t0 >= 3000) enterState(ERROR);
      break;

    case ERROR:
      if (now - lastBlink >= 200) {
        lastBlink = now;
        digitalWrite(LED_PIN, !digitalRead(LED_PIN));

        if (digitalRead(LED_PIN) == LOW) {
          blinksDone++;
          if (blinksDone >= 3) enterState(IDLE);
        }
      }
      break;
  }
}
