/*
Keyboard key reserved:
Q[81] W[87] E[69] R[82] T[84] Y[89]
A[65] S[83]

IR generator 1:
- Pin define (3 & Ground).
- IR code for SHM 38K Hz.
- OK   key [0x80BF738C] - (81-Q) Keyboard mapping
- EXIT Key [0x80BFA35C] - (87-W) Keyboard mapping

IR generator 2:
- Pin define (4 & Ground).
- IR code for SHM 38K Hz.
- OK   key [0x80BF738C] - (65-A) Keyboard mapping
- EXIT Key [0x80BFA35C] - (83-S) Keyboard mapping

Light Sensor:
- Pin define (5V, Ground & A0).
- Keyboard mapping (69-E)

RGB sensor:
- ALL - (82-R) Keyboard mapping
- Lux - (84-T) Keyboard mapping
- RGB - (89-Y) Keyboard mapping

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

void setup()
{
      Serial.begin(9600);
      pinMode (A0, INPUT);
      pinMode (13, OUTPUT);

      if (tcs.begin()) {
                Serial.println("Found RGB sensor.");
      } else {
                Serial.println("No RGB sensor found ... ignore that if you don't nedded.");
                while (1);
      }
}

void loop()
{
    while (Serial.available() == 0);

    int val         = Serial.read();
    int lightValue  = analogRead(A0);

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
    } else {
                Serial.print( "NeoSaid:" ); Serial.print( " [" ); Serial.print( val ); Serial.print( "] " ); Serial.print( "Nothing found!!!" );
    }

    Serial.println("");
}