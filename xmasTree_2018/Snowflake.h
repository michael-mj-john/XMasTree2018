
struct Snowflake {
  bool isActive;
  uint8_t row;
  uint8_t column;
  int waitMillis; // milliseconds before it moves on

  Snowflake(uint8_t col) {
    row = 19;
    column = col;
  }
};
