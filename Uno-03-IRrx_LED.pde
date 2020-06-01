#include <IRremote.h>

const int irReceiverPin = 2;
const int ledPin        = 13;

IRrecv irrecv(irReceiverPin);
decode_results results;

void setup()
{
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  irrecv.enableIRIn();
}

void blinkLED() {
	for (int i=1; i<=2; i++) {
		digitalWrite(ledPin, HIGH);
		delay(100);
		digitalWrite(ledPin, LOW);
		delay(100);
	}
}

void loop()
{
  if (irrecv.decode(&results)) {
    Serial.print("irCode: ");
    Serial.print(results.value, HEX);
    Serial.print(",  bits: ");
    Serial.println(results.bits);
    blinkLED();
    irrecv.resume();
  }
}
