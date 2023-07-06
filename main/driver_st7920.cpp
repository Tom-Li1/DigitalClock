#include <Arduino.h>
#include <SPI.h>
#include "driver_st7920.h"

/* Instruction structure is same to that in datasheet:
   0b RS RW DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0.
   Bits of instruction above are rearranged and to the form shown in
   timing diagram of serial mode data transfer in datasheet and then transferred to ST7920.
   Internal function for this driver program, won't be called externally. */
static void sendInstructionToST7920(short instruction) {
  SPI.transfer((instruction >> 8 & 0b0000000010) |
               (instruction >> 6 & 0b0000000100) | 0b11111000);
  SPI.transfer(instruction & 0b0011110000);
  SPI.transfer(instruction << 4 & 0b0011110000);
}


/* Provide 'E' to select "extended instruction" set.
   Provide 'B' to select "basic instruction" set.
   Internal function for this driver program, won't be called externally. */
static void choseInstructionSet(char instructionSet) {
  if (instructionSet == 'E') {
    sendInstructionToST7920(0b0000110100);
  } else if (instructionSet == 'B') {
    sendInstructionToST7920(0b0000110000);
  }
}


void testInstruction(short instruction) {
  sendInstructionToST7920(instruction);
  delay(100);
}


