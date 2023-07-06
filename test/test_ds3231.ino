#include <Wire.h>

// device address: 0b1101000

void setup () {
  int result;
  Serial.begin(9600);
  Wire.begin();

  Wire.beginTransmission(0b1101000);
  Wire.write((byte)0b00010001);
  result = Wire.endTransmission(false);
  Serial.print("Set current address: ");
  Serial.println(result);

  Wire.requestFrom(0b1101000, 2, true);
  Serial.print("Temperature data: ");
  while (Wire.available()) {
    Serial.print(Wire.read(), BIN);
    Serial.print(' ');
  };
  Serial.println("");
}

void loop () {
  ;
}