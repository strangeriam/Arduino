#include <Wire.h>

/*
Keyboard key reserved:
Q[81] W[87] E[69] R[82] T[84] Y[89] U[85]
A[65] S[83]
*/

const int pinLED1 = 13;

const int pinRelay1 = 2;
const int pinRelay2 = 3;
const int pinRelay3 = 4;

void keyPrint() {
	Serial.println(" ");
	Serial.println("Keyboard key mapping");
	Serial.print("W, Only Relay 1 LOW_SHORT.");
	Serial.print("E, Only Relay 2 LOW_SHORT.");

	Serial.println("R,");
	Serial.println("	Step-1: Relay 3 LOW_SHORT..");
	Serial.println("	Step-2: Relay 2 LOW_SHORT..");
	Serial.println("	Step-3: Wait 6s, then Relay 3 HIGH_OPEN..");

	Serial.println("A, Relay 3 LOW_SHORT");
	Serial.println("S, Relay 3 HIGH_OPEN");
	Serial.println("Q, ALL HIGH_OPEN");
    Serial.println(" ");
}

void blinkLED() {
	for (int i=1; i<=3; i++) {
			digitalWrite(pinLED1, HIGH);
			delay(100);
			digitalWrite(pinLED1, LOW);
			delay(100);
	}

	delay(500);
}

void allRelayOpen() {
	Serial.println("Relay Go: Keep all Relays OPEN.");
	digitalWrite(pinRelay1, HIGH);
	digitalWrite(pinRelay2, HIGH);
	digitalWrite(pinRelay3, HIGH);
	delay(100);
}


void setup(void)
{
	Serial.begin(9600);
	Serial.println("Uno, Relay Go Ver: 20190919a");

	pinMode(pinLED1, OUTPUT);

	pinMode(pinRelay1, OUTPUT);
	pinMode(pinRelay2, OUTPUT);
	pinMode(pinRelay3, OUTPUT);

	digitalWrite(pinRelay1, HIGH);
	digitalWrite(pinRelay2, HIGH);
	digitalWrite(pinRelay3, HIGH);

	keyPrint();
	Serial.println("Relay Go Ready Yet.");
}

void loop() {

     while (Serial.available() == 0);
     int valKey = Serial.read();

     // Relay 1
	 if (valKey == 87) {
			allRelayOpen();
			Serial.println(" ");
	 		Serial.println("KEY W-87 DC12V.");
			Serial.println("	Step-1: All Relays HIGH_OPEN..");
			Serial.println("	Step-2: Relay 1 LOW_SHORT..");

			digitalWrite(pinRelay1, LOW);

     // Relay 2
	 } else if (valKey == 69) {
			allRelayOpen();
			Serial.println(" ");
	 		Serial.println("KEY E-69 PoE.");
			Serial.println("	Step-1: All Relays HIGH_OPEN..");
			Serial.println("	Step-2: Relay 2 LOW_SHORT..");

			digitalWrite(pinRelay2, LOW);

     // Relay 3
	 } else if (valKey == 82) {
			allRelayOpen();
			Serial.println(" ");
	 		Serial.println("KEY R-82 Heater.");
			Serial.println("	Step-1: All Relays HIGH_OPEN..");
			Serial.println("	Step-2: Relay 3 LOW_SHORT..");
			Serial.println("	Step-3: Relay 2 LOW_SHORT..");
			Serial.println("	Step-4: Wait 7s..");
			Serial.println("	Step-5: Relay 3 HIGH_OPEN..");

			digitalWrite(pinLED1, HIGH); // LED ON

			digitalWrite(pinRelay3, LOW);
			delay(100);
			digitalWrite(pinRelay2, LOW);
			delay(7000);
			digitalWrite(pinRelay3, HIGH);

			digitalWrite(pinLED1, LOW); // LED OFF

     // Relay 3
	 } else if (valKey == 65) {
	 		Serial.println("KEY A-65 Heater Short.");
			Serial.println("	Step-1: KEEP Relay 3 LOW_SHORT..");
			digitalWrite(pinRelay3, LOW);
			digitalWrite(pinLED1, HIGH); // LED ON

     // Relay 3
	 } else if (valKey == 83) {
	 		Serial.println("KEY S-83 Heater Open.");
			Serial.println("	Step-1: KEEP Relay 3 HIGH_OPEN..");
			digitalWrite(pinRelay3, HIGH);
			digitalWrite(pinLED1, LOW); // LED OFF

	 // =================================
	 } else if (valKey == 81) {
	 		Serial.println("KEY Q-81.");
			allRelayOpen();

	 } else {
	 		Serial.println("Relay Go: Not thing...");
			blinkLED();
	 		keyPrint();
	 }

     Serial.println(" ");
}

