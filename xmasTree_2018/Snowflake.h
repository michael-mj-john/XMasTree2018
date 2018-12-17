#include "lightHash.h";


class Snowflake {
  private:
    int8_t row;
    uint8_t column;
    int animDelay; // milliseconds before it moves on
    uint16_t lastMillis;

  public:
    struct Snowflake *next;

  Snowflake(Snowflake *headPtr) {
    row = 19;
    column = random(0,6);
    next = headPtr;
    animDelay = 300;
  }

  boolean setColor() {
    if( millis() - lastMillis > animDelay ) {
       leds[lights[column][row]].setRGB( 50, 50, 50 ); // set it to white
       leds[lights[column][row+1]].setRGB( 0, 0, 50 ); // set trailing pixel to blue
       row--;
       lastMillis = millis();
    }
    if( row == -1 ) {
       leds[lights[column][row+1]].setRGB( 0, 0, 50 ); // set final pixel to blue
       return true;
    }
    return false;
  }

  
};
