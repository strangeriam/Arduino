// 31 ~ 40 -->氣動控制 41 ~ 50 Sensor
//筆鋼 37,38;47,48
//微動開關 49

int ctl0=24,ctl1=25,ctl2=26,ctl3=27,ctl4=28;
//int ctl0=25,ctl1=24,ctl2=26,ctl3=27,ctl4=28;
int detect1=6; //23
int detect2=7; //24
int ctlswRJ=23;
int sensor1=29;
int sensor2=30;
int DCctl=22;
int val,val1,val2,s41,s42,s43,s44,s45,s46;
int testcount,passcount;
int YellowButton=9;
int GreenButton=10;
int greencount=0;
int yellowcount=0;
int debug=0;
int RedLight=51,YellowLight=52,GreenLight=53;
int DetectBoardLED=8;
int AcPin=21;
int OapReset=47;
///////////////////////////////////////////////
// 接 74HC595 的 ST_CP (ic pin 12,pcb pin 4)
int latchPin = 3;
// 接 74HC595 的 SH_CP (ic pin 11,pcb pin 3)
int clockPin = 4;
// 接 74HC595 的 DS (ic pin 14,pcb pin 2)
int dataPin = 5;
// OUT1 (TCS3200 pin 6 , PCB pin 5)
// GND (PCB pin 6)
// VCC (PCB pin 1)
int flag=0;
int counter=0;
int countR=0,countG=0,countB=0;
int ledsensor=0;
byte ledsensor2;
byte ledsensor1;
///////////////////////////////////////////////
void setup()
{
	Serial.begin(115200);
	pinMode(RedLight,OUTPUT);
	pinMode(YellowLight,OUTPUT);
	pinMode(GreenLight,OUTPUT);
	digitalWrite(RedLight,HIGH);
	digitalWrite(YellowLight,LOW);
	digitalWrite(GreenLight,HIGH);
	pinMode(DetectBoardLED,OUTPUT);
	pinMode(AcPin,OUTPUT);
	digitalWrite(AcPin,HIGH);
	pinMode(ctl0,OUTPUT);
	pinMode(ctl1,OUTPUT);
	pinMode(ctl2,OUTPUT);
	pinMode(ctl3,OUTPUT);
	pinMode(ctl4,OUTPUT);
	pinMode(ctlswRJ,OUTPUT);
	pinMode(DCctl,OUTPUT);
	digitalWrite(ctl0,LOW);
	digitalWrite(ctl1,LOW);
	digitalWrite(ctl2,LOW);
	digitalWrite(ctl3,LOW);
	digitalWrite(ctl4,LOW);
	digitalWrite(ctlswRJ,LOW);
	digitalWrite(DCctl,LOW);
	pinMode(sensor1,INPUT);
	pinMode(sensor2,INPUT);	
	pinMode(YellowButton,OUTPUT);
	pinMode(GreenButton,OUTPUT);
	digitalWrite(YellowButton,HIGH);
	digitalWrite(GreenButton,HIGH);
	pinMode(YellowButton,INPUT);
	pinMode(GreenButton,INPUT);
    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(dataPin, OUTPUT);

	pinMode(31,OUTPUT);
	pinMode(32,OUTPUT);
	pinMode(33,OUTPUT);
	pinMode(34,OUTPUT);
	pinMode(35,OUTPUT);
	pinMode(36,OUTPUT);	
	pinMode(41,INPUT);
	pinMode(42,INPUT);
	pinMode(43,INPUT);
	pinMode(44,INPUT);	
	pinMode(45,INPUT);
	pinMode(46,INPUT);		
	
	pinMode(detect1,INPUT);		
	pinMode(detect2,INPUT);	
	pinMode(OapReset,OUTPUT);
	digitalWrite(OapReset,LOW);
}


void TCS()
{
	digitalWrite(latchPin, LOW);
	ledsensor2 = B00010000 | ledsensor1;
	shiftOut(dataPin, clockPin, MSBFIRST, ledsensor2); //second chip	
	shiftOut(dataPin, clockPin, MSBFIRST, ledsensor); //first chip
	digitalWrite(latchPin, HIGH);
	delay(2);
	flag=0;
	attachInterrupt(0, ISR_INTO, CHANGE);
	timer2_init();
}

void ISR_INTO()
{
	counter++;
}

void timer2_init(void)
{
	TCCR2A=0x00;
	TCCR2B=0x07; //the clock frequency source 1024 points
	TCNT2= 100;    //10 ms overflow again
	TIMSK2 = 0x01; //allow interrupt
}

