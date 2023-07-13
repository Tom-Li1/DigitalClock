#include <Arduino.h>
#include <SPI.h>
#include "driver_st7920.h"


volatile static char instructionSet_ST7920 = 'B'; // Current instruction set: 'B' - basic, 'E' - extended.
volatile static bool displayStatus_ST7920 = true; // true - display ON, false - display OFF. (irrelevant to backlight)
volatile static bool underlineCursorStatus_ST7920 = true; // true - show underline cursor, false - hide underline cursor.
volatile static bool blinkCursorStatus_ST7920 = true; // true - show blink cursor, false - hide blink cursor.


/* Instruction structure is same to that in datasheet:
   0b RS RW DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0.
   Bits are reordered and transferred according to transaction rule:
   (byte 1) 1 1 1 1 RW RS 0;
   (byte 2) DB7 DB6 DB5 DB4 0 0 0 0;
   (byte 3) DB3 DB2 DB1 DB0 0 0 0 0. */
static void sendInstruction_ST7920(short instruction) {
  SPI.transfer((instruction >> 8 & 0b0000000010) |
               (instruction >> 6 & 0b0000000100) | 0b11111000);
  SPI.transfer(instruction & 0b0011110000);
  SPI.transfer(instruction << 4 & 0b0011110000);
  delayMicroseconds(80);
}


/* Provide 'E' to select "extended instruction" set.
   Provide 'B' to select "basic instruction" set.
   Avoid choosing same instruction set repeatly to save time. */
static void chooseInstructionSet_ST7920(char choice) {
  if (choice == 'E' and instructionSet_ST7920 == 'B') {
    instructionSet_ST7920 = 'E';
    sendInstruction_ST7920(0b0000110100);
  } else if (choice == 'B' and instructionSet_ST7920 == 'E') {
    instructionSet_ST7920 = 'B';
    sendInstruction_ST7920(0b0000110000);
  }
}


/* mode = 'C': cursor moves after writing a character
   mode = 'D': display shifts after writing a character
   direction = 'L': cursor or display moves left
   direction = 'R': cursor or display moves right */
static void setEntryMode_ST7920(char mode, char direction) {
  if (mode == 'C' and direction == 'R') sendInstruction_ST7920(0b0000000110);
  else if (mode == 'C' and direction == 'L') sendInstruction_ST7920(0b0000000100);
  else if (mode == 'D' and direction == 'R') sendInstruction_ST7920(0b0000000101);
  else if (mode == 'D' and direction == 'L') sendInstruction_ST7920(0b0000000111);
}


/* direction = 'R': move cursor right by one, address counter += 1.
   direction = 'L': move cursor left by one, address counter -= 1. */
static void moveCursor_ST7920(char direction) {
  chooseInstructionSet_ST7920('B');
  if (direction == 'R') sendInstruction_ST7920(0b0000010100);
  else if (direction == 'L') sendInstruction_ST7920(0b0000010000);
}


/* direction = 'R': Shift entire display content right by one.
   direction = 'L': Shift entire display content left by one.
   Shift of content is achieved by changing pixel mapping offset of LCD driver.
   Data in DDRAM and address counter remains unchanged. */
static void shiftDisplay_ST7920(char direction) {
  chooseInstructionSet_ST7920('B');
  if (direction == 'R') sendInstruction_ST7920(0b0000011100);
  else if (direction == 'L') sendInstruction_ST7920(0b0000011000);
}


/* Only move cursor to home without changing data in DDRAM. */
static void homeCursor_ST7920() {
  chooseInstructionSet_ST7920('B');
  sendInstruction_ST7920(0b0000000010);
}


/* Initialize the display according to the instructions in the datasheet. */
void initialize_ST7920() {
  // Activate and config SPI communication.
  SPI.begin();
  SPI.beginTransaction(SPISettings(600000, MSBFIRST, SPI_MODE3));

  // Choose basic function set.
  instructionSet_ST7920 = 'B';
  sendInstruction_ST7920(0b0000110000);
  delayMicroseconds(20);

  // set display status according to global variables defined at the beginning.
  short displayControl = 0b0000001000;
  if (displayStatus_ST7920) displayControl |=  0b0000000100;
  if (underlineCursorStatus_ST7920) displayControl |= 0b0000000010;
  if (blinkCursorStatus_ST7920) displayControl |= 0b0000000001;
  sendInstruction_ST7920(displayControl);
  delayMicroseconds(20);

  // Clear display content.
  sendInstruction_ST7920(0b0000000001);
  delay(10);

  // set entry mode: cursor moves right
  sendInstruction_ST7920(0b0000000110);
}


/* Fill DDRAM with space (clear half height and full sized characters).
   Move cursor to home (left end of the first line) by setting address counter to 0x00. */
