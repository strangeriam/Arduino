const int pinLED_red        = 12;
const int pinLED_green      = 11;
const int pinLED_yellow     = 10;

void setup()
{
  pinMode(pinLED_red,    OUTPUT);
  pinMode(pinLED_green,  OUTPUT);
  pinMode(pinLED_yellow, OUTPUT);
}

void blinkLED_red() {
	   for (int i=1; i<=2; i++) {
		      digitalWrite(pinLED_red, HIGH);
		      delay(100);
		      digitalWrite(pinLED_red, LOW);
		      delay(100);
	   }

     delay(2000);
}

void blinkLED_green() {
     for (int i=1; i<=2; i++) {
          digitalWrite(pinLED_green, HIGH);
          delay(100);
          digitalWrite(pinLED_green, LOW);
          delay(100);
     }

     delay(1000);
}

void blinkLED_yellow() {
     for (int i=1; i<=2; i++) {
          digitalWrite(pinLED_yellow, HIGH);
          delay(100);
          digitalWrite(pinLED_yellow, LOW);
          delay(100);
     }

     delay(1000);
}

void loop()
{
    blinkLED_red();
    blinkLED_green();
    blinkLED_yellow();
}