ISR(TIMER2_OVF_vect)//the timer 2, 10ms interrupt overflow again. Internal overflow interrupt executive function
{
	TCNT2=100;
	flag++;
	if(flag==1)
	{
		counter=0;
	}
	else if(flag==2)
	{	
	
		digitalWrite(latchPin, LOW);
		ledsensor2 = B00010000 | ledsensor1;
		shiftOut(dataPin, clockPin, MSBFIRST, ledsensor2); //second chip
		shiftOut(dataPin, clockPin, MSBFIRST, ledsensor); //first chip
		digitalWrite(latchPin, HIGH);
		countR=counter/1.051;
		Serial.print("red=");
		Serial.println(countR,DEC); 
		digitalWrite(latchPin, LOW);
		ledsensor2 = B11010000 | ledsensor1;
		shiftOut(dataPin, clockPin, MSBFIRST, ledsensor2); 
		shiftOut(dataPin, clockPin, MSBFIRST, ledsensor); 
		digitalWrite(latchPin, HIGH);			
	}
	else if(flag==3)
	{	
	
		countG=counter/1.0157;
		Serial.print("green=");
		Serial.println(countG,DEC);
		digitalWrite(latchPin, LOW);
		ledsensor2 = B10010000 | ledsensor1;
		shiftOut(dataPin, clockPin, MSBFIRST, ledsensor2); 
		shiftOut(dataPin, clockPin, MSBFIRST, ledsensor); 
		digitalWrite(latchPin, HIGH);
	}
	else if(flag==4)
	{	
		countB=counter/1.114;
		Serial.print("blue=");
		Serial.println(countB,DEC);
		digitalWrite(latchPin, LOW);
		ledsensor2 = B00010000 | ledsensor1;
		shiftOut(dataPin, clockPin, MSBFIRST, ledsensor2); 
		shiftOut(dataPin, clockPin, MSBFIRST, ledsensor); 
		digitalWrite(latchPin, HIGH);
	}
	else
	{
		flag=0; 
		TIMSK2 = 0x00;
	}
	counter=0;
	delay(2);
}

