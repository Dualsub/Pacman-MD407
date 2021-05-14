#include "delay.h"

// Angivet på föreläsning.
void delay_250ns() 
{
	*STK_CTRL = 0;
	*STK_LOAD = 168 / 4 - 1;
	*STK_VAL = 0;
	*STK_CTRL = 5;
	while((*STK_CTRL & 0x10000) == 0);
	*STK_CTRL = 0;
}

// Väntar 4000 st 250 ns perioder per angiven millisekund. Om simulatorn används väntas 1/1000 av tiden.
void delay_milli(unsigned int ms) 
{
	#ifdef SIMULATOR
	ms /= 1000;
	ms++;
	#endif
	for(int i = 0; i < 4000 * ms; i++) { delay_250ns(); }
}

// Väntar 4 st 250 ns perioder per angiven mikrosekund. Om simulatorn används väntas 1/1000 av tiden.
void delay_mikro(unsigned int us) 
{
	#ifdef SIMULATOR
	us /= 1000;
	us++;
	#endif
	for(int i = 0; i < 4 * us; i++) { delay_250ns(); }
}