
const uint8_t kMatrixWidth = 7;
const uint8_t kMatrixHeight = 20;
#define MAX_DIMENSION ((kMatrixWidth>kMatrixHeight) ? kMatrixWidth : kMatrixHeight)
#define NUM_LEDS_ACTIVE = kMatrixWidth * kMatrixHeight

static uint16_t noiseX;  // column
static uint16_t noiseY;  // row
static uint16_t noiseZ;  // time

uint16_t noiseSpeed = 20;
uint16_t scale = 311;  // starting point. Scales up from 1 to about 5K (for distance between pixels)

// This is the array that we keep our computed noise values in
uint8_t noise[MAX_DIMENSION][MAX_DIMENSION];


// Fill the x/y array of 8-bit noise values using the inoise8 function.
void fillnoise8() {
  for(int i = 0; i < MAX_DIMENSION; i++) {
    int ioffset = scale * i;
    for(int j = 0; j < MAX_DIMENSION; j++) {
      int joffset = scale * j;
      noise[i][j] = inoise8(noiseX + ioffset,noiseY + joffset,noiseZ);
    }
  }
  noiseZ += noiseSpeed;
}

uint16_t XY( uint8_t x, uint8_t y)
{
  uint16_t i;
  i = (y * kMatrixWidth) + x;

  return i;
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
