#include <SPI.h>

// According to datasheet of display (not ST7920), SCLK is idle when high.
// Hence CPOL aka clock polarity is 1.

// Data at SID is captured when SCLK rises.
// So CPHA aka clock phase is also 1.

// https://docs.arduino.cc/learn/communication/spi?_gl=1*s42wob*_ga*NDU5MTM3NDU3LjE2ODczNzMzMzM.*_ga_NEXN8H46L5*MTY4ODQwNTc3MS4xNC4xLjE2ODg0MDU5ODcuMC4wLjA.
// Therefore, the corresponding SPI mode is SPI_MODE3.
// Since most significant bit first, use MSBFIRST.

// For ST7920, clock pulse width high/low is 800 ns.
// Hence one clock period is 800 * 2 = 1600 ns = 0.0000016 s.
// The maximum frequency for SPI is then 1 / 0.0000016 = 625000 Hz

// For ST7920, only write data is available in SPI mode.
// There is no internal buffer area in ST7920, send next command/data after the previous one is processed.
// Timing Diagram of Serial Mode Data Transfer are available in datasheet of ST7920.

void setup() {
  SPI.begin();
  SPI.beginTransaction(SPISettings(600000, MSBFIRST, SPI_MODE3));

  // 0b 1 1 1 1 1 R/W RS 0 + 0b D7 D6 D5 D4 0 0 0 0 + 0b D3 D2 D1 D0 0 0 0 0

  // function set: basic instructions
  SPI.transfer((byte)0b11111000);
  SPI.transfer((byte)0b00110000);
  SPI.transfer((byte)0b00000000);
  delay(100);

  // display ON
  SPI.transfer((byte)0b11111000);
  SPI.transfer((byte)0b00000000);
  SPI.transfer((byte)0b11110000);
  delay(100);

  // display clear
  SPI.transfer((byte)0b11111000);
  SPI.transfer((byte)0b00000000);
  SPI.transfer((byte)0b00010000);
  delay(100);

  // entry mode: cursor moves right
  SPI.transfer((byte)0b11111000);
  SPI.transfer((byte)0b00000000);
  SPI.transfer((byte)0b01100000);
  delay(100);

  //set home
  SPI.transfer((byte)0b11111000);
  SPI.transfer((byte)0b00000000);
  SPI.transfer((byte)0b00100000);
  delay(100);

  // set DDRAM address to 0x00
  SPI.transfer((byte)0b11111000);
  SPI.transfer((byte)0b10000000);
  SPI.transfer((byte)0b00000000);
  delay(100);

  // write DDRAM 段
  SPI.transfer((byte)0b11111010);
  SPI.transfer((byte)0b10110000);
  SPI.transfer((byte)0b01100000);
  delay(100);
  // write DDRAM again
  SPI.transfer((byte)0b11111010);
  SPI.transfer((byte)0b11000000);
  SPI.transfer((byte)0b11100000);
  delay(100);

  // write DDRAM 子
  SPI.transfer((byte)0b11111010);
  SPI.transfer((byte)0b11010000);
  SPI.transfer((byte)0b01110000);
  delay(100);
  // write DDRAM again
  SPI.transfer((byte)0b11111010);
  SPI.transfer((byte)0b11010000);
  SPI.transfer((byte)0b00110000);
  delay(100);

  // write DDRAM 杰
  SPI.transfer((byte)0b11111010);
  SPI.transfer((byte)0b10110000);
  SPI.transfer((byte)0b11010000);
  delay(100);
  // write DDRAM again
  SPI.transfer((byte)0b11111010);
  SPI.transfer((byte)0b11010000);
  SPI.transfer((byte)0b11000000);
  delay(100);

  // write DDRAM 是
  SPI.transfer((byte)0b11111010);
  SPI.transfer((byte)0b11000000);
  SPI.transfer((byte)0b10100000);
  delay(100);
  // write DDRAM again
  SPI.transfer((byte)0b11111010);
  SPI.transfer((byte)0b11000000);
  SPI.transfer((byte)0b01110000);
  delay(100);

  // write DDRAM 大
  SPI.transfer((byte)0b11111010);
  SPI.transfer((byte)0b10110000);
  SPI.transfer((byte)0b01000000);
  delay(100);
  // write DDRAM again
  SPI.transfer((byte)0b11111010);
  SPI.transfer((byte)0b11110000);
  SPI.transfer((byte)0b00110000);
  delay(100);

  // write DDRAM 牛
  SPI.transfer((byte)0b11111010);
  SPI.transfer((byte)0b11000000);
  SPI.transfer((byte)0b01010000);
  delay(100);
  // write DDRAM again
  SPI.transfer((byte)0b11111010);
  SPI.transfer((byte)0b10100000);
  SPI.transfer((byte)0b00110000);
  delay(100);

  // write DDRAM 逼
  SPI.transfer((byte)0b11111010);
  SPI.transfer((byte)0b10110000);
  SPI.transfer((byte)0b00010000);
  delay(100);
  // write DDRAM again
  SPI.transfer((byte)0b11111010);
  SPI.transfer((byte)0b11000000);
  SPI.transfer((byte)0b01100000);
  delay(100);

  // write DDRAM ！
  SPI.transfer((byte)0b11111010);
  SPI.transfer((byte)0b10100000);
  SPI.transfer((byte)0b00110000);
  delay(100);
  // write DDRAM again
  SPI.transfer((byte)0b11111010);
  SPI.transfer((byte)0b10100000);
  SPI.transfer((byte)0b00010000);
  delay(100);
}

void loop() {
  SPI.transfer((byte)0b11111000);
  SPI.transfer((byte)0b00010000);
  SPI.transfer((byte)0b11000000);
  delay(500);
}