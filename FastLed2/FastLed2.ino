#include "FastLED.h"
 
#define NUM_LEDS 22
#define DATA_PIN 5
#define TWO_HUNDRED_PI 628
#define TWO_THIRDS_PI 2.094
 
CRGB leds[NUM_LEDS];
 
int val1 = 0;
int val2 = 0;
int val3 = 0;
 
void setup() { 
    FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);
}
 
void loop() {
    for(int i=0; i<TWO_HUNDRED_PI; i++){
        val1 = round(255/2.0*(sin(i/100.0)+1));
        val2 = round(255/2.0*(sin(i/100.0+TWO_THIRDS_PI)+1));
        val3 = round(255/2.0*(sin(i/100.0-TWO_THIRDS_PI)+1));
     
        leds[7] = CHSV(0, 255, val1);
        leds[8] = CHSV(96, 255, val2);
        leds[9] = CHSV(160, 255, val3);
     
        FastLED.show();
     
        delay(1);
    }
}
