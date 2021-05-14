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

// Variabel som håller keypadens status (ändrad eller inte).
// Deklarerad globalt för att vara oändrad mellan anrop av "keyb_alt_ctrl".
char keybstate = 0;

// Returnerar vilka tangeter som är nedtyckta
unsigned short keyb_alt_ctrl(void) 
{
	unsigned short key_status = 0;

	// Läser av varje rad på keypaden och lägger värdet i "key_status" genom att
	// skifta till rätt position.
	for(int row = 0; row < 4; row++) 
	{
		kbd_active(row + 1);
		unsigned short c = (unsigned short)*GPIO_D_IDR_HIGH;
		c &= 0x000F;
		c = c << 4 * (3 - row);
		key_status |= c;
	}
	
	return key_status;
}

void keypad_init(void) 
{
	// Konfigurerar pinnar 15-12 samt 7-0 som utgång, pinnar 11-8 som ingång.
	*GPIO_D_MODER = 0x55005555;
	
	// Säkerställer att input-pinnarna är "pull-up".
	*GPIO_D_PUPDR &= 0xFF00FFFF;
	*GPIO_D_PUPDR |= 0x00550000;
	
	// Sätter utportstypen till "push-pull".
	*GPIO_D_OTYPER &= 0x0F00;
	
	// Sätter frekvensen för utgångsuppdateringen till 2 MHz.
	*GPIO_D_OSPEEDR &= 0x00FF0000;
}