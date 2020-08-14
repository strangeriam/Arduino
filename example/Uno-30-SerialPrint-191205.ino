
int pinLED_system = 13;

// ==================================
void setup(){
	pinMode(pinLED_system, OUTPUT);
	digitalWrite(pinLED_system, HIGH);

	Serial.begin(9600);
}

void loop(){
	if(Serial.available()){
		Serial.println(Serial.read());
	}
}
