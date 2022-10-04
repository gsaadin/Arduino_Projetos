// ---------------------------- BIT BUTTONS ----------------------------

const byte BUTTON_BIT_1 = 9;                       // Button LED #1
const byte BUTTON_BIT_2 = 8;                       // Button LED #2
const byte BUTTON_BIT_3 = 7;                       // Button LED #3
const byte BUTTON_BIT_4 = 6;                       // Button LED #4
const byte BUTTON_BIT_5 = 5;                       // Button LED #5
const byte BUTTON_BIT_6 = 4;                       // Button LED #6
const byte BUTTON_BIT_7 = 3;                       // Button LED #7
const byte BUTTON_BIT_8 = 2;                       // Button LED #8

// -------------------------- SHIFT REGISTER ---------------------------

const byte SER = A0;                               // SERIAL pin
const byte CLK = A1;                               // CLOCK pin
const byte LATCH = A2;                             // LATCH pin

// ------------------------------ STATES -------------------------------

byte state1 = 0;                                   // LED #1 state
byte state2 = 0;                                   // LED #2 state
byte state3 = 0;                                   // LED #3 state
byte state4 = 0;                                   // LED #4 state
byte state5 = 0;                                   // LED #5 state
byte state6 = 0;                                   // LED #6 state
byte state7 = 0;                                   // LED #7 state
byte state8 = 0;                                   // LED #8 state

// ------------------------------- LEDS --------------------------------

const byte LOW_LED = 13;                           // Low similarity LED (red)
const byte MEDIUM_LED = 12;                        // Medium similarity LED (yellow)
const byte HIGH_LED = 11;                          // High similarity LED (green)
const byte VICTORY_LED = 10;                       // Victory LED (white)

// ------------------------------ OTHERS -------------------------------

byte similarity;                                   // No. of similar bits
byte answer;                                       // Game answer
byte num = 0;                                      // Guess



void setup() {

  // ----------------------------- RANDOM ------------------------------
  
  randomSeed(analogRead(A5));                      // A5 must be disconnected
  answer = random(0,256);

  // ---------------------------- BUTTONS ------------------------------
  
  pinMode(BUTTON_BIT_1, INPUT);
  pinMode(BUTTON_BIT_2, INPUT);
  pinMode(BUTTON_BIT_3, INPUT);
  pinMode(BUTTON_BIT_4, INPUT);
  pinMode(BUTTON_BIT_5, INPUT);
  pinMode(BUTTON_BIT_6, INPUT);
  pinMode(BUTTON_BIT_7, INPUT);
  pinMode(BUTTON_BIT_8, INPUT);

  // ------------------------- SHIFT REGISTER --------------------------

  pinMode(SER, OUTPUT);
  pinMode(CLK, OUTPUT);
  pinMode(LATCH, OUTPUT);

  // ------------------------------ LEDS -------------------------------

  pinMode(LOW_LED, OUTPUT);
  pinMode(MEDIUM_LED, OUTPUT);
  pinMode(HIGH_LED, OUTPUT);
  pinMode(VICTORY_LED, OUTPUT);
}



void loop() {
  state1 = changeState(BUTTON_BIT_1, state1);     // BIT 1
  state2 = changeState(BUTTON_BIT_2, state2);     // BIT 2
  state3 = changeState(BUTTON_BIT_3, state3);     // BIT 3
  state4 = changeState(BUTTON_BIT_4, state4);     // BIT 4
  state5 = changeState(BUTTON_BIT_5, state5);     // BIT 5
  state6 = changeState(BUTTON_BIT_6, state6);     // BIT 6
  state7 = changeState(BUTTON_BIT_7, state7);     // BIT 7
  state8 = changeState(BUTTON_BIT_8, state8);     // BIT 8
  

  num = 128 * state1 + 64 * state2 + 32 * state3 + 16 * state4 + 8 * state5 + 4 * state6 + 2 * state7 + 1 * state8; // Calculate input


  digitalWrite(SER, LOW);                         // Restart SERIAL pin
  digitalWrite(CLK, LOW);                         // Restart CLOCK pin
  digitalWrite(LATCH, LOW);                       // Enable LED writing
  
  shiftOut(SER, CLK, LSBFIRST, num);              // Register NUM to LEDs
  
  digitalWrite(LATCH, HIGH);                      // Display written LEDs
  

  similarity = getSimilarity(answer, num);        // Calculate similarity between ANSWER and GUESS


  if (similarity <= 3) {
    ledSignal(1, 0, 0, 0);                        // LOW SIMILARITY
  }
  else if (similarity <= 5) {
    ledSignal(0, 1, 0, 0);                        // MEDIUM SIMILARITY
  }
  else if (similarity <= 7) {
    ledSignal(0, 0, 1, 0);                        // HIGH SIMILARITY
  }
  else {
    ledSignal(0, 0, 0, 1);                        // VICTORY
  }
}



// Debounce and read button
byte debounceButton(byte button) {
  if (digitalRead(button)) {
    delayMicroseconds(20);
    return digitalRead(button);
  }

  return 0;
}


// Change LED state
byte changeState(byte button, byte state) {
  if (debounceButton(button)) {
    state = not state;
    while (digitalRead(button));
  }

  return state;
}


// Get # of similar bits between ANSWER and GUESS
byte getSimilarity(byte answer, byte guess) {
  byte similarBits = 0;

  for (byte i = 0; i < 8; i++) {
    if (bitRead(answer, i) == bitRead(guess, i)) {
      similarBits += 1;
    }
  }

  return similarBits;
}


// Control similarity level LEDs
void ledSignal(int low, int med, int high, int vic) {
  digitalWrite(LOW_LED, low);
  digitalWrite(MEDIUM_LED, med);
  digitalWrite(HIGH_LED, high);
  digitalWrite(VICTORY_LED, vic);
}
