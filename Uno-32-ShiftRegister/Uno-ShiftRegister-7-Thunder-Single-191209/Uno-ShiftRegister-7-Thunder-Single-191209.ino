
#define DataPin 5
#define LatchPin 4
#define ClockPin 3

void setup() {
      pinMode(DataPin, OUTPUT);
      pinMode(LatchPin, OUTPUT);
      pinMode(ClockPin, OUTPUT);
}

void loop() {
      uint8_t number;

      for (int i = 0; i < 8; i++) {
            digitalWrite(LatchPin, LOW);

            number = 0;
            bitSet(number, i);

            shiftOut(DataPin, ClockPin, MSBFIRST, number);

            digitalWrite(LatchPin, HIGH);
            delay(300);
      }

      for (int i = 0; i < 8; i++) {
            digitalWrite(LatchPin, LOW);

            number = 0;
            bitSet(number, i);

            shiftOut(DataPin, ClockPin, LSBFIRST, number);

            digitalWrite(LatchPin, HIGH);
            delay(300);
      }
}
