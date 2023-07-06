#include <Arduino.h>

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

void testInstruction(short instruction);