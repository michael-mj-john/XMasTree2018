/* MJ's holiday xmas tree lights 2018 
 *  MIT license open source
 */

#include <FastLED.h>
#include "lightHash.h"
//#include "Snowflake.h"
#include "noisefunctions.cpp"
  
#define PIN 7
#define FLAKEMAX 50
#define FIRE true

  
// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

#ifdef SNOWFLAKE
bool isBlue = false;
struct Snowflake snowflakes[FLAKEMAX];
uint8_t flakeCount = 0;
uint32_t lastSpawn; uint32_t minDelay=300;
#endif

#ifdef FIRE
const uint8_t kMatrixWidth = 7;
const uint8_t kMatrixHeight = 20;
#define MAX_DIMENSION ((kMatrixWidth>kMatrixHeight) ? kMatrixWidth : kMatrixHeight)
#define NUM_LEDS_ACTIVE = kMatrixWidth * kMatrixHeight

static uint16_t noiseX;  // column
static uint16_t noiseY;  // row
static uint16_t noiseZ;  // time

uint16_t noiseSpeed = 15;
uint16_t scale = 311;  // starting point. Scales up from 1 to about 5K (for distance between pixels)

// This is the array that we keep our computed noise values in
uint8_t noise[MAX_DIMENSION][MAX_DIMENSION];
#endif


void setup() {
  Serial.begin(9600);
  FastLED.addLeds<NEOPIXEL, PIN>(leds, NUM_LEDS);
  initLights();
  randomSeed(analogRead(0));
}

void loop() {

    #ifdef SNOWFLAKE
    snowflakeUpdate();
    #endif

    #ifdef FIRE
    fireUpdate();
    #endif
  
    FastLED.show();
 
 }


void fireUpdate () {

  fillNoise8();
  renderNoise();

  
}

// Fill the x/y array of 8-bit noise values using the inoise8 function.
void fillNoise8() {
  for(int i = 0; i < MAX_DIMENSION; i++) {
    int ioffset = scale * i;
    for(int j = 0; j < MAX_DIMENSION; j++) {
      int joffset = scale * j;
      noise[i][j] = inoise8(noiseX + ioffset,noiseY + joffset,noiseZ);
    }
  }
  noiseZ += noiseSpeed;
}

void renderNoise() {
  for(int i = 0; i < kMatrixWidth; i++) {
    for(int j = 0; j < kMatrixHeight; j++) {
      // We use the value at the (i,j) coordinate in the noise
      // array for our brightness, and the flipped value from (j,i)
      // for our pixel's hue.

      leds[lights[i][j]] = CHSV(noise[j][i],255,noise[i][j]);

      // You can also explore other ways to constrain the hue used, like below
      // leds[XY(i,j)] = CHSV(ihue + (noise[j][i]>>2),255,noise[i][j]);
    }
  }
}


#ifdef SNOWFLAKE
void snowflakeUpdate() {
     
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
#endif
