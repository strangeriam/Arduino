#include <TimerOne.h>

#define SysLedPin 13

#define DS_DataPin 5
#define STCP_LatchPin 4
#define SHCP_ClockPin 3
#define MR_ResetPin 7



//=== RGB ==========================================================
#define TCS3200_OUT 2


int g_count = 0;
int g_array[3];
int g_flag = 0;
float g_SF[3];

// (S0, 0000 0010) (S1, 0000 0100)
// (S2, 0000 1000) (S3, 0001 0000)

// OUTPUT Frequency Scaling. (S0,S1)
// Configure Freq Scale to 2 % (---- -10-).

// Photodiode Type. (S2,S3)
// RED (---0 0---)
void TSC_FilterColor_Red() {
		Serial.println("--> Get Color Red.");

		g_count = 0;
		g_flag ++;

		digitalWrite(STCP_LatchPin, LOW);
		shiftOut(DS_DataPin, SHCP_ClockPin, MSBFIRST, B00000101);
		digitalWrite(STCP_LatchPin, HIGH);

		Timer1.setPeriod(1000000);
}

// GREEN (---1 1---)
void TSC_FilterColor_Green() {
		Serial.println("--> Get Color Green.");

		g_count = 0;
		g_flag ++;

		digitalWrite(STCP_LatchPin, LOW);
		shiftOut(DS_DataPin, SHCP_ClockPin, MSBFIRST, B00011101);
		digitalWrite(STCP_LatchPin, HIGH);

		Timer1.setPeriod(1000000);
}

// BLUE (---1 0---)
void TSC_FilterColor_Blue() {
		Serial.println("--> Get Color Blue.");

		g_count = 0;
		g_flag ++;

		digitalWrite(STCP_LatchPin, LOW);
		shiftOut(DS_DataPin, SHCP_ClockPin, MSBFIRST, B00010101);
		digitalWrite(STCP_LatchPin, HIGH);

		Timer1.setPeriod(1000000);
}

// CLEAR (---0 1---)
void TSC_FilterColor_Clear() {
		Serial.println("--> Get Color Clear.");

		g_count = 0;
		g_flag ++;

		digitalWrite(STCP_LatchPin, LOW);
		shiftOut(DS_DataPin, SHCP_ClockPin, MSBFIRST, B00001101);
		digitalWrite(STCP_LatchPin, HIGH);

		Timer1.setPeriod(1000000);
}

void TSC_Count() {
		g_count ++;
}

void TSC_Callback() {
	  switch(g_flag) {
		    case 0:
		    Serial.println("->WB Start");
		    TSC_FilterColor_Red();
		    break;

		    case 1:
		    Serial.print("->Frequency R=");
		    Serial.println(g_count);
		    g_array[0] = g_count;
		    TSC_FilterColor_Green();
		    break;

		    case 2:
		    Serial.print("->Frequency G=");
		    Serial.println(g_count);
		    g_array[1] = g_count;
		    TSC_FilterColor_Clear();
		    break;

		    case 3:
		    Serial.print("->Frequency B=");
		    Serial.println(g_count);
		    Serial.println("->WB End");
		    g_array[2] = g_count;
		    TSC_FilterColor_Blue();
		    break;

		    default:
		    g_count = 0;
		    break;
	  }
}



void setup() {
		Serial.begin(9600);

		pinMode(SysLedPin, OUTPUT);
		digitalWrite(SysLedPin, HIGH);

		Serial.println("ShiftRegister +MultiLEDs (Lu191217.0925)");

		// === 74HC595  =============================
		pinMode(DS_DataPin, OUTPUT);
		pinMode(STCP_LatchPin, OUTPUT);
		pinMode(SHCP_ClockPin, OUTPUT);
		pinMode(MR_ResetPin, OUTPUT);
		delay(500);

		// Set MR pin HIGH to active Q0~Q7.
		digitalWrite(MR_ResetPin, HIGH);

		// Turn on LED 1
		digitalWrite(STCP_LatchPin, LOW);
		shiftOut(DS_DataPin, SHCP_ClockPin, MSBFIRST, B00000001);
		digitalWrite(STCP_LatchPin, HIGH);

		// === RGB ==================================
		pinMode(TCS3200_OUT, INPUT);
		Timer1.initialize();
		//Timer1.attachInterrupt( TSC_Callback );

/*		attachInterrupt(0, TSC_Count, RISING);
		delay(4000);

		for(int i=0; i<3; i++) {
			Serial.print( "g_array: ");
			Serial.println(g_array[i]);
		}

		g_SF[0] = 255.0/ g_array[0];
		g_SF[1] = 255.0/ g_array[1];
		g_SF[2] = 255.0/ g_array[2];

		Serial.print( "g_SF 0: ");
		Serial.println( g_SF[0]);

		Serial.print( "g_SF 1: ");
		Serial.println( g_SF[1]);

		Serial.print( "g_SF 2: ");
		Serial.println( g_SF[2]);*/
}

