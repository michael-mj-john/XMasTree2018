/*
 * Class designed (eventually) to be used for particles floating up the tree. Never quite got to it.
 */



class SmokeParticle {

    private:
      uint8_t row;
      uint8_t column;
      boolean active;
      uint16_t lastMillis;
      uint16_t animDelay;

    SmokeParticle() {
      row = 9;
      active = false;
      animDelay = 600;
    }

public:
    void setColumn( uint8_t col ) {
      column = col;
      active = true;
      lastMillis = millis();
    }

    bool draw() {
      if( active ) {
         if( millis() - lastMillis > animDelay ) {
             leds[lights[column][row]].setRGB( 50, 50, 50 ); // set it to white
             leds[lights[column][row-1]].setRGB( 0, 0, 0 ); // set trailing pixel to off
             row++;
             lastMillis = millis();
          }
              
          if( row > 19 ) {
            row = 9;
            active = false;
            return false;
          }
          return true;
      }
      return false;     
    }
  
};
