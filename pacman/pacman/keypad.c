#include "keypad.h"

void kbd_active(unsigned int row) 
{
	switch(row)
	{
		case 1:
			*GPIO_D_ODR_HIGH = 0x10;
			break;
		case 2:
			*GPIO_D_ODR_HIGH = 0x20;
			break;
		case 3:
			*GPIO_D_ODR_HIGH = 0x40;
			break;
		case 4:
			*GPIO_D_ODR_HIGH = 0x80;
			break;
		case 5:
			*GPIO_D_ODR_HIGH = 0xF0;
			break;
		default:
			*GPIO_D_ODR_HIGH = 0;
			break;
	}
}

int kbd_get_col(void) 
{
	unsigned char c;
	c = *GPIO_D_IDR_HIGH;
	
	if(c & 8) 
	{
		return 4;
	}
	
	if(c & 4) 
	{
		return 3;
	}
	
	if(c & 2) 
	{
		return 2;
	}
	
	if(c & 1) 
	{
		return 1;
	}
	
	return 0;
}

unsigned char keyb(void) 
{
	char key[] = { 1,2,3,0xA,4,5,6,0xB,7,8,9,0xC,0xE,0,0xF,0xD };
	int row, col;
	for(row = 1; row <= 4; row++) 
	{
		kbd_active(row);
		if(col = kbd_get_col()) 
		{
			kbd_active(0);
			return key[4*(row-1)+(col-1)];
		}
	}
	
	return 0xFF;
}

void keypad_init(void) 
{
	// Konfigurerar pinnar 15-12 och pinnar 11-8 som ingång.
	*GPIO_D_MODER &= ~0x55FF0000;
    *GPIO_D_MODER |= 0x55000000;
	
	// Säkerställer att input-pinnarna är "pull-up".
	*GPIO_D_PUPDR &= 0xFF00FFFF;
	*GPIO_D_PUPDR |= 0x00550000;
	
	// Sätter utportstypen till "push-pull".
	*GPIO_D_OTYPER &= 0x0FFF;
	
	// Sätter frekvensen för utgångsuppdateringen till 2 MHz.
	*GPIO_D_OSPEEDR &= 0x00FFFFFF;
}