#include <FastLED.h>
#include "lightHash.h"
#include "Snowflake.h"
  
#define PIN 7
#define FLAKEMAX 10

  
// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

bool isBlue = false;
struct Snowflake snowflakes[FLAKEMAX];
uint8_t flakeCount = 0;

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<NEOPIXEL, PIN>(leds, NUM_LEDS);
  snowflakes_head = NULL;
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
        }
        isBlue = true;
     }

     if( random(100) < 20 && flakeCount < FLAKEMAX ) { 
        if( addFlake() ) {
          Serial.println("flake added. Count ", flakeCount );
        }
        else {
          Serial.println( "flake max reached at ", flakeCount );
        }
        
      }

     updateFlakes();

     Serial.println(flakeCount);
     FastLED.show();
 
 }


 void updateFlakes() {
  
    for( uint8_t i=0; i<FLAKEMAX; i++ ) {
        if( snowflakes[i].row >=0 ) {
          snowflakes[i].setColor();
        }
    }

 }

boolean addFlake( void ) {
      for( uint8_t i=0; i<FLAKEMAX; i++ ) {
          if( snowflakes[i].row < 0 ) {
            snowflakes[i].init();
            flakeCount++;
            return true;
          }
        }
        return false;
}
