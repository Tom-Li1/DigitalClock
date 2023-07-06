#include <SPI.h>
#include "driver_st7920.h"

void setup () {
  Serial.begin(9600);


  SPI.begin();
  SPI.beginTransaction(SPISettings(600000, MSBFIRST, SPI_MODE3));

  testInstruction(0b0000110000); // basic function set
  testInstruction(0b0000001111); // display on, cursor on, cursor blink on
  testInstruction(0b0000000001); // display clear
  testInstruction(0b0000000110); // cursor moves right
  testInstruction(0b0000000010); // set cursor to home

  // play with DDRAM address
  delay(1000);
  testInstruction(0b0010000001);
  delay(1000);
  testInstruction(0b0010001000);
  delay(1000);
  testInstruction(0b0010010000);

  testInstruction(0b0010000000);
}

void loop () {
  testInstruction(0b1000001011);
  testInstruction(0b1000001011);
}