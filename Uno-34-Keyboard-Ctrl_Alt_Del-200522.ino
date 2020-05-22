/*
Button for Keyboard (Arduino Leonardo only)

The circuit:
 * LED attached to pin 13.
 * pushbutton attached to pin 2.
*/

#include "Keyboard.h"

const char ctrlKey = KEY_LEFT_CTRL;
const char altKey = KEY_LEFT_ALT;
const char delKey = KEY_DELETE;

// variables will change:
// variable for reading the pushbutton status
int buttonState = 0;

void setup() {
      pinMode(13, OUTPUT);

      pinMode(2, INPUT);
      digitalWrite(2, HIGH);

      Keyboard.begin();
}

void loop(){
      // read the state of the pushbutton value:
      buttonState = digitalRead(2);

      // check if the pushbutton is pressed.
      // if it is, the buttonState is HIGH:
      if (buttonState == LOW) {
                  digitalWrite(13, HIGH);
                  delay(30);

                  while(buttonState == LOW){
                        buttonState = digitalRead(2);
                        Keyboard.press(ctrlKey);
                        Keyboard.press(altKey);
                        Keyboard.press(delKey);
                  }
      } else {
                  // turn LED off:
                  digitalWrite(13, LOW);
                  Keyboard.releaseAll();
      }

      delay(100);
}