void loop()
{
	val=digitalRead(YellowButton);
	if ( val == 0 ) {
		val1=digitalRead(detect1);
		val2=digitalRead(detect2);
		yellowcount++;
		//Serial.println(yellowcount);
		//增加累計超過幾秒才動作
		Serial.println("Press Yellow Button");
	} else {
		if ( yellowcount > 400 ) {
			s41 = digitalRead(41);
			s42 = digitalRead(42);
			s43 = digitalRead(43);
			s44 = digitalRead(44);
			if ( (s41 == 0) && (s42== 1) && (s43 == 0) && (s44== 1)) {
				ExportDUT();
				yellowcount=0;
			} else if ( (s41 == 1) && (s42== 0) && (s43 == 1) && (s44== 0) ) {
				InsertDUT();
				yellowcount=0;
			} else if ( (s41 == 1) && (s42== 1) && (s43 == 0) && (s44== 1) ) {
				InsertDUT1(); // Sensor 都沒到位的處理					
			} else if ( (s41 == 1) && (s42== 0) && (s43 == 1) && (s44== 1) ) {
				InsertDUT1(); // Sensor 都沒到位的處理				
			} else if ( (s41 == 1) && (s42== 1) && (s43 == 1) && (s44== 1) ) {
				InsertDUT1(); // Sensor 都沒到位的處理
			} else {
				ExportDUT();
				yellowcount=0;
			}
		}	
		yellowcount=0;
	}
	val=digitalRead(GreenButton);
	if ( val == 0 ) {
		s41 = digitalRead(41);
		s42 = digitalRead(42);
		s43 = digitalRead(43);
		s44 = digitalRead(44);	
		if ( (s41 == 1) && (s42== 0) && (s43 == 1) && (s44== 0) ) {
			digitalWrite(DetectBoardLED,HIGH);
		}
		val1=digitalRead(detect1);
		val2=digitalRead(detect2);
		if ( (val1 == 0) && (val2 == 0) ) {
			greencount++;
			//Serial.println(greencount);
			Serial.println("Press Green Button");
		} else {
			greencount=0;
		}
		digitalWrite(DetectBoardLED,LOW);
	} else {
		if ( (val1 == 0) && (val2 == 0) ) {
			if ( greencount > 100 ) {
				s41 = digitalRead(41);
				s42 = digitalRead(42);
				s43 = digitalRead(43);
				s44 = digitalRead(44);
				if ( (s41 == 0) && (s42== 1) && (s43 == 0) && (s44== 1)) {
					ExportDUT();
					greencount=0;
				} else if ( (s41 == 1) && (s42== 0) && (s43 == 1) && (s44== 0) ) {
					InsertDUT();
					greencount=0;
				} else if ( (s41 == 1) && (s42== 1) && (s43 == 1) && (s44== 1) ) {			
				} else {
					ExportDUT();
					greencount=0;
				}
			}		
		}
		greencount=0;
	}
  if (Serial.available() > 0) {
    // 讀取進來的 byte
    int inByte = Serial.read();  
    switch (inByte) {
    case 'H':
		Serial.println("'0': Switch to NONE");
		Serial.println("'1': Switch to Cable A");
		Serial.println("'2': Switch to Cable B");
		Serial.println("'3': Switch to Cable C");
		Serial.println("'4': Switch to Cable D");
		Serial.println("'5': Test LED 5");
		Serial.println("'6': Test LED 1");
		Serial.println("'7': Test LED 2");
		Serial.println("'8': Test LED 3");
		Serial.println("'9': Test LED 4");
		Serial.println("'I': Get Insert Status");
		Serial.println("'E': Get Export Status");
		//Serial.println("'i': Insert Dut (Debug Only)");
		//Serial.println("'o': Export Dut (Debug Only)");
		Serial.println("'y': Get Yellow Button Status");
		Serial.println("'g': Get Green Button Status");
		Serial.println("'V': Get Solenoid Valve Sensor Status");
		Serial.println("'R': Switch to RJ 1");
		Serial.println("'r': Switch to RJ 2");
		Serial.println("'D': Turn On DC");
		Serial.println("'d': Turn Off DC");
		Serial.println("'a': PWC Test with Sensor 2");
		Serial.println("'A': PWC Test with Sensor 1/2");
		Serial.println("'C': AC ON");
		Serial.println("'c': AC OFF");
		Serial.println("'B': Turn On Detect Board LED");
		Serial.println("'b': Turn Off Detect Board LED");
		Serial.println("'m': Get Detect Board Status");
		Serial.println("'!': Turn On Red Light");
		Serial.println("'@': Turn On Yellow Light");
		Serial.println("'#': Turn On Green Light");
		Serial.println("'s': Get PoE Sensor Status");
		Serial.println("'u': Press Button");
		Serial.println("'U': Press Button for Wookie");
		Serial.println("'~': Run ~");
		Serial.println("'f' = Solenoid Off Power.");
		Serial.println("Bigfoot Automatic fixuture V1.50, build date 2016/05/25");
		Serial.println("Powered by Alan #3292 , Jeff #2898 , Kent #2137");		
		Serial.println("#"); 
		break;		
    case 'u':
		Serial.println("Press Button");
		digitalWrite(35, LOW);
		digitalWrite(36, HIGH);
		delay(100);
		digitalWrite(35, HIGH);
		digitalWrite(36, LOW);
		delay(200);
		digitalWrite(35, LOW);
		digitalWrite(36, LOW);		
		Serial.println("#"); 
		break;	
    case 'U':
		Serial.println("Press Button for Wookie");
		digitalWrite(OapReset, HIGH);
		delay(100);
		digitalWrite(OapReset, LOW);
		delay(200);
		Serial.println("#"); 
		break;	
    case 'f':
		Serial.println("Solenoid Off Power");
		digitalWrite(31, LOW);
		digitalWrite(32, LOW);
		digitalWrite(33, LOW);
		digitalWrite(34, LOW);	
		Serial.println("#"); 
		break;			
    case 'I':
		Serial.println("Insert Status");
		InsertStatus();
		Serial.println("#"); 
		break;
    case 'E':
		Serial.println("Export Status");
		ExportStatus();
		Serial.println("#"); 
		break;
    //case 'i':
	//	InsertDUT();
	//	break;	
    //case 'o':
	//	ExportDUT();
	//	break;		
    case 'y':
		Serial.println("Get YellowButton Status");
		val=digitalRead(YellowButton);
		Serial.println(val);		
		Serial.println("#"); 
		break;
    case 'g':
		Serial.println("Get GreenButton Status");
		val=digitalRead(GreenButton);
		Serial.println(val);		
		Serial.println("#"); 
		break;	
    case 'V':
		SolenoidValveSensor();
		break;	
    case 'B':
		Serial.println("Turn On Detect Board LED");
		digitalWrite(DetectBoardLED,HIGH);		
		Serial.println("#"); 
		break;	
    case 'b':
		Serial.println("Turn Off Detect Board LED");
		digitalWrite(DetectBoardLED,LOW);		
		Serial.println("#"); 
		break;
    case 'm':
		Serial.println("Get Detect detect pin 1 Status");
		val=digitalRead(detect1);
		Serial.println(val);
		Serial.println("Get Sensor detect pin 2 Status");
		val=digitalRead(detect2);
		Serial.println(val);		
		Serial.println("#"); 
		break;
	case '~':
		Serial.println("Run ~");
		digitalWrite(RedLight,LOW);
		digitalWrite(YellowLight,HIGH);
		digitalWrite(GreenLight,HIGH);
		delay(500);
		digitalWrite(RedLight,HIGH);
		digitalWrite(YellowLight,LOW);
		digitalWrite(GreenLight,HIGH);
		delay(500);
		digitalWrite(RedLight,HIGH);
		digitalWrite(YellowLight,HIGH);
		digitalWrite(GreenLight,LOW);
		delay(500);
		digitalWrite(RedLight,HIGH);
		digitalWrite(YellowLight,LOW);
		digitalWrite(GreenLight,HIGH);
		delay(500);
		digitalWrite(RedLight,LOW);
		digitalWrite(YellowLight,HIGH);
		digitalWrite(GreenLight,HIGH);	
		Serial.println("#"); 
		break;		
	case '!':
		Serial.println("Turn On Red");
		digitalWrite(RedLight,LOW);
		digitalWrite(YellowLight,HIGH);
		digitalWrite(GreenLight,HIGH);
		Serial.println("#"); 
		break;
	case '@':
		Serial.println("Turn On Yellow");
		digitalWrite(RedLight,HIGH);
		digitalWrite(YellowLight,LOW);
		digitalWrite(GreenLight,HIGH);	
		Serial.println("#"); 
		break;
	case '#':
		Serial.println("Turn On Green");
		digitalWrite(RedLight,HIGH);
		digitalWrite(YellowLight,HIGH);
		digitalWrite(GreenLight,LOW);
		Serial.println("#"); 		
		break;
    case 'C':
		Serial.println("AC ON");
		digitalWrite(AcPin,LOW);
		Serial.println("#"); 
		break;
    case 'c':
		Serial.println("AC OFF");
		digitalWrite(AcPin,HIGH);
		Serial.println("#"); 
		break;				
    case 'D':
		Serial.println("Enable DC");
		digitalWrite(DCctl,HIGH);
		Serial.println("#"); 
		break;
    case 'd':
		Serial.println("Disable DC");
		digitalWrite(DCctl,LOW);
		Serial.println("#"); 
		break;
    case 'R':
		Serial.println("Switch RJ 1");
		digitalWrite(ctlswRJ,HIGH);
		Serial.println("#"); 
		break;
    case 'r':
		Serial.println("Switch RJ 2");
		digitalWrite(ctlswRJ,LOW);
		Serial.println("#"); 
		break;		
    case '0':
		Serial.println("Switch to NONE");
		digitalWrite(AcPin,HIGH);
		delay(1000);
		digitalWrite(ctl0,LOW);
		digitalWrite(ctl1, LOW);
		digitalWrite(ctl2, LOW);
		digitalWrite(ctl3, LOW);
		digitalWrite(ctl4, LOW);
		Serial.println("#"); 
		break;
    case '1':
		Serial.println("Switch to Cable A");
		digitalWrite(AcPin,HIGH);
		delay(1000);
		digitalWrite(ctl0,HIGH);  //24
		digitalWrite(ctl1, HIGH); 
		digitalWrite(ctl2, LOW);
		digitalWrite(ctl3, LOW);
		digitalWrite(ctl4, LOW);
		digitalWrite(AcPin,LOW);
		Serial.println("#"); 
		break;
    case '2':
		Serial.println("Switch to Cable B");
		digitalWrite(AcPin,HIGH);
		delay(1000);
		digitalWrite(ctl0,HIGH);  //24
		digitalWrite(ctl1, LOW); 
		digitalWrite(ctl2, HIGH);
		digitalWrite(ctl3, LOW);
		digitalWrite(ctl4, LOW);
		digitalWrite(AcPin,LOW);
		Serial.println("#"); 
		break;
    case '3':
		Serial.println("Switch to Cable C");
		digitalWrite(AcPin,HIGH);
		delay(1000);
		digitalWrite(ctl0,HIGH);  //24
		digitalWrite(ctl1, LOW); 
		digitalWrite(ctl2, LOW);
		digitalWrite(ctl3, HIGH);
		digitalWrite(ctl4, LOW);
		digitalWrite(AcPin,LOW);
		Serial.println("#"); 
		break;
    case '4':
		Serial.println("Switch to Cable D");
		digitalWrite(AcPin,HIGH);
		delay(1000);
		digitalWrite(ctl0,HIGH);  //24
		digitalWrite(ctl1, LOW); 
		digitalWrite(ctl2, LOW);
		digitalWrite(ctl3, LOW);
		digitalWrite(ctl4, HIGH);
		digitalWrite(AcPin,LOW);
		Serial.println("#"); 
		break;
	
    case '5':
			Serial.println("Test LED 5");
			ledsensor = B11101111;
			ledsensor1 = B00001111;
			TCS();
			if((countR>10)||(countG>10)||(countB>10))
			{
				if((countR>countG)&&(countR>countB))
				{
					Serial.print("red");
					Serial.print("\n");
					delay(1000);
				}
				else if((countG>=countR)&&(countG>countB))
				{
					Serial.print("green");
					Serial.print("\n");
					delay(1000);
				} 
				else if((countB>countG)&&(countB>countR))
				{
					Serial.print("blue");
					Serial.print("\n");
					delay(1000);
				}
			}
			else 
			{
				delay(1000);       
			}
			Serial.println("#");
			break;
    case '6':
			Serial.println("Test LED 1");
			ledsensor = B11111110;
			ledsensor1 = B00001111;
			TCS();
			if((countR>10)||(countG>10)||(countB>10))
			{
				if((countR>countG)&&(countR>countB))
				{
					Serial.print("red");
					Serial.print("\n");
					delay(1000);
				}
				else if((countG>=countR)&&(countG>countB))
				{
					Serial.print("green");
					Serial.print("\n");
					delay(1000);
				} 
				else if((countB>countG)&&(countB>countR))
				{
					Serial.print("blue");
					Serial.print("\n");
					delay(1000);
				}
			}
			else 
			{
				delay(1000);       
			}
			Serial.println("#");
			break;		  
    case '7':
			Serial.println("Test LED 2");
			ledsensor = B11111101;
			ledsensor1 = B00001111;
			TCS();
			if((countR>10)||(countG>10)||(countB>10))
			{
				if((countR>countG)&&(countR>countB))
				{
					Serial.print("red");
					Serial.print("\n");
					delay(1000);
				}
				else if((countG>=countR)&&(countG>countB))
				{
					Serial.print("green");
					Serial.print("\n");
					delay(1000);
				} 
				else if((countB>countG)&&(countB>countR))
				{
					Serial.print("blue");
					Serial.print("\n");
					delay(1000);
				}
			}
			else 
			{
				delay(1000);       
			}
			Serial.println("#");
			break;
     case '8':
			Serial.println("Test LED 3");
			ledsensor = B11111011;
			ledsensor1 = B00001111;
			TCS();
			if((countR>10)||(countG>10)||(countB>10))
			{
				if((countR>countG)&&(countR>countB))
				{
					Serial.print("red");
					Serial.print("\n");
					delay(1000);
				}
				else if((countG>=countR)&&(countG>countB))
				{
					Serial.print("green");
					Serial.print("\n");
					delay(1000);
				} 
				else if((countB>countG)&&(countB>countR))
				{
					Serial.print("blue");
					Serial.print("\n");
					delay(1000);
				}
			}
			else 
			{
				delay(1000);       
			}
			Serial.println("#");
			break;
     case '9':   
			Serial.println("Test LED 4");
			ledsensor = B11110111;
			ledsensor1 = B00001111;
			TCS();
			if((countR>10)||(countG>10)||(countB>10))
			{
				if((countR>countG)&&(countR>countB))
				{
					Serial.print("red");
					Serial.print("\n");
					delay(1000);
				}
				else if((countG>=countR)&&(countG>countB))
				{
					Serial.print("green");
					Serial.print("\n");
					delay(1000);
				} 
				else if((countB>countG)&&(countB>countR))
				{
					Serial.print("blue");
					Serial.print("\n");
					delay(1000);
				}
			}
			else 
			{
				delay(1000);       
			}
			Serial.println("#");
			break;				
    case 's':
		Serial.println("Get Sensor 1 Status");
		val=digitalRead(sensor1);
		Serial.println(val);
		Serial.println("Get Sensor 2 Status");
		val=digitalRead(sensor2);
		Serial.println(val);		
		Serial.println("#"); 
		break;
	case 'A':
		if ( SwitchNoneN() == 0 ) {
			SwitchNoneN();
			Serial.println("PWC Test : FAILED");
			break;
		}
		if ( SwitchAA() == 0 ) {
			SwitchNoneN();
			Serial.println("\r\nPWC Test : FAILED\r\n#"); 
			break;
		}
		if ( SwitchNoneN() == 0 ) {
			SwitchNoneN();
			Serial.println("\r\nPWC Test : FAILED\r\n#"); 
			break;
		}
		if ( SwitchBB() == 0 ) {
			SwitchNoneN();
			Serial.println("\r\nPWC Test : FAILED\r\n#"); 
			break;		
		}
		if ( SwitchNoneN() == 0 ) {
			SwitchNoneN();
			Serial.println("\r\nPWC Test : FAILED\r\n#"); 
			break;		
		}
		if ( SwitchCC() == 0 ) {
			SwitchNoneN();
			Serial.println("\r\nPWC Test : FAILED\r\n#"); 
			break;		
		}
		if ( SwitchNoneN() == 0 ) {
			SwitchNoneN();
			Serial.println("\r\nPWC Test : FAILED\r\n#"); 
			break;		
		}
		if ( SwitchDD() == 0 ) {
			SwitchNoneN();
			Serial.println("\r\nPWC Test : FAILED\r\n#"); 
			break;		
		}
		if ( SwitchNoneN() == 0 ) {
			SwitchNoneN();
			Serial.println("\r\nPWC Test : FAILED\r\n#"); 
			break;		
		}
		Serial.println("\r\nPWC Test : PASSED\r\n#"); 
		break;
    default:
			Serial.println("Type 'H' to get more information");
			break;
    }  
  }
}

