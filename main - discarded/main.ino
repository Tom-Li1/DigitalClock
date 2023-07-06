#include "i2c.h"

void setup() {
  // put your setup code here, to run once:
  setPin();
  start();
  writeByte(0b01001000);
  writeByte(0b00000001);
  stop();
}

void loop() {
  // put your main code here, to run repeatedly:
  int i, j;
  byte digits[4] = {0b01101000, 0b01101010, 0b01101100, 0b01101110};

  for (i = 0b00000000; i <= 0b11111111; i++)
  {
    for (j = 0; j < 4; j++)
    {
      start();
      writeByte(digits[j]);
      writeByte(i);
      stop();
    }
    delay(100);
  }
}
