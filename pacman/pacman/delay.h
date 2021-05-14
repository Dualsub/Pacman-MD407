#ifndef DELAY_H
#define DELAY_H
 
 // Definitioner för SysTick och dess register.
 #define STK		0xE000E010
 #define STK_CTRL 	((unsigned int*) STK)
 #define STK_LOAD	((unsigned int*)(STK + 0x4))
 #define STK_VAL	((unsigned int*)(STK + 0x8))
 #define STK_CALIB	((unsigned int*)(STK + 0x0C))

void delay_250ns();
void delay_milli(unsigned int ms);
void delay_mikro(unsigned int us);

#endif