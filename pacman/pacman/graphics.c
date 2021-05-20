#include "graphics.h"

// Drivrutiner för display. Givna i boken.
__attribute__((naked))
void graphics_initalize ( void )
{
__asm__ volatile(" .HWORD 0xDFF0\n");
__asm__ volatile(" BX LR\n");
}

__attribute__((naked))
void graphics_clear_screen ( void )
{
__asm__ volatile(" .HWORD 0xDFF1\n");
__asm__ volatile(" BX LR\n");
}

__attribute__((naked))
void graphics_pixel_set ( int x, int y )
{
__asm__ volatile(" .HWORD 0xDFF2\n");
__asm__ volatile(" BX LR\n");
}

__attribute__((naked))
void graphics_pixel_clear ( int x, int y )
{
__asm__ volatile(" .HWORD 0xDFF3\n");
__asm__ volatile(" BX LR\n");
}

// Skriver angivet tecken till displayen.
void ascii_write_char(unsigned char c)
{
	while((ascii_read_status() & 0x80) == 0x80);
	delay_mikro(8);
	ascii_write_data(c);
	delay_mikro(60);
}

// Ställer markören vid angiven position (rad, kollumn).
void ascii_gotoxy(int x, int y)
{
	char addr = x - 1;
	if(y == 2) 
	{
		addr += 0x40;
	}
	ascii_write_cmd(0x80 | addr);
}

void ascii_init() 
{
	// Väntar tills displayen är redo att ta emot kommando.
	// Sätter FunctionSet till 5x8 punkters tecken samt antalet till 2.
	while((ascii_read_status() & 0x80) == 0x80);
	delay_mikro(8);
	ascii_write_cmd(0x38);
	delay_mikro(50);

	// Väntar tills displayen är redo att ta emot kommando.
	// Sätter DisplaySet till tänd display och tänd markör med konstant visning.
	while((ascii_read_status() & 0x80) == 0x80);
	delay_mikro(8);
	ascii_write_cmd(0xE);
	delay_mikro(50);

	// Väntar tills displayen är redo att ta emot kommando.
	// Sätter EntryModeSet till "increment" och inget skift av adressbufferten.
	while((ascii_read_status() & 0x80) == 0x80);
	delay_mikro(8);
	ascii_write_cmd(0x6);
	delay_mikro(50);
}

// Angiven på föreläsing.
void ascii_write_controller(unsigned char c) 
{
	ascii_ctrl_bit_set(B_E);
	*GPIO_E_ODR_HIGH = c;
	ascii_ctrl_bit_clear(B_E);
	delay_250ns();
}

// Angiven på föreläsing.
unsigned char ascii_read_controller() 
{
	char c;
	ascii_ctrl_bit_set(B_E);
	
	delay_250ns();
	delay_250ns();
	
	c = *GPIO_E_IDR_HIGH;
	ascii_ctrl_bit_clear(B_E);
	
	return c;
}

// Angiven på föreläsing. Läser status.
unsigned char ascii_read_status() 
{
	char c;
	*GPIO_E_MODER = 0x00005555;
	ascii_ctrl_bit_set(B_RW);
	ascii_ctrl_bit_clear(B_RS);
	c = ascii_read_controller();
	*GPIO_E_MODER = 0x55555555;
	
	return c;
}

// Angiven på föreläsning. Läser data från displayen.
unsigned char ascii_read_data() 
{
	char c;
	*GPIO_E_MODER = 0x00005555;
	ascii_ctrl_bit_set(B_RW);
	ascii_ctrl_bit_set(B_RS);
	c = ascii_read_controller();
	*GPIO_E_MODER = 0x55555555;
	
	return c;
}

// Skriver data till displayen.
void ascii_write_data(unsigned char data) 
{
	ascii_ctrl_bit_clear(B_RW);
	ascii_ctrl_bit_set(B_RS);
	ascii_write_controller(data);
}

// Skriver kommando till displayen.
void ascii_write_cmd(unsigned char cmd) 
{
	ascii_ctrl_bit_clear(B_RW);
	ascii_ctrl_bit_clear(B_RS);
	ascii_write_controller(cmd);
}

// Sätter bitmaska x till 1.
void ascii_ctrl_bit_set(char x) 
{
	char c;
	c = *GPIO_E_ODR_LOW;
	*GPIO_E_ODR_LOW = B_SELECT | x | c;
}


// Sätter bitmaska x till 0.
void ascii_ctrl_bit_clear(char x) 
{
	char c;
	c = *GPIO_E_ODR_LOW;
	c = c & ~x;
	*GPIO_E_ODR_LOW = B_SELECT | c;
	
}

// Skriver ut en  given sträng på en given rad. 
void ascii_display(char* string, int row)
{
    for (int i = 1; i <= 20; i++)
    {
        ascii_gotoxy(i,row);
        if(*string)
        {
            ascii_write_char(*string++); 
        }
        else
        {
            ascii_write_char(' ');
        }

    }
}

void graphics_init(void)
{
    graphics_initalize();
    graphics_clear_screen();
    ascii_init();
    
    // Sätter pinnar 0-15 till utport för asciidisplayen.
	*GPIO_E_MODER = 0x55555555;
	
	// Sätter utportstypen till "push-pull".
	*GPIO_E_OTYPER = 0x0000;
	
	// Sätter frekvensen för utgångsuppdateringen till 2 MHz.
	*GPIO_E_OSPEEDR = 0x00000000;
    
}