int SwitchNoneN() {
	Serial.print("Switch to NONE ");
	digitalWrite(AcPin,HIGH);
	delay(1000);	
	digitalWrite(ctl0,LOW);
	digitalWrite(ctl1, LOW);
	digitalWrite(ctl2, LOW);
	digitalWrite(ctl3, LOW);
	digitalWrite(ctl4, LOW);
	delay(250);
	testcount=0;
	passcount=0;
	while (1) {
		testcount++;
		if (testcount == 6) {
			Serial.print(" FAIL");
			return 0;
		}
		delay(250);
		val1=digitalRead(sensor1);
		val2=digitalRead(sensor2);
		if ( (val1 == 0) || (val2 == 0) ) {
			Serial.print(".");
			passcount = 0;
		} else {
			Serial.print("*");
			passcount++;
			if (passcount == 2) {
				Serial.print(" PASS");
				Serial.println("");
				return 1;
			}
		}
	}
}

int SwitchAA() {
	Serial.print("Switch to Cable A ");
	digitalWrite(AcPin,HIGH);
	delay(1000);
	digitalWrite(ctl0,HIGH);  //24
	digitalWrite(ctl1, HIGH); 
	digitalWrite(ctl2, LOW);
	digitalWrite(ctl3, LOW);
	digitalWrite(ctl4, LOW);
	digitalWrite(AcPin,LOW);	
	delay(250);
	testcount=0;
	passcount=0;
	while (1) {
		testcount++;
		if (testcount == 80) {
			Serial.print(" FAIL");
			return 0;
		}
		delay(250);
		val1=digitalRead(sensor1);
		val2=digitalRead(sensor2);
		if ( (val1 == 1) || (val2 == 1) ) {
			Serial.print(".");
			passcount = 0;
		} else {
			Serial.print("*");
			passcount++;
			if (passcount == 4) {
				Serial.print(" PASS");
				Serial.println("");
				return 1;
			}
		}
	}
}

