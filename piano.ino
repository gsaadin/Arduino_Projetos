const int DO = 262;
const int RE = 294;
const int MI = 330;
const int FA = 349;
const int SOL = 392;
const int LA = 440;
const int SI = 494;
const int DO2 = 523;

const int DO_BUTTON = 12;
const int RE_BUTTON = 11;
const int MI_BUTTON = 10;
const int FA_BUTTON = 9;
const int SOL_BUTTON = 8;
const int LA_BUTTON = 7;
const int SI_BUTTON = 6;
const int DO2_BUTTON = 5;

const int BUZZER = 3;

void setup() {
  pinMode(BUZZER, OUTPUT);
}

void loop() {
  bool doRead = digitalRead(DO_BUTTON);
  bool reRead = digitalRead(RE_BUTTON);
  bool miRead = digitalRead(MI_BUTTON);
  bool faRead = digitalRead(FA_BUTTON);
  bool solRead = digitalRead(SOL_BUTTON);
  bool laRead = digitalRead(LA_BUTTON);
  bool siRead = digitalRead(SI_BUTTON);
  bool do2Read = digitalRead(DO2_BUTTON);

  if (doRead) {
    tone(BUZZER, DO);
    while (digitalRead(DO_BUTTON));
  }
  else if (reRead) {
    tone(BUZZER, RE);
    while (digitalRead(RE_BUTTON));
  }
  else if (miRead) {
    tone(BUZZER, MI);
    while (digitalRead(MI_BUTTON));
  }
  else if (faRead) {
    tone(BUZZER, FA);
    while (digitalRead(FA_BUTTON));
  }
  else if (solRead) {
    tone(BUZZER, SOL);
    while (digitalRead(SOL_BUTTON));
  }
  else if (laRead) {
    tone(BUZZER, LA);
    while (digitalRead(LA_BUTTON));
  }
  else if (siRead) {
    tone(BUZZER, SI);
    while (digitalRead(SI_BUTTON));
  }
  else if (do2Read) {
    tone(BUZZER, DO2);
    while (digitalRead(DO2_BUTTON));
  }
  else {
    noTone(BUZZER);
  }
}
