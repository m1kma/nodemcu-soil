//
// Mika Mäkelä - 2019
//
// This code is intent to use in the NodeMCU board. 
// Read value from the analog soil sensor and send data to the Adafruit IO cloud. 

#include "config.h"

AdafruitIO_Feed *io_soil_1 = io.feed("soil1");
uint8_t int_led = D1;
uint8_t soil_power = D2;

void setup() {
    // put your setup code here, to run once:
    Serial.begin(9600);
    pinMode(int_led, OUTPUT);
  
    pinMode(soil_power, OUTPUT);  
    digitalWrite(soil_power, LOW);
  
    // ####### Connect to io.adafruit.com #######

    Serial.println("Connecting to Adafruit IO...");
    io.connect();

    int count = 0;

    // wait for a connection - blink led
    while (io.status() < AIO_CONNECTED)
    {
        Serial.println(io.statusText());

        digitalWrite(int_led, LOW);
        delay(250);
        digitalWrite(int_led, HIGH);
        delay(500);

        if (count > 20)
        {
            digitalWrite(int_led, LOW);
            delay(100);
            digitalWrite(int_led, HIGH);
            delay(100);
            digitalWrite(int_led, LOW);
            delay(100);
        
            Serial.println("No Wifi connection");
            ESP.deepSleep(300e6);
        }
        
        count++;
    }

    digitalWrite(int_led, LOW);

    // we are connected
    Serial.println(io.statusText());
    io.run();
    
    digitalWrite(soil_power, HIGH);
    delay(1000);

    int soil1 = analogRead(A0);
    Serial.println(soil1);
    
    digitalWrite(soil_power, LOW);
    io_soil_1->save(soil1);
    
    delay(1000);

    Serial.println("End. Going to sleep.");
    ESP.deepSleep(300e6);    
}

void loop() {
  delay(1000);
}