int SwitchBB() {
	Serial.print("Switch to Cable B ");
	digitalWrite(AcPin,HIGH);
	delay(1000);
	digitalWrite(ctl0,HIGH);  //24
	digitalWrite(ctl1, LOW); 
	digitalWrite(ctl2, HIGH);
	digitalWrite(ctl3, LOW);
	digitalWrite(ctl4, LOW);
	digitalWrite(AcPin,LOW);
	delay(250);
	testcount=0;
	passcount=0;
	while (1) {
		testcount++;
		if (testcount == 80) {
			Serial.print(" FAIL");
			return 0;
		}
		delay(250);
		val1=digitalRead(sensor1);
		val2=digitalRead(sensor2);
		if ( (val1 == 1) || (val2 == 1) ) {
			Serial.print(".");
			passcount = 0;
		} else {
			Serial.print("*");
			passcount++;
			if (passcount == 4) {
				Serial.print(" PASS");
				Serial.println("");
				return 1;
			}
		}
	}
}

int SwitchCC() {
	Serial.print("Switch to Cable C ");
	digitalWrite(AcPin,HIGH);
	delay(1000);
	digitalWrite(ctl0,HIGH);  //24
	digitalWrite(ctl1, LOW); 
	digitalWrite(ctl2, LOW);
	digitalWrite(ctl3, HIGH);
	digitalWrite(ctl4, LOW);
	digitalWrite(AcPin,LOW);
	delay(250);
	testcount=0;
	passcount=0;
	while (1) {
		testcount++;
		if (testcount == 80) {
			Serial.print(" FAIL");
			return 0;
		}
		delay(250);
		val1=digitalRead(sensor1);
		val2=digitalRead(sensor2);
		if ( (val1 == 1) || (val2 == 1) ) {
			Serial.print(".");
			passcount = 0;
		} else {
			Serial.print("*");
			passcount++;
			if (passcount == 4) {
				Serial.print(" PASS");
				Serial.println("");
				return 1;
			}
		}
	}
}

