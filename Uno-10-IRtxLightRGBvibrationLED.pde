/*
Keyboard key reserved:
Q[81] W[87] E[69] R[82] T[84] Y[89] U[85] I[73] O[79] P[80]
A[65] S[83] D[68] F[70] G[71]

IR generator 1:
- Pin define (3 & Ground).
- IR code for SHM 38K Hz.
- OK   key [0x80BF738C] - (81-Q) Keyboard mapping
- EXIT Key [0x80BFA35C] - (87-W) Keyboard mapping

IR generator 2:
- Pin define (4 & Ground).
- IR code for SHM 38K Hz, Key code on bottom line.
- OK   key [0x80BF738C] - (65-A) Keyboard mapping
- EXIT Key [0x80BFA35C] - (83-S) Keyboard mapping

Light Sensor:
- Pin define (5V, Ground & A0).
- Keyboard mapping (69-E)

RGB sensor:
- ALL - (82-R) Keyboard mapping
- Lux - (84-T) Keyboard mapping
- RGB - (89-Y) Keyboard mapping

Vibration sensor:
- Pin define (5V, Ground & D9)
- Extra LED  (13 & Ground)
- Keyboard mapping (85-U)

3 LED for Status Indicator
- Pin define (10 Yellow, 11 Green, 12 Red & Ground).
- YELLOW   (73-I) Keyboard mapping
- GREEN    (79-O) Keyboard mapping
- RED      (80-P) Keyboard mapping

Release Note:
- [161216] Light sensor, modified "Light Level C" begining value from "301" to "0".
*/

// IR
#include <IRremote.h>
IRsend irsend;

// RGB sensor
#include <Wire.h>
#include "Adafruit_TCS34725.h"
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X);

int pin_LED   = 13;
int pin_Light = A0;
int pin_EP    = 9;

// Status Indicator
int pinLED_red        = 12;
int pinLED_green      = 11;
int pinLED_yellow     = 10;

void setup() {
      Serial.begin(9600);
      pinMode (pin_Light, INPUT);
      pinMode (pin_LED,   OUTPUT);
      pinMode (pin_EP,    INPUT); //set EP input for measurment

      pinMode (pinLED_red,    OUTPUT); // Status Indicator
      pinMode (pinLED_green,  OUTPUT); // Status Indicator
      pinMode (pinLED_yellow, OUTPUT); // Status Indicator

      if (tcs.begin()) {
                Serial.println("Found RGB sensor.");
      } else {
                Serial.println("No RGB sensor found ... ignore that if you don't nedded.");
               // while (1);
      }

      //blinkLED_red();
      //blinkLED_green();
      //blinkLED_yellow();
}

// Status Indicator - Start
void blinkLED_red() {
       for (int i=1; i<=2; i++) {
              digitalWrite(pinLED_red, LOW);
              delay(100);
              digitalWrite(pinLED_red, HIGH);
              delay(100);
       }

     delay(2000);
}

void blinkLED_green() {
     for (int i=1; i<=2; i++) {
          digitalWrite(pinLED_green, LOW);
          delay(100);
          digitalWrite(pinLED_green, HIGH);
          delay(100);
     }

     delay(1000);
}

void blinkLED_yellow() {

          digitalWrite(pinLED_red,   LOW);
          digitalWrite(pinLED_green, LOW);

     for (int i=1; i<=10; i++) {
          digitalWrite(pinLED_yellow, HIGH);
          delay(100);
          digitalWrite(pinLED_yellow, LOW);
          delay(100);
     }

     delay(1000);
}
// Status Indicator - End

