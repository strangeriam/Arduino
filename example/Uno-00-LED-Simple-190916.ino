const int pinLED_red = 13;


void setup ()
{
	Serial.begin(115200);
	pinMode(pinLED_red, OUTPUT);
}

void blinkLED_red () {
	for (int i=1; i<=30; i++) {
			digitalWrite(pinLED_red, HIGH);
			delay(100);
			digitalWrite(pinLED_red, LOW);
			delay(100);
	}

	delay(2000);
}

void loop()
{
	Serial.println("AAA");
	blinkLED_red();
	delay(1000);
}