int SwitchDD() {
	Serial.print("Switch to Cable D ");
	digitalWrite(AcPin,HIGH);
	delay(1000);
	digitalWrite(ctl0,HIGH);  //24
	digitalWrite(ctl1, LOW); 
	digitalWrite(ctl2, LOW);
	digitalWrite(ctl3, LOW);
	digitalWrite(ctl4, HIGH);
	digitalWrite(AcPin,LOW);
	delay(250);
	testcount=0;
	passcount=0;
	while (1) {
		testcount++;
		if (testcount == 80) {
			Serial.print(" FAIL");
			return 0;
		}
		delay(250);
		val1=digitalRead(sensor1);
		val2=digitalRead(sensor2);
		if ( (val1 == 1) || (val2 == 1) ) {
			Serial.print(".");
			passcount = 0;
		} else {
			Serial.print("*");
			passcount++;
			if (passcount == 4) {
				Serial.print(" PASS");
				Serial.println("");
				return 1;
			}
		}
	}
}

void SolenoidValveSensor () {
	s41 = digitalRead(41);
	Serial.print("41 = ");
	Serial.println(s41);
	s42 = digitalRead(42);
	Serial.print("42 = ");
	Serial.println(s42);
	s43 = digitalRead(43);
	Serial.print("43 = ");
	Serial.println(s43);
	s44 = digitalRead(44);
	Serial.print("44 = ");
	Serial.println(s44);
	s45 = digitalRead(45);
	Serial.print("45 = ");
	Serial.println(s45);
	s46 = digitalRead(46);
	Serial.print("46 = ");
	Serial.println(s46);	
	Serial.println("#"); 	
}

