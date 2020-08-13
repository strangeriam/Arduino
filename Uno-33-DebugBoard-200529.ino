
#include <Wire.h>

const int pinLED_Red    = 13;
const int pinLED_Yellow = 12;
const int pinLED_Green  = 11;

const int pinRelay      = 10;
const int pinReset      = 9;



void blinkLED() {
    Serial.println("\nTryTryLu: RYG LED Blinking.");

    digitalWrite(pinLED_Red, LOW);
    digitalWrite(pinLED_Yellow, LOW);
    digitalWrite(pinLED_Green, LOW);

    for (int i=1; i<=3; i++) {
            digitalWrite(pinLED_Red, HIGH);
            delay(200);
            digitalWrite(pinLED_Red, LOW);

            digitalWrite(pinLED_Yellow, HIGH);
            delay(200);
            digitalWrite(pinLED_Yellow, LOW);

            digitalWrite(pinLED_Green, HIGH);
            delay(200);
            digitalWrite(pinLED_Green, LOW);
    }
}

void setup() {

        digitalWrite(pinReset, HIGH);
        digitalWrite(pinRelay, HIGH);

        Serial.begin(9600);
        Serial.println("USB RS232");

        pinMode(pinLED_Red,    OUTPUT);
        pinMode(pinLED_Yellow, OUTPUT);
        pinMode(pinLED_Green,  OUTPUT);
        pinMode(pinRelay,      OUTPUT);
        pinMode(pinReset,      OUTPUT);

        digitalWrite(pinLED_Yellow, HIGH);
}

void help() {
        Serial.println("=== Help ===");
        Serial.println("W-87, Reset.. pin 9.");
        Serial.println("E-69, LED blinking.. pin 11, 12 & 13.");
        Serial.println("R-82, Relay.. pin 10.");
        Serial.println("T-84, LED GREEN.. pin 11.");
        Serial.println("Y-89, LED YELLOW.. pin 12.");
        Serial.println("U-85, LED RED.. pin 13.");
        Serial.println("I-73, All LED Off...");
}

/*
Keyboard key reserved:
Q[81] W[87] E[69] R[82] T[84] Y[89] U[85] I[73] O[79] P[80]
A[65] S[83] D[68] F[70]
*/
void loop() {
         while (Serial.available() == 0);
         int valKey = Serial.read();

         if (valKey == 81) {
                Serial.println("\nTryTryLu: KEY Q-81.");

                help();

                Serial.println("\nTryTryLu: KEY Q-81 Done.");

         } else if (valKey == 87) {
                Serial.println("\nTryTryLu: KEY W-87.");
                Serial.println("W-87, Reset.. pin 9.");

                delay(200);
                digitalWrite(pinReset, LOW);

                Serial.println("\nTryTryLu: KEY W-87 Done.");

         } else if (valKey == 69) {
                Serial.println("\nTryTryLu: KEY E-69.");
                Serial.println("E-69, LED blinking.. pin 11, 12 & 13.");

                blinkLED();

                Serial.println("\nTryTryLu: KEY E-69 Done.");

         } else if (valKey == 82) {
                Serial.println("\nTryTryLu: KEY R-82.");
                Serial.println("R-82, Relay.. pin 10.");

                digitalWrite(pinRelay, LOW);
                delay(200);
                digitalWrite(pinRelay, HIGH);

                Serial.println("\nTryTryLu: KEY R-82 Done.");

         } else if (valKey == 84) {
                Serial.println("\nTryTryLu: KEY T-84.");
                digitalWrite(pinLED_Green, HIGH);
                Serial.println("\nTryTryLu: KEY T-84 Done.");

         } else if (valKey == 89) {
                Serial.println("\nTryTryLu: KEY Y-89.");
                digitalWrite(pinLED_Yellow, HIGH);
                Serial.println("\nTryTryLu: KEY Y-89 Done.");

         } else if (valKey == 85) {
                Serial.println("\nTryTryLu: KEY U-85.");
                digitalWrite(pinLED_Red, HIGH);
                Serial.println("\nTryTryLu: KEY U-85 Done.");

         } else if (valKey == 73) {
                Serial.println("\nTryTryLu: KEY I-73.");

                digitalWrite(pinLED_Red, LOW);
                digitalWrite(pinLED_Yellow, LOW);
                digitalWrite(pinLED_Green, LOW);

                Serial.println("\nTryTryLu: KEY I-73 Done.");
         }
}
