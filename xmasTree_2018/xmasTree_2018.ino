/* MJ's holiday xmas tree lights 2018 
 *  MIT license open source
 */

#include <FastLED.h>
#include "lightHash.h"
#include "Snowflake.h"
#include "noisefunctions.h"
  
#define PIN 7
#define FLAKEMAX 50

  
// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

bool isBlue = false;
struct Snowflake snowflakes[FLAKEMAX];
uint8_t flakeCount = 0;
uint32_t lastSpawn; uint32_t minDelay;

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<NEOPIXEL, PIN>(leds, NUM_LEDS);
  initLights();
  minDelay = 300;
  randomSeed(analogRead(0));
}

void loop() {
     
     // make everything blue
     if( !isBlue ) { 
       for( int col=0; col<COLUMNS; col++ ){
            for( int row=0; row<ROWS; row++ ) {
              leds[lights[col][row]] = CRGB::Blue;
            }
        }
        isBlue = true;
     }

     if( random(100) < 20 && flakeCount < FLAKEMAX && millis() - lastSpawn > minDelay ) { 
        if( addFlake() ) {
          Serial.print("flake added. Count "); Serial.println ( flakeCount );
        }
        else {
          Serial.print( "flake max reached at "); Serial.println( flakeCount );
        }
        lastSpawn = millis();
      }

     updateFlakes();

     Serial.println(flakeCount);
     FastLED.show();
 
 }


 void updateFlakes() {

    flakeCount = 0;
    for( uint8_t i=0; i<FLAKEMAX; i++ ) {
        if( snowflakes[i].row >=0 ) {
          snowflakes[i].setColor();
          flakeCount++;
        }
        
    }

 }

boolean addFlake( void ) {
      for( uint8_t i=0; i<FLAKEMAX; i++ ) {
          if( snowflakes[i].row < 0 ) {
            snowflakes[i].init();
            return true;
          }
        }
        return false;
}
