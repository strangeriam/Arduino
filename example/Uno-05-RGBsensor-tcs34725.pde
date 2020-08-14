/* Lu [161219]

- Connect SCL    to analog 5
  Connect SDA    to analog 4
  Connect VDD    to 3.3V DC
  Connect GROUND to common ground

Initialise with default values (int time = 2.4ms, gain = 1x)

RGB sensor:
- Keyboard mapping (82-R) (84-T)

 */

#include <Wire.h>
#include "Adafruit_TCS34725.h"

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X);

void setup(void) {
     Serial.begin(9600);

     if (tcs.begin()) {
              Serial.println("Found sensor");
     } else {
              Serial.println("No TCS34725 found ... check your connections");
              while (1);
     }
}

void loop(void) {
     // KEYBOARD Key mapping
     while (Serial.available() == 0);
     int val = Serial.read();

     // RGB sensor
     uint16_t r, g, b, c, colorTemp, lux;

     tcs.getRawData(&r, &g, &b, &c);
     colorTemp = tcs.calculateColorTemperature(r, g, b);
     lux = tcs.calculateLux(r, g, b);

     if (val == 82) {
                Serial.print("Color Temp: "); Serial.print(colorTemp, DEC); Serial.print(" K - ");
                Serial.print("Lux: "); Serial.print(lux, DEC); Serial.print(" - ");
                Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
                Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
                Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");
                Serial.print("C: "); Serial.print(c, DEC);

     } else if (val == 84) {
                int colorRed   = r;
                int colorGreen = g;
                int colorBlue  = b;

                //Serial.print(colorRed); Serial.print(" "); Serial.print(colorGreen); Serial.print(" "); Serial.print(colorBlue);

                if ( colorRed >= 3000 && colorRed <= 4000 && colorGreen >= 2500 && colorGreen <= 3500 && colorBlue >= 1000 && colorBlue <= 2000 ) {
                          Serial.print( "This LEGO color is: YELLOW" );

                } else if ( colorRed >= 700 && colorRed <= 1000 && colorGreen >= 1000 && colorGreen <= 2000 && colorBlue >= 1000 && colorBlue <= 2000 ) {
                          Serial.print( "This LEGO color is: GREEN" );

                } else if ( colorRed >= 1000 && colorRed <= 2000 && colorGreen >= 800 && colorGreen <= 1000 && colorBlue >= 700 && colorBlue <= 800 ) {
                          Serial.print( "This LEGO color is: RED" );

                } else if ( colorRed >= 900 && colorRed <= 1000 && colorGreen >= 1000 && colorGreen <= 2000 && colorBlue >= 2000 && colorBlue <= 3000 ) {
                          Serial.print( "This LEGO color is: BLUE" );
                } else {
                          Serial.print( "NO COLOR!!!" );
                }

     } else {
                Serial.print( "NeoSaid:" ); Serial.print( " [" ); Serial.print( val ); Serial.print( "] " ); Serial.print( "Nothing found!!!" );
     }

     Serial.println(" ");
}
