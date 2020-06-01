// Use commands from computer to control Arsuino.

#include <IRremote.h>

IRsend irsend;

// Define Pin
int ledPin = 13;

void setup()
{
  // Create Serial Object (115200 Baud)
  Serial.begin(115200);
  pinMode (ledPin, OUTPUT);
}

void loop()
{
    while (Serial.available() == 0);

    // Read the incoming byte
    int val = Serial.read();

    if (val == 88) {
        irsend.sendNEC(0x1067A857, 32);
        Serial.println("Lu: Received X");
    }

    else if (val == 83) {
        irsend.sendNEC(0x1067A857, 32);
        Serial.println("Lu: Received S");
    }

    else {
        Serial.println("Lu: Nothing found!!!");
    }

    //Serial.println(val);
}