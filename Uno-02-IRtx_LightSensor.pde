/*
IR generator:
- Pin define (3 & Ground).
- IR code for SHM 38K Hz.
- OK   key [0x80BF738C] - (81-Q) Keyboard mapping
- EXIT Key [0x80BFA35C] - (87-W) Keyboard mapping

Light Sensor:
- Pin define (5V, Ground & A0).
- Keyboard mapping (69-E)

RGB sensor:
- Keyboard mapping (82-R)

Release Note:
- [161216] Light sensor, modified "Light Level C" begining value from "301" to "0".
*/

#include <IRremote.h>

IRsend irsend;

void setup()
{
    Serial.begin(9600);
    pinMode (A0, INPUT);
    pinMode (13, OUTPUT);

    Serial.println("Version: v161219");
}

void loop()
{
    while (Serial.available() == 0);

    int val         = Serial.read();
    int lightValue  = analogRead(A0);

    if (val == 81) {
                irsend.sendNEC( 0x80BF738C, 32 );
                Serial.println( "Queen Q: SHM 38KHz of OK." );

    } else if (val == 87) {
                irsend.sendNEC( 0x80BFA35C, 32 );
                Serial.println( "Wizard W: SHM 38KHz of EXIT." );

    } else if (val == 69) {
                if ( lightValue >= 0 && lightValue <= 500 ) {
                                Serial.print( "Eyes E:" ); Serial.print( " [" ); Serial.print( lightValue ); Serial.print( "] " );
                                Serial.print( "Light Level C." ); Serial.print( " -*_*!" );

                } else if ( lightValue >= 501 && lightValue <= 700 ) {
                                Serial.print( "Eyes E:" ); Serial.print( " [" ); Serial.print( lightValue ); Serial.print( "] " );
                                Serial.print( "Light Level B." ); Serial.print( " -^o^-" );

                } else if ( lightValue >= 701 && lightValue <= 1000 ) {
                                Serial.print( "Eyes E:" ); Serial.print( " [" ); Serial.print( lightValue ); Serial.print( "] " );
                                Serial.print( "Light Level A." ); Serial.print( " =^O^=" );
                } else {
                                Serial.print( "Eyes E: Light Down." );
                }

                Serial.println( " " );
    } else {
                Serial.print( "NeoSaid:" ); Serial.print( " [" ); Serial.print( val ); Serial.print( "] " ); Serial.print( "Nothing found!!!" );
                Serial.println( " " );
    }
}