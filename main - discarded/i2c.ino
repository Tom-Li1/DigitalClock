#include "i2c.h"


void setPin(void)
{
  pinMode(SCL, OUTPUT);
  pinMode(SDA, OUTPUT);
  digitalWrite(SCL, HIGH);
  digitalWrite(SDA, HIGH);
}


void start(void)
{
  digitalWrite(SDA, LOW);
  digitalWrite(SCL, LOW);
}


void stop(void)
{
  digitalWrite(SCL, HIGH);
  digitalWrite(SDA, HIGH);
}


void clockPause(void)
{
  digitalWrite(SCL, HIGH);
  digitalWrite(SCL, LOW);
}


void writeByte(byte data)
{
  byte mask;
  int i;

  for (i = 0; i < 8; i++)
  {
    mask = 0b10000000 >> i;
    if (data & mask)
    {
      digitalWrite(SDA, HIGH);
      clockPause();
      digitalWrite(SDA, LOW);
    }
    else
      clockPause();
  }
  clockPause();
}

