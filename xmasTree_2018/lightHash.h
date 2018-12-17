#pragma once

// stores lights in row/column array. Hashes row/column to light index
// taking into account vertical swaps and also masked lights @ bottom
// of the tree

#define ROWS 20
#define COLUMNS 7
#define NUM_LEDS 150


CRGB leds[NUM_LEDS];


uint8_t lights[COLUMNS][ROWS];

void initLights() { 
  int lightIndex = 0;
  int currentJump = 0;
 
  for( int i=0; i<COLUMNS; i++ ) {
    if( i % 2 == 0 ) { //even numbered column
      for( int j=0; j<ROWS; j++ ) {
        lights[i][j] = lightIndex + currentJump;
        lightIndex++; 
      }
    }
    else {  //odd numbered column, has to count down
      lightIndex += ROWS-1;
      for( int j=0; j<ROWS; j++ ) {
        lights[i][j] = lightIndex + currentJump;
        lightIndex--; 
      }
      lightIndex += ROWS+1;      
    }
    // accommodate the lights that should be masked out at the bottom of the tree
    if( lightIndex - currentJump == 40 ) { currentJump += 6; }
    if( lightIndex - currentJump == 80 ) { currentJump += 4; }
    if( lightIndex - currentJump == 120 ) { currentJump += 4; }
  }
  
}
