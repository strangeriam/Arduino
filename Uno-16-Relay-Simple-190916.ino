const int pinLED = 13;

const int relay1 = 2;
const int relay2 = 3;

void setup()
{
	pinMode(pinLED, OUTPUT);

	pinMode(relay1, OUTPUT);
	pinMode(relay2, OUTPUT);
}

void led13() {
	for (int i=1; i<=5; i++) {
		digitalWrite(pinLED, HIGH);
		delay(100);
		digitalWrite(pinLED, LOW);
		delay(100);
	}
	delay(1000);
}

void relay1_switch () {
}

void loop()
{
	digitalWrite(relay1, HIGH);
	digitalWrite(relay2, LOW);
	delay(1000);

	digitalWrite(relay1, LOW);
	digitalWrite(relay2, HIGH);
	delay(1000);

	led13();

}