void InsertDUT () {
	Serial.println("Insert DUT");
	Serial.println("Control Solenoid valve 2 UP");
	//Serial.println("Pin 31 LOW , Pin 32 HIGH");
		digitalWrite(31, LOW);
		digitalWrite(32, HIGH);
	//Serial.println("Require 41 HIGH , 42 LOW");
	while (1) {
		delay(100);
		s41 = digitalRead(41);
		s42 = digitalRead(42);
		if ( debug ) {
			SolenoidValveSensor();
		}			
		if ( (s41 == 1) && (s42== 0) ) {
			break;
		}
	}
	delay(100);	
	Serial.println("Control Solenoid valve 1 IN");
	//Serial.println("Pin 33 HIGH , Pin 34 LOW");
		digitalWrite(33, HIGH);
		digitalWrite(34, LOW);
	//Serial.println("Require 43 LOW , 44 HIGH");
	while (1) {
		delay(100);
		s43 = digitalRead(43);
		s44 = digitalRead(44);
		if ( debug ) {
			SolenoidValveSensor();
		}			
		if ( (s43 == 0) && (s44== 1) ) {
			break;
		}
	}
	delay(100);
	Serial.println("Control Solenoid valve 2 Down");
	//Serial.println("Pin 31 High , Pin 32 LOW");
		digitalWrite(31, HIGH);
		digitalWrite(32, LOW);
	//Serial.println("Require 41 LOW , 42 HIGH");
	while (1) {
		delay(100);
		s41 = digitalRead(41);
		s42 = digitalRead(42);
		if ( debug ) {
			SolenoidValveSensor();
		}			
		if ( (s41 == 0) && (s42== 1) ) {
			break;
		}
	}
	// digitalWrite(31, LOW);
	// digitalWrite(32, LOW);
	// digitalWrite(33, LOW);
	// digitalWrite(34, LOW);			
	Serial.println("#"); 	
}

