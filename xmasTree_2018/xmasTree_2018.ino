/* MJ's holiday xmas tree lights 2018 
 *  MIT license open source
 */

#include <FastLED.h>
#include "lightHash.h"
  
#define PIN 7
#define FLAKEMAX 50
#define FIRE true

  
// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

#ifdef SNOWFLAKE
#include "Snowflake.h"
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
//boolean smokeFlag[7] = {0};
//SmokeParticle* particle[7] = {}; 

uint16_t noiseSpeed = 10;
uint16_t scale = 31;  // starting point. Scales up from 1 to about 5K (for distance between pixels)

// This is the array that we keep our computed noise values in
uint8_t noise[MAX_DIMENSION][MAX_DIMENSION];
#endif


void setup() {
  Serial.begin(9600);
  FastLED.addLeds<WS2811, PIN, RGB>(leds, NUM_LEDS);
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

#ifdef FIRE
void fireUpdate () {

  fillNoise8();
  renderNoise();
//  renderSmoke();

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
      // for pixel's saturation.
      uint8_t sat = map(noise[j][i], 0,255, 190, 255);
      uint8_t bri = map(noise[i][j], 0,255, 100, 200);

      uint8_t hueMin, hueMax;
      if( j < 8 ) { hueMin = 4; hueMax = 10; }
      else if( j < 15 ) { hueMin = 12, hueMax = 16; }
      else { hueMin = 18; hueMax = 22; }
      uint8_t hue = map(noise[i][j], 0,255, hueMin,hueMax);
    
      if( j < 17 ) {
        leds[lights[i][j]] = CHSV(hue,sat,max(noise[i][j], 0));
      }
      else {
        leds[lights[i][j]] = CHSV(hue,sat,(noise[i][j]-(j*3)));
      }

//      if( j == 7 && sat > 250 && !smokeFlag[i] ) {
//        spawnSmoke(i);
//      }

    }
  }
}
/*
void renderSmoke() {

  for( int i=0; i<COLUMNS; i++ ) {
      if( !particle[i]->draw() ) {
        smokeFlag[i] = false;
      }   
  }
  
}


void spawnSmoke( uint8_t column ) {

    particle[column]->setColumn(column);
    smokeFlag[column] = true;
}
*/

#endif

#ifdef SNOWFLAKE

void addFlake( void );
void updateFlakes( void );

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
        addFlake();
        lastSpawn = millis();
      }

     updateFlakes();

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

void addFlake( void ) {  
      //iterate the fixed-length array to look for a free flake slot
      for( uint8_t i=0; i<FLAKEMAX; i++ ) {
          if( snowflakes[i].row < 0 ) {
            snowflakes[i].init();
            return;
          }
        }
}
#endif