void loop() {
			while (Serial.available() == 0);
			int valKey = Serial.read();

			if(valKey == 72) {
						Serial.println("KEY W-72.");

			} else if(valKey == 90) {
						Serial.println("KEY Z-90 RGB Try Try look.");

						Timer1.attachInterrupt( TSC_Callback );

						attachInterrupt(0, TSC_Count, RISING);
						delay(4000);

						for(int i=0; i<3; i++) {
							Serial.print( "g_array: ");
							Serial.println(g_array[i]);
						}

						g_SF[0] = 255.0/ g_array[0];
						g_SF[1] = 255.0/ g_array[1];
						g_SF[2] = 255.0/ g_array[2];

						Serial.print( "g_SF 0: ");
						Serial.println( g_SF[0]);

						Serial.print( "g_SF 1: ");
						Serial.println( g_SF[1]);

						Serial.print( "g_SF 2: ");
						Serial.println( g_SF[2]);

			} else if(valKey == 88) {
						Serial.println("KEY X-88 RGB Value.");

						g_flag = 0;

						for(int i=0; i<3; i++)
							Serial.println(int(g_array[i] * g_SF[i]));
						//delay(4000);
			} else {
					switch (valKey) {

							case '0':
										Serial.println("--> KEY 0 MR RESET.");
										digitalWrite(MR_ResetPin, LOW);
										delay(500);

										digitalWrite(STCP_LatchPin, LOW);
										digitalWrite(STCP_LatchPin, HIGH);

										digitalWrite(MR_ResetPin, HIGH);

										//Wait 1 second and turn on LED 1.
										delay(1000);
										digitalWrite(STCP_LatchPin, LOW);
										shiftOut(DS_DataPin, SHCP_ClockPin, MSBFIRST, B00000001);
										digitalWrite(STCP_LatchPin, HIGH);
										break;
							case '6':
										Serial.println("--> Q6 LED ON ");
										digitalWrite(STCP_LatchPin, LOW);
							        	shiftOut(DS_DataPin, SHCP_ClockPin, MSBFIRST, B00100001);
										digitalWrite(STCP_LatchPin, HIGH);
										break;
							case '7':
										Serial.println("--> Q7 LED ON");
										digitalWrite(STCP_LatchPin, LOW);
							        	shiftOut(DS_DataPin, SHCP_ClockPin, MSBFIRST, B01000001);
										digitalWrite(STCP_LatchPin, HIGH);
										break;
							case '8':
										Serial.println("--> Q8 LED ON");
										digitalWrite(STCP_LatchPin, LOW);
							        	shiftOut(DS_DataPin, SHCP_ClockPin, MSBFIRST, B10000001);
										digitalWrite(STCP_LatchPin, HIGH);
										break;
							default:
										Serial.println(" ('H' get HELP).");
										break;
						}
			}
}


//===============================================================
void helpPrint() {

		Serial.println("\n==== HELP ===================================");
		Serial.println("'0': MR RESET");
		Serial.println("'1': ");
		Serial.println("'2': ");
		Serial.println("'3': ");
		Serial.println("'4': ");
		Serial.println("'5': ");
		Serial.println("'6': Q6 LED ON, Green.");
		Serial.println("'7': Q7 LED ON, Green.");
		Serial.println("'8': Q8 LED ON, Green.");
		Serial.println("'9': ");
		Serial.println("'A': ");
		Serial.println("'B': ");
		Serial.println("'C': ");
		Serial.println("'X': RGB Value.");
		Serial.println("'H': Command HELP.");
}