void clearCharacterDisplay_ST7920() {
  chooseInstructionSet_ST7920('B');
  sendInstruction_ST7920(0b0000000001);
  delay(2);
}


/* option: 'D' - display, 'C' - cursor, 'B' - cursor blink.
   status: true - ON, false - OFF. */ 
void setDisplayStatus_ST7920(char option, bool status) {
  short instruction = 0b0000001000;
  chooseInstructionSet_ST7920('B');
  switch (option) {
    case 'D':
      displayStatus_ST7920 = status;
      break;
    case 'C':
      underlineCursorStatus_ST7920 = status;
      break;
    case 'B':
      blinkCursorStatus_ST7920 = status;
      break;
  }
  if (displayStatus_ST7920) instruction |=  0b0000000100;
  if (underlineCursorStatus_ST7920) instruction |= 0b0000000010;
  if (blinkCursorStatus_ST7920) instruction |= 0b0000000001;
  sendInstruction_ST7920(instruction);
}


void printHalfCharacters();


void printFullCharacters();


void test() {
  initialize_ST7920();

  sendInstruction_ST7920(0b1010100100);
  sendInstruction_ST7920(0b1011001010);
  delay(1000);

  sendInstruction_ST7920(0b1010100100);
  sendInstruction_ST7920(0b1011001110);
  delay(1000);

  setEntryMode_ST7920('C', 'L');

  sendInstruction_ST7920(0b1010100100);
  sendInstruction_ST7920(0b1011001111);
  delay(1000);

  sendInstruction_ST7920(0b1010100100);
  sendInstruction_ST7920(0b1010001111);
  delay(1000);

  setEntryMode_ST7920('C', 'R');

  sendInstruction_ST7920(0b1010111010);
  sendInstruction_ST7920(0b1010111010);
  delay(1000);

  sendInstruction_ST7920(0b1011010111);
  sendInstruction_ST7920(0b1011010110);
  delay(1000);

  sendInstruction_ST7920(0b1011001111);
  sendInstruction_ST7920(0b1011010100);
  delay(1000);

  sendInstruction_ST7920(0b1011001010);
  sendInstruction_ST7920(0b1010111110);
  delay(1000);

  homeCursor_ST7920();
  delay(1000);

  setDisplayStatus_ST7920('C', false);
  setDisplayStatus_ST7920('B', false);

  // problematic for loop
  for (int i = 0; i < 8; i++) {
    shiftDisplay_ST7920('R');
    delay(500);
  }
  for (int i = 0; i < 8; i++) {
    shiftDisplay_ST7920('L');
    delay(500);
  }

  
  for (int i = 0; i < 8; i++) {
    moveCursor_ST7920('R');
    delay(500);
  }
  for (int i = 0; i < 8; i++) {
    moveCursor_ST7920('L');
    delay(500);
  }
  
  setDisplayStatus_ST7920('D', false);
  delay(1000);
  setDisplayStatus_ST7920('D', true);
  delay(1000);

  setDisplayStatus_ST7920('B', false);
  delay(1000);
  setDisplayStatus_ST7920('B', true);
  delay(1000);

  setDisplayStatus_ST7920('C', false);
  delay(1000);
  setDisplayStatus_ST7920('C', true);
  delay(1000);

  clearCharacterDisplay_ST7920();
  delay(1000);
}

/* DDRAM address is used to locate the character going to be shown.
   Hence it can also be understood as "cursor".
   6 bits (A5-A0) are used to express DDRAM address, so the range is 0-63 (0b000000 - 0b111111). 
   
   ST7920 is designed for 256*64 display.
   However this driver is programmed for 128*64 display with ST7920.
   
   DDRAM address and corresponding cursor position for 256*64 display:
   Line 0: [00] [01] [02] [03] [04] [05] [06] [07] [08] [09] [10] [11] [12] [13] [14] [15]
   Line 1: ...
   ......: ...
   Line 4: [48] [49] [50] [51] [52] [53] [54] [55] [56] [57] [58] [59] [60] [61] [62] [63]

   That for 128*64 display (*be careful its very weird* blame the pcb designer):
   Line 0: [00] [01] [02] [03] [04] [05] [06] [07] (first 8 chars of line 0)
   Line 1: [16] [17] [18] [19] [20] [21] [22] [23] (first 8 chars of line 1)
   Line 2: [08] [09] [10] [11] [12] [13] [14] [15] (latter 8 chars of line 0)
   Line 3: [24] [25] [26] [27] [28] [29] [30] [31] (latter 8 chars of line 1) 
   
   Address counter of DDRAM will be added / subtracted by 1 within the range 0-63,
   but 32-63 is not shown on 128*64. */
