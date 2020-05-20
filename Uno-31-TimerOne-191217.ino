#include <TimerOne.h>

void goLED_13() {
      digitalWrite( 13, digitalRead( 13 ) ^ 1 );
}

void setup() {
      pinMode(13, OUTPUT);

      Timer1.initialize();

      Timer1.attachInterrupt( goLED_13 );
}

void loop() {

}

