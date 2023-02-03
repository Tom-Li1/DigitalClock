// 使用外部终端 在指定引脚电平变化时 插入执行某函数
// 需要注意当前开发板的哪些Pin能够接受外部中断信号

/* ISR - Interrupt Serivce Routine
   1. 收到中断时 执行一个函数
   2. 程序停止运行 跳转执行ISR的函数
   3. ISR的函数结束后 程序从中断处继续执行
   4. ISR的函数最好不花费太多时间
   5. ISR函数中不可使用delay() Serial Millis等函数和方法
   6. ISR使用的变量必须为全局变量
   7. 使用 volatile 类型限定符修饰ISR用到的变量
      指明变量的易变性 防止编译器错误地使用高速缓存优化
   8. 同时间点内 只能执行一个ISR的函数
   9. 多个ISR触发 按优先级执行函数 */

/* attachInterrupt(InterruptVector, ISR, Mode)
   InterruptVector: 指明中断信号来源的编号
                    使用Pin触发中断时 可能不等于Pin编号
   ISR: 中断所触发的函数
   Mode: RISING FALLING LOW CHANGE (HIGH)
         指明Pin在哪种电平变化时触发中断 */

/* digitalPinToInterrupt(PinNumber)
   传入想要当作中断信号检测的Pin的编号
   函数返回它的中断来源编号
   作为attachInterrupt()的InterruptVector参数
   attachInterrupt(digitalPinToInterrupt(pin), ISR, Mode)*/


const byte ledPin = 13;
const byte buttonPin = 2;

volatile bool toggleState = false;

void checkSwitch() {
  // ISR函数
  if (digitalRead(buttonPin) == LOW)
  {
    toggleState = !toggleState;
    digitalWrite(ledPin, toggleState);
  }
}

void setup()
{
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);
  attachInterrupt(
    digitalPinToInterrupt(buttonPin),
    checkSwitch,
    FALLING);
  // GPIO2电平下降时 跳转执行checkSwitch()
  // 读取GPIO2电平 如果低 切换LED状态
}

void loop()
{
  // 减低检测频率 观测效果
  Serial.println("Delay Started");
  delay(5000);
  Serial.println("Delay Finished");
  Serial.println("..............");
}