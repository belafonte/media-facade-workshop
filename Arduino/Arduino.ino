// Parse incoming messages consisting of three decimal values followed by a carriage return
//  Example  "12 34 56\n"
//  In TouchDesigner:     op('serial1').send("12 34 56", terminator="\n")
//
#include "FastLED.h"

#define LED_COUNT 60
#define NUM_CHANNELS 3
#define BUFFER_SIZE LED_COUNT *NUM_CHANNELS

CRGB leds[LED_COUNT];
// int ledsChannels = sizeof leds / sizeof leds[0] * 3;

int sensorPin = A1;
int sensorValue = 0;

unsigned char incomingByte = 0; // for incoming serial data
unsigned char buffer[BUFFER_SIZE];

// int bufferLen = sizeof buffer / sizeof buffer[0];

unsigned char val = 255;

void setup()
{
    Serial.begin(115200);

    pinMode(A1, INPUT);

    Serial.println("BEGIN");
    FastLED.addLeds<NEOPIXEL, 3>(leds, LED_COUNT);
    FastLED.show();
}

void loop()
{

    if (Serial.available() > 0)
    {
        // read the incoming byte:
        Serial.readBytes(buffer, BUFFER_SIZE);

        for (int i = 0; i < LED_COUNT; i++)
        {
            leds[i].r = buffer[i * NUM_CHANNELS];
            leds[i].g = buffer[i * NUM_CHANNELS + 1];
            leds[i].b = buffer[i * NUM_CHANNELS + 2];
        }
        FastLED.show();
    }
    sensorValue = analogRead(sensorPin);
    Serial.println(sensorValue);
}
