#ifndef DRIVER_ST7920_H
#define DRIVER_ST7920_H


/* Wire Connection for Arduino Nano:
   Display Module - Nano Board
   VCC - 5V
   GND - GND
   RS (CS) - D10 (SPI chip-select)
   R/W (SID) - D11 (SPI master data output) 
   E (SCLK) - D13 (SPI clock)
   PSB - GND (select SPI as communication mode)
   RST - 3V3 (never reset) 
   BLA (backlight LED +) - 5V (some other module needs 3.3v)
   BLK (backlight LED -) - GND */


#include <Arduino.h>


// 8*16 half height non-ascii character (icon) code
#define SMILE_REVERSE 0x01
#define SMILE 0x02
#define HEART 0x03
#define DIAMOND 0x04
#define CLUB 0x05
#define SPADE 0x06
#define DOT 0x07
#define DOT_REVERSE 0x08
#define CIRCLE 0x09
#define CIRCLE_REVERSE 0x0a
#define MALE 0x0b
#define FEMALE 0x0c
#define QUAVER 0x0d
#define QUAVER_DOUBLE 0x0e
#define SUN 0x0f
#define TRIANGLE_RIGHT 0x10
#define TRIANGLE_LEFT 0x11
#define ARROW_UP_DOWN 0x12
#define EXCLAMATION_DOUBLE 0x13
#define PILCROW 0x14
#define SILCROW 0x15
#define UNDERLINE 0x16
#define ARROW_UP_DOWN_UNDERLINE 0x17
#define ARROW_UP 0x18
#define ARROW_DOWN 0x19
#define ARROW_RIGHT 0x1a
#define ARROW_LEFT 0x1b
#define DIVIDE 0x1c
#define ARROW_LEFT_RIGHT 0x1d
#define TRIANGLE_UP 0x1e
#define TRIANGLE_DOWN 0x1f
#define TRIANGLE_UP_HOLLOW 0x7f


void test();

// Initialize the display according to the instructions in the datasheet.
void initialize_ST7920(); 

// Clear all characters and home cursor (reset DDRAM data and address).
void clearCharacterDisplay_ST7920(); 

/* Turn on/off character and cursor display (not backlight)
   option: 'D' - display, 'C' - cursor, 'B' - cursor blink.
   status: true - ON, false - OFF. */
void setDisplayStatus_ST7920(char option, bool status);

/* Print a series of half height 8*16 characters.
   The order is from left to right and from top to bottom.
   chars: An array of chars or half height character code for icons.
   length: number of half characters in array.
   row (0-3): The row number (vertical position) of the first character.
   column (0-15): The column number (horizontal position) of the first character. */
void printHalfCharacters(char chars[], char length, char row, char column);

/* Print a series of 16*16 Chinese/Japanese/Korean characters.
   The order is from left to right and from top to bottom.
   chars: An array of GB codes of your characters.
   length: number of character codes in the array.
   row (0-3): The row number (vertical position) of the first character.
   column (0-7): The column number (horizontal position) of the first character. */
void printFullCharacters_ST7920(short chars[], byte length, byte row, byte column);

#endif