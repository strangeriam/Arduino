
int pinLED_system = 13;

//Pin connected to ST_CP of 74HC595
int latchPin = 4;
//Pin connected to SH_CP of 74HC595
int clockPin = 3;
////Pin connected to DS of 74HC595
int dataPin = 5;

void setup() {
      pinMode(pinLED_system, OUTPUT);
      digitalWrite(pinLED_system, HIGH);

      //Start Serial for debuging purposes
      Serial.begin(115200);

      //set pins to output because they are addressed in the main loop
      pinMode(latchPin, OUTPUT);
}

void loop() {
      //count up routine
      for (int j = 0; j < 256; j++) {
          //ground latchPin and hold low for as long as you are transmitting
          digitalWrite(latchPin, 0);

          //count up on GREEN LEDs
          shiftOut(dataPin, clockPin, j);

          //count down on RED LEDs
          shiftOut(dataPin, clockPin, 255-j);

          //return the latch pin high to signal chip that it no longer needs to listen for information
          digitalWrite(latchPin, 1);
          delay(1000);
      }
}

void shiftOut(int myDataPin, int myClockPin, byte myDataOut) {
      // This shifts 8 bits out MSB first, on the rising edge of the clock, clock idles low internal function setup
      int i=0;
      int pinState;
      pinMode(myClockPin, OUTPUT);
      pinMode(myDataPin, OUTPUT);

      //clear everything out just in case to prepare shift register for bit shifting
      digitalWrite(myDataPin, 0);
      digitalWrite(myClockPin, 0);

      //for each bit in the byte myDataOut
      //NOTICE THAT WE ARE COUNTING DOWN in our for loop
      //This means that %00000001 or "1" will go through such that it will be pin Q0 that lights.
      for (i=7; i>=0; i--)  {
            digitalWrite(myClockPin, 0);

            //if the value passed to myDataOut and a bitmask result true then... so if we are at i=6 and our value is
            // %11010100 it would the code compares it to %01000000 and proceeds to set pinState to 1.
            if ( myDataOut & (1<<i) ) {
                    pinState= 1;
            } else {
                    pinState= 0;
            }

            //Sets the pin to HIGH or LOW depending on pinState
            digitalWrite(myDataPin, pinState);

            //register shifts bits on upstroke of clock pin
            digitalWrite(myClockPin, 1);

            //zero the data pin after shift to prevent bleed through
            digitalWrite(myDataPin, 0);
      }

      //stop shifting
      digitalWrite(myClockPin, 0);
}