void InsertStatus () {
	s41 = digitalRead(41);
	s42 = digitalRead(42);
	s43 = digitalRead(43);
	s44 = digitalRead(44);
	if ( (s43 == 0) && (s44== 1) && (s41 == 0) && (s42== 1)) {
		digitalWrite(DetectBoardLED,HIGH);
		delay(150);	
		val1=digitalRead(detect1);
		val2=digitalRead(detect2);
		digitalWrite(DetectBoardLED,LOW);		
		if ( (s43 == 0) && (s44== 1) && (s41 == 0) && (s42== 1) && (val1 == 0) && (val2 == 0)) {
			Serial.println("1");
		}
	} else {
		Serial.println("0"); 	
	}
}

void ExportStatus () {
	s41 = digitalRead(41);
	s42 = digitalRead(42);
	s43 = digitalRead(43);
	s44 = digitalRead(44);
	if ( (s43 == 1) && (s44== 0) && (s41 == 1) && (s42== 0) ) {
		Serial.println("1"); 	
	} else {
		Serial.println("0"); 	
	}
}

void InsertDUT1 () {
	Serial.println("Insert DUT");
	Serial.println("Control Solenoid valve 2 UP");
	//Serial.println("Pin 31 LOW , Pin 32 HIGH");
		digitalWrite(31, LOW);
		digitalWrite(32, HIGH);
	//Serial.println("Require 41 HIGH , 42 LOW");
	while (1) {
		delay(100);
		s41 = digitalRead(41);
		s42 = digitalRead(42);
		if ( debug ) {
			SolenoidValveSensor();
		}			
		if ( (s41 == 1) && (s42== 0) ) {
			break;
		}
	}
	delay(100);	
	Serial.println("Control Solenoid valve 1 IN");
	//Serial.println("Pin 33 HIGH , Pin 34 LOW");
		digitalWrite(33, HIGH);
		digitalWrite(34, LOW);
	//Serial.println("Require 43 LOW , 44 HIGH");
	while (1) {
		delay(100);
		s43 = digitalRead(43);
		s44 = digitalRead(44);
		if ( debug ) {
			SolenoidValveSensor();
		}			
		if ( (s43 == 0) && (s44== 1) ) {
			break;
		}
	}
	// digitalWrite(31, LOW);
	// digitalWrite(32, LOW);
	// digitalWrite(33, LOW);
	// digitalWrite(34, LOW);			
	Serial.println("#"); 	
}

void ExportDUT () {
	Serial.println("Export DUT");
	s41 = digitalRead(41);
	s42 = digitalRead(42);
	s43 = digitalRead(43);
	s44 = digitalRead(44);
	if ( (s43 == 0) && (s44== 1) && (s41 == 0) && (s42== 1) ) {
		Serial.println("Control Solenoid valve 1 IN");
		digitalWrite(33, HIGH);
		digitalWrite(34, LOW);
		delay(200);
		digitalWrite(33, LOW);
		digitalWrite(34, LOW);
	}
	Serial.println("Control Solenoid valve 2 UP");
	// Serial.println("Pin 31 LOW , Pin 32 HIGH");
		digitalWrite(31, LOW);
		digitalWrite(32, HIGH);
	// Serial.println("Require 41 HIGH , 42 LOW");
	while (1) {
		delay(100);
		s41 = digitalRead(41);
		s42 = digitalRead(42);
		if ( debug ) {
			SolenoidValveSensor();
		}				
		if ( (s41 == 1) && (s42== 0) ) {
			break;
		}
	}
	delay(100);
	Serial.println("Control Solenoid valve 1 Out");
	// Serial.println("Pin 33 LOW , Pin 34 HIGH");
		digitalWrite(33, HIGH);
		digitalWrite(34, LOW);
		delay(300);	
		digitalWrite(33, LOW);
		digitalWrite(34, HIGH);
	// Serial.println("Require 43 HIGH , 44 LOW");
	while (1) {
		delay(100);
		s43 = digitalRead(43);
		s44 = digitalRead(44);
		if ( debug ) {
			SolenoidValveSensor();
		}					
		if ( (s43 == 1) && (s44== 0) ) {
			break;
		}
	}
	// digitalWrite(31, LOW);
	// digitalWrite(32, LOW);
	// digitalWrite(33, LOW);
	// digitalWrite(34, LOW);				
	Serial.println("#"); 
}
