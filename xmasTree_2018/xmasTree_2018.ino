#include <FastLED.h>
#include "lightHash.h"
#include "Snowflake.h"
  
#define NUM_LEDS 150
#define PIN 7

CRGB leds[NUM_LEDS];
  
// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

volatile byte mode=0;
int snowFlakes[COLUMNS]; // will hold the value for each column that has one snowflake
bool isBlue = false;


void setup() {
  Serial.begin(9600);
  FastLED.addLeds<NEOPIXEL, PIN>(leds, NUM_LEDS);

  initLights();
  randomSeed(analogRead(0));
}

void loop() {

     
     // make everything blue
     if( !isBlue ) { 
       for( int col=0; col<COLUMNS; col++ ){
            for( int row=0; row<ROWS; row++ ) {
              leds[lights[col][row]] = CRGB::Blue;
            }
            //ensure that snowflake flags are initialized to zero
            snowFlakes[col] = -1; 
            snowFlakes[col] = -1; 
        }
        isBlue = true;
     }
    
    for( int row = ROWS-1; row >=-1; row-- ) {
      for( int col = 0; col < COLUMNS; col++ ) {
        if( row == -1 ) {
          leds[lights[col][row+1]] = CRGB::Blue;
            if( random(100) < 25 ) {
               snowFlakes[col] = 19;
            }
        }
        else if( snowFlakes[col] == row ) {
            snowFlakes[col]--;
            leds[lights[col][row]].setRGB( 50, 50, 50 );
            if( row < 19 ) { leds[lights[col][row+1]] = CRGB::Blue; } // trailing back to blue
        }
      }
      FastLED.show();
      delay(100); // need to get rid of this evil
    }    
 }
    
  
