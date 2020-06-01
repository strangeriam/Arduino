// for temperature & humidity sensor.
#include <dht.h>

dht DHT;
#define DHT11_PIN 7

// for RGB backlight LCD.
#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

const int colorR = 0;
const int colorG = 0;
const int colorB = 0;

int lastTemp;
int dataTemp;

////////////////////////////
void setup(){
      Serial.begin(9600);
}

void LcdText( int dataHumi ){

    if (dataHumi < 40) {
             lcd.print("EMP attack !!!");

    } else if (dataHumi >= 40 && dataHumi < 50) {
             lcd.print("Sunny day ~~~");

    } else if (dataHumi >= 50 && dataHumi < 70) {
             lcd.print("=^_^= Papa loveU");

    } else if (dataHumi >= 70 && dataHumi < 85) {
             lcd.print("=^o^= umbrella");

    } else if (dataHumi >= 85) {
             lcd.print("^^!!! raining");
    } else {
             lcd.print("Sys got wrong!!!");
    }
}

void LcdColor( int dataHumi ){

    if (dataHumi < 40) {
             lcd.setRGB(100, 0, 0); delay(1000);
             lcd.setRGB(0, 0, 100);
             delay(5000);

    } else if (dataHumi >= 40 && dataHumi < 50) {
             lcd.setRGB(colorR, 100, colorB);
             delay(5000);

    } else if (dataHumi >= 50 && dataHumi < 70) {
             lcd.setRGB(0, 255, 150);
             delay(5000);

    } else if (dataHumi >= 70 && dataHumi < 85) {
             lcd.setRGB(100, 0, 0); delay(2000);
             lcd.setRGB(255, 100, 150);
             delay(3000);

    } else if (dataHumi >= 85) {
             lcd.setRGB(100, 0, 0);
             delay(5000);
    } else {
             lcd.setRGB(colorR, colorG, colorB);
    }

    lcd.setRGB(0, 0, 0);
    delay(10000);
}

// Color Pink (255, 100, 150)

void loop(){
    // Temperature & Humidity
    int chk = DHT.read11(DHT11_PIN);

    int dataTemp = DHT.temperature;
    int dataHumi = DHT.humidity;

    Serial.print("currentTemp =");
    Serial.println(dataTemp);
    Serial.println();

    lcd.begin(16, 2);
    LcdText( dataHumi );

    lcd.setCursor(0, 1);
    lcd.print(dataTemp); lcd.print("c");
    lcd.print("..");
    lcd.print(dataHumi); lcd.print("%       ");
    LcdColor( dataHumi );
}