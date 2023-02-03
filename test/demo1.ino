/* 未使用终端和计时器 用按钮控制LED 模拟 双稳态开关 */

const byte ledPin = 13;
const byte buttonPin = 2;

volatile bool toggleState = false;

void checkSwitch() {
  if (digitalRead(buttonPin) == LOW)
  {
    delay(200);
    toggleState = !toggleState;
    digitalWrite(ledPin, toggleState);
  }
}

void setup()
{
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop()
{
  checkSwitch();
}