void loop() {
     while (Serial.available() == 0);

     int val         = Serial.read();
     int lightValue  = analogRead(pin_Light);

     // IR remote.
     if (val == 81 || val == 87) {
                if (val == 81) {
                                irsend.sendNEC( 0x80BF738C, 32 );
                                Serial.print( "key Q:" ); Serial.print( " [" );  Serial.print( "OK" ); Serial.print( "] " );
                                Serial.print( "IR SHM 38KHz." );
                } else if (val == 87) {
                                irsend.sendNEC( 0x80BFA35C, 32 );
                                Serial.print( "key W:" ); Serial.print( " [" );  Serial.print( "EXIT" ); Serial.print( "] " );
                                Serial.print( "IR SHM 38KHz." );
                }
     // Light sensor.
     } else if (val == 69) {
                if ( lightValue >= 0 && lightValue <= 500 ) {
                                Serial.print( "key E:" ); Serial.print( " [" ); Serial.print( lightValue ); Serial.print( "] " );
                                Serial.print( "Light Level C." ); Serial.print( " -*_*!" );

                } else if ( lightValue >= 501 && lightValue <= 700 ) {
                                Serial.print( "key E:" ); Serial.print( " [" ); Serial.print( lightValue ); Serial.print( "] " );
                                Serial.print( "Light Level B." ); Serial.print( " -^o^-" );

                } else if ( lightValue >= 701 && lightValue <= 1000 ) {
                                Serial.print( "key E:" ); Serial.print( " [" ); Serial.print( lightValue ); Serial.print( "] " );
                                Serial.print( "Light Level A." ); Serial.print( " =^O^=" );
                } else {
                                Serial.print( "key E: Light Down." );
                }
     // RGB sensor.
     } else if (val == 82 || val == 84 || val == 89) {
                uint16_t r, g, b, c, colorTemp, lux;

                tcs.getRawData(&r, &g, &b, &c);
                colorTemp = tcs.calculateColorTemperature(r, g, b);
                lux = tcs.calculateLux(r, g, b);

                if (val == 82) {
                                Serial.print("key R:");
                                Serial.print(" Color Temp: "); Serial.print(colorTemp, DEC); Serial.print(" K - ");
                                Serial.print("Lux: "); Serial.print(lux, DEC); Serial.print(" - ");
                                Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
                                Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
                                Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");
                                Serial.print("C: "); Serial.print(c, DEC); Serial.print(" ");

                } else if (val == 84) {
                                Serial.print("key T:"); Serial.print( " [ " ); Serial.print(lux, DEC); Serial.print( " ] " );
                                Serial.print("Lux, 1 Lux= 1 lumen/meter^2.");

                } else if (val == 89) {
                                Serial.print("key Y:"); Serial.print( " [ " ); Serial.print(r, DEC); Serial.print( " " ); Serial.print(g, DEC); Serial.print( " " ); Serial.print(b, DEC); Serial.print( " ] " );
                                //Serial.print("key Y:"); Serial.print( " [ " ); Serial.print( "Red_" ); Serial.print(r, DEC); Serial.print( " " ); Serial.print( "Green_" ); Serial.print(g, DEC); Serial.print( " " ); Serial.print( "Blue_" ); Serial.print(b, DEC); Serial.print( " ]" );
                                Serial.print("R_G_B, Color detected.");
                }
     // Vibration Sensor.
     } else if (val == 85) {
                long measurement = TP_init(); //Vibration sensor.
                delay(500); // default is 50. unit is ?

                Serial.print( "key U:" ); Serial.print( " [" );  Serial.print( measurement ); Serial.print( "] " );

                if (measurement > 500){
                                digitalWrite(pin_LED, HIGH);
                                Serial.print( "Vibration Level: Earthquake." );

                } else if (measurement > 100){
                                digitalWrite(pin_LED, HIGH); 
                                Serial.print( "Vibration Level: Shake Tea." );
                                digitalWrite(pin_LED, LOW); 
                } else {
                                digitalWrite(pin_LED, LOW); 
                                Serial.print( "Vibration Level: Very Quiet." );
                }
     // Status Indicator
     } else if (val == 73 || val == 79 || val == 80) {
                if (val == 73) {
                                blinkLED_yellow();
                                Serial.print( "key I:" ); Serial.print( " [" );  Serial.print( "Indicator YELLOW" ); Serial.print( "] " );
                } else if (val == 79) {
                                blinkLED_green();
                                Serial.print( "key O:" ); Serial.print( " [" );  Serial.print( "Indicator GREEN" ); Serial.print( "] " );
                } else if (val == 80) {
                                blinkLED_red();
                                Serial.print( "key P:" ); Serial.print( " [" );  Serial.print( "Indicator RED" ); Serial.print( "] " );
                }

     } else if (val == 65) {
                                Serial.print( "key A:" ); Serial.print( " [" );  Serial.print( "" ); Serial.print( "] " );
                                Serial.print( "Unused." );
     } else {
                                Serial.print( "NeoSaid:" ); Serial.print( " [" ); Serial.print( val ); Serial.print( "] " ); Serial.print( "Nothing found!!!" );
     }

     Serial.println("");
}


