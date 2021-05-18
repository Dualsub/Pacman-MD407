#ifndef GRAPHICS_H
#define GRAPHICS_H

#define MAX_POINTS 40

typedef struct 
{
	unsigned char x,y;
} POINT;

// Definterar typen för GEOMETRY.
typedef struct
{
	int numpoints;
	int sizex;
	int sizey;
	POINT px[MAX_POINTS];
} GEOMERTY;

void graphics_initalize ( void );
void graphics_clear_screen ( void );
void graphics_pixel_set ( int x, int y );
void graphics_pixel_clear ( int x, int y );

// Definitioner för GPIOE och dess register.
#define GPIO_E 0x40021000
#define GPIO_E_MODER ((volatile unsigned int *) GPIO_E)
#define GPIO_E_OTYPER ((volatile unsigned short *) (GPIO_E+4))
#define GPIO_E_OSPEEDR ((volatile unsigned int *) (GPIO_E+8))
#define GPIO_E_PUPDR ((volatile unsigned int *) (GPIO_E+0xC))

#define GPIO_E_IDR_LOW ((volatile unsigned char *) (GPIO_E+0x10))
#define GPIO_E_IDR_HIGH ((volatile unsigned char *) (GPIO_E+0x11))

#define GPIO_E_ODR_LOW ((volatile unsigned char *) (GPIO_E+0x14))
#define GPIO_E_ODR_HIGH ((volatile unsigned char *) (GPIO_E+0x15))

 // Makser för kontrollbitar.
#define B_E			0x40
#define B_SELECT	4
#define B_RW		2
#define B_RS		1


void ascii_init();
void ascii_gotoxy(int x, int y);
void ascii_write_controller(unsigned char c);
unsigned char ascii_read_controller();
unsigned char ascii_read_status();
unsigned char ascii_read_data();
void ascii_write_data(unsigned char data);
void ascii_write_char(unsigned char c);
void ascii_write_cmd(unsigned char cmd);
void ascii_ctrl_bit_set(char x);
void ascii_ctrl_bit_clear(char x);
void ascii_display(char* string, int row);
void graphics_init(void);

#endif
