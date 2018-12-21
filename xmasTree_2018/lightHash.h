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
         Serial.print( i );Serial.print(" "); Serial.print( j );Serial.print(" "); Serial.print( lightIndex ); Serial.print(" ");
       lights[i][j] = lightIndex+currentJump;
         Serial.print( lights[i][j] ); Serial.print( "\n" );
       lightIndex--; 
      }
      lightIndex += ROWS+1;      
    }
    
    // accommodate the lights that should be masked out at the bottom of the tree
    if( lightIndex == 40 ) { currentJump+=3; }
    if( lightIndex == 80 ) { currentJump += 3; }
    if( lightIndex == 120 ) { currentJump += 3; }
  }
  
}