// for Vibration sensor.
long TP_init(){
     delay(10); // default is 10
     long measurement=pulseIn (pin_EP, HIGH);  //wait for the pin to get HIGH and returns measurement
     return measurement;
}


/*
SHM IR Key code list:
POWER [80BF3BC4]   - 1 [80BF49B6] - ARROW UP     [80BF53AC] - PLAY           [80BF8976]
FAV   [80BFF30C]   - 2 [80BFC936] - ARROW DOWN   [80BF4BB4] - PLAY BACK      [80BFB34C]
OK    [80BF738C]   - 3 [80BF33CC] - ARROW LEFT   [80BF837C] - PLAY FORWARD   [80BF0BF4]
VOL+  [80BF01FE]   - 4 [80BF718E] - ARROW RIGHT  [80BF11EE] - STOP           [80BFB14E]
VOL-  [80BF817E]   - 5 [80BFF10E] - EPG          [80BF5BA4] - PAUSE          [80BFE916]
CH+   [80BFA15E]   - 6 [80BF13EC] - MENU         [80BF19E6] - TV/RADIO       [80BFC33C]
CH-   [80BF619E]   - 7 [80BF51AE] - OPT          [80BFA956] - SETUP          [80BFC13E]
MUTE  [80BF39C6]   - 8 [80BFD12E] - VOD          [80BF6B94] - COLOR RED      [80BF916E]
DOWN  [80BF31CE]   - 9 [80BF23DC] - NAV          [80BF11EE] - COLOR GREEN    [80BF21DE]
UP    [80BFBB44]   - 0 [80BFE11E] - LAST         [80BF41BE] - COLOR YELLOW   [80BF9B64]
EXIT  [80BFA35C]                                              COLOR BLUE     [80BF6996]

TRZ IR Key code list:
POWER   [1067E21D] - 1 [1067D827] - ARROW UP     [106728D7] - PLAY/PAUSE     [10679867]
HOME    [1067C23D] - 2 [1067E817] - ARROW DOWN   [10676897] - PLAY BACK      [1067D22D]
URL     [106742BD] - 3 [1067C837] - ARROW LEFT   [10678877] - PLAY FORWARD   [106718E7]
BAR     [1067827D] - 4 [10671AE5] - ARROW RIGHT  [1067B847] - PLAY STEP BACK [106738C7]
MENU    [106702FD] - 5 [10672AD5] - VOL+         [10677A85] - PLAY STEP NEXT [106708F7]
SMILE 1 [1067629D] - 6 [10670AF5] - VOL+         [1067FA05] - STOP           [106758A7]
SMILE 2 [1067A25D] - 7 [10679A65] - COLOR RED    [1067DA25]
SMILE 3 [106722DD] - 8 [1067AA55] - COLOR BLUE   [1067EA15]
OK      [1067A857] - 9 [10678A75] - COLOR YELOOW [1067CA35]
EPG     [10677887] - 0 [10676A95]
TAB     [106748B7]

*/