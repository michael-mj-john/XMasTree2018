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
struct Snowflake* snowflakes_head;
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
        struct Snowflake* flakePtr;
        flakePtr = new Snowflake();
        flakePtr->next = snowflakes_head; 
        flakeCount++;
     }

     updateFlakes();

     Serial.println(flakeCount);
     FastLED.show();
 
 }


 void updateFlakes() {
    struct Snowflake *flakePtr = snowflakes_head;
    struct Snowflake *prevPtr;
    boolean flakeDead;
    while( flakePtr != NULL ) {
       flakeDead = flakePtr->setColor();
       if( flakeDead ) {
         Serial.println( "flake flagged" );
          prevPtr->next = flakePtr->next;
          delete flakePtr;
          flakeCount--;
          Serial.println( "removed flake" );
       }     
       if( 
       prevPtr = flakePtr;
       flakePtr = flakePtr->next;      
    }
 
 }
  
