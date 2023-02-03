// UNO的每个I/O引脚都支持PinChangeInterrupts
// ATMega328有24个PCI引脚
// UNO提供20个可用的PCI引脚
// PCI模式的触发 只能使用CHANGE模式 即电平跳变时触发
// 引脚根据ports进行了分组
// 同一个port的引脚 公用同一个PCI

/* PORT B
   PIN 8-13
   PORT PB0-PB5
   PCINT PCINT0-PCINT5

   PORT C
   PIN 0-5
   PORT PC0-PC5
   PCINT PCINT8-PCINT13

   PORT D
   PIN 0-7
   PORT PD0-PD7
   PCINT PCINT16-23 */

/* 1. Enable/Disable PCINT
      Pin Change Interrupt Control Register PCICR
      Bit 2 - Port D
      Bit 1 - Port C
      Bit 0 - Port B

  2. Enable/Disable Pin(s)
     
     Port B - Pin Change Mask 0 (PMSK0)
     Bit 7 - PCINT 7 (XTAL 2)
     Bit 6 - PCINT 6 (XTAL 1)
     Bit 5-0 - PCINT 5-0

     Port C - Pin Change Mask 1 (PMSK1)
     Bit 7 - PCINT15
     Bit 6 - PCINT14 (RESET)
     Bit 5-0 - PCINT 13-8

     Port D - Pin Change Mask 2 (PMSK2)
     Bit 7-0 - PCINT 23-16
  
  3. Define ISR
     ISR(PCINT0_vect) - ISR for Port B (D8-13)
     ISR(PCINT1_vect) - ISR for Port C (A0-5)
     ISR(PCINT2_vect) - ISR for Port D (D0-7)

/* PCICR |= B00000001; // Enable PCI port B
   PCMSK0 |= B00010000; // Enable Pin 12
   ISR(PCINT0_vect) // Define ISR for Port B */

/* Pin Change Interrupt Flag Register PCIFR
   Bit 2 - PCIF 2 - Port D
   Bit 1 - PCIF 1 - Port C
   Bit 0 - PCIF 0 - Port B
   对应Port的Pin有变化时 寄存器被激活
   通过对指定位写1 重设寄存器
   如果Port与ISR绑定 该寄存器会被自动重设

// PCI只能使用CHANGE模式 每次按钮输入会导致两次触发
// 同一个PORT可能有多个中断事件
// 通过设置变量保存上一次Pin的变化方向 判断下一次Pin的变化
// 比较不同的中断去判断哪个Pin的电平发生变化

    
      














