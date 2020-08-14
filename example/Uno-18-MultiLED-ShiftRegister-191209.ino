
#define SysLedPin 13

#define DS_DataPin 5
#define STCP_LatchPin 4
#define SHCP_ClockPin 3

//#define MR_ResetPin 7

void setup() {
		Serial.begin(9600);

		pinMode(SysLedPin, OUTPUT);
		digitalWrite(SysLedPin, HIGH);

		pinMode(DS_DataPin, OUTPUT);
		pinMode(STCP_LatchPin, OUTPUT);
		pinMode(SHCP_ClockPin, OUTPUT);
		//pinMode(MR_ResetPin, OUTPUT);

		Serial.println("ShiftRegister + MultiLEDs");
}

void loop() {
			while (Serial.available() == 0);
			int valKey = Serial.read();

			if(valKey == 72) {
						Serial.println("KEY W-72 HELP.");
						helpPrint();

			} else if(valKey == 88) {
						Serial.println("KEY X-88 MR RESET (N/A).");
/*						digitalWrite(MR_ResetPin, LOW);

						digitalWrite(STCP_LatchPin, HIGH);
						delay(500);
						digitalWrite(STCP_LatchPin, LOW);*/
			} else {
						digitalWrite(STCP_LatchPin, LOW);
						switch (valKey) {

								case '0':
											Serial.println("--> Zero.");
											break;
								case '1':
											Serial.println("--> Light LED 1");
								        	shiftOut(DS_DataPin, SHCP_ClockPin, MSBFIRST, B00000000);
								        	shiftOut(DS_DataPin, SHCP_ClockPin, MSBFIRST, B00000001);
											break;
								case '2':
											Serial.println("--> Light LED 2");
								        	shiftOut(DS_DataPin, SHCP_ClockPin, MSBFIRST, B00000000);
								        	shiftOut(DS_DataPin, SHCP_ClockPin, MSBFIRST, B00000010);
											break;
								case '3':
											Serial.println("--> Light LED 3");
								        	shiftOut(DS_DataPin, SHCP_ClockPin, MSBFIRST, B00000000);
								        	shiftOut(DS_DataPin, SHCP_ClockPin, MSBFIRST, B00000100);
											break;
								case '4':
											Serial.println("--> Light LED 4");
								        	shiftOut(DS_DataPin, SHCP_ClockPin, MSBFIRST, B00000000);
								        	shiftOut(DS_DataPin, SHCP_ClockPin, MSBFIRST, B00001000);
											break;
								case '5':
											Serial.println("--> Light LED 5");
								        	shiftOut(DS_DataPin, SHCP_ClockPin, MSBFIRST, B00000000);
								        	shiftOut(DS_DataPin, SHCP_ClockPin, MSBFIRST, B00010000);
											break;
								case '6':
											Serial.println("--> Light LED 6");
								        	shiftOut(DS_DataPin, SHCP_ClockPin, MSBFIRST, B00000000);
								        	shiftOut(DS_DataPin, SHCP_ClockPin, MSBFIRST, B00100000);
											break;
								case '7':
											Serial.println("--> Light LED 7");
								        	shiftOut(DS_DataPin, SHCP_ClockPin, MSBFIRST, B00000000);
								        	shiftOut(DS_DataPin, SHCP_ClockPin, MSBFIRST, B01000000);
											break;
								case '8':
											Serial.println("--> Light LED 8");
								        	shiftOut(DS_DataPin, SHCP_ClockPin, MSBFIRST, B00000000);
								        	shiftOut(DS_DataPin, SHCP_ClockPin, MSBFIRST, B10000000);
											break;
								case '9':
											Serial.println("--> Light LED 9");
								        	shiftOut(DS_DataPin, SHCP_ClockPin, MSBFIRST, B00000001);
								        	shiftOut(DS_DataPin, SHCP_ClockPin, MSBFIRST, B00000000);
											break;
								case 'A':
											Serial.println("--> Light LED 10");
								        	shiftOut(DS_DataPin, SHCP_ClockPin, MSBFIRST, B00000010);
								        	shiftOut(DS_DataPin, SHCP_ClockPin, MSBFIRST, B00000000);
											break;
								case 'B':
											Serial.println("--> Light LED 11");
								        	shiftOut(DS_DataPin, SHCP_ClockPin, MSBFIRST, B00000100);
								        	shiftOut(DS_DataPin, SHCP_ClockPin, MSBFIRST, B00000000);
											break;
								case 'C':
/*											Serial.println("--> RGB Sensor 1");
								        	shiftOut(DS_DataPin, SHCP_ClockPin, MSBFIRST, B00110000);
								        	shiftOut(DS_DataPin, SHCP_ClockPin, MSBFIRST, B11000011);
											break;*/
								default:
											//Serial.print("SHIFT REGISTER + MULTI LEDs");
											Serial.println(" ('H' get HELP).");
											// Turn off all LEDs.
											shiftOut(DS_DataPin, SHCP_ClockPin, MSBFIRST, B00000000);
											shiftOut(DS_DataPin, SHCP_ClockPin, MSBFIRST, B00000000);
											break;
						}

						digitalWrite(STCP_LatchPin, HIGH);
			}
}


//===============================================================
void helpPrint() {

		Serial.println("\n==== HELP ===================================");
		Serial.println("'0': MR RESET");
		Serial.println("'1': RGB try LED 1");
		Serial.println("'2': RGB try LED 2");
		Serial.println("'3': RGB try LED 3");
		Serial.println("'4': RGB try LED 4");
		Serial.println("'5': RGB try LED 5");
		Serial.println("'6': RGB try LED 6");
		Serial.println("'7': RGB try LED 7");
		Serial.println("'8': RGB try LED 8");
		Serial.println("'9': RGB try LED 9");
		Serial.println("'A': RGB try LED 10");
		Serial.println("'B': RGB try LED 11");
		//Serial.println("'C': RGB Sensor 1");
}


