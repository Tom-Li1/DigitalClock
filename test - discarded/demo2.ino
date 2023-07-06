/* 未使用终端和计时器 用按钮控制LED 模拟 双稳态开关 
   用较低的检测频率 说明该方式的劣势 即有可能错过一些输入 */

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
  Serial.begin(9600);
}

void loop()
{
  checkSwitch();

  // 减低检测频率 观测效果
  Serial.println("Delay Started");
  delay(5000);
  Serial.println("Delay Finished");
  Serial.println("..............");
}