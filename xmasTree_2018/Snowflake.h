#include "lightHash.h";


class Snowflake {
  private:
    int8_t row;
    uint8_t column;
    int animDelay; // milliseconds before it moves on
    uint32_t lastMillis;

  public:
    struct Snowflake *next;

  Snowflake() {
    row = 19;
    column = random(0,6);
    next = NULL;
    animDelay = 100;
  }

  boolean setColor() {
    if( millis() - lastMillis > animDelay ) {
       leds[lights[column][row]].setRGB( 50, 50, 50 ); // set it to white
       leds[lights[column][row+1]].setRGB( 0, 0, 50 ); // set trailing pixel to blue
       row--;
       lastMillis = millis();
    }
    if( row < 0 ) {
       leds[lights[column][row+1]].setRGB( 0, 0, 50 ); // set final pixel to blue
       return true;
       Serial.println( "returned true" );
    }
    return false;
    Serial.println( "returned false" );
  }

  
};
