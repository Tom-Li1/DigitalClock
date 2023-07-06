#include <Wire.h>

// device address: 0b1010111 (A0-A2 are not connected and so stand for 1)

void setup() {
  int result;
  Serial.begin(9600);
  Wire.begin();
  
  Serial.println("AT24C32 Byte Write Test");
  Wire.beginTransmission(0b1010111);
  Wire.write(0b00000101); // first word address
  Wire.write(0b01010101); // second word address
  Wire.write(0b00110011); // one byte of data
  result = Wire.endTransmission(true);
  Serial.println("Write Result:");
  Serial.println(result);
  
  Serial.println("AT24C32 Random Read Test");
  Wire.beginTransmission(0b1010111);
  Wire.write(0b00000101); // first word address
  Wire.write(0b01010101); // second word address
  result = Wire.endTransmission(false);
  Serial.println("Provide random read address:");
  Serial.println(result);
  Wire.requestFrom(0b1010111, 1, true);
  Serial.println("Available byte requested:");
  Serial.println(Wire.available());
  Serial.println("Byte Read:");
  while (Wire.available()) {
    Serial.println(Wire.read());
  }
}

void loop() {
  ;
}