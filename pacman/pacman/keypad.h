// Definitioner för GPIOD och dess register.
#define GPIO_D 0x40020C00
#define GPIO_D_MODER ((volatile unsigned int *) GPIO_D)
#define GPIO_D_OTYPER ((volatile unsigned short *) (GPIO_D+4))
#define GPIO_D_OSPEEDR ((volatile unsigned int *) (GPIO_D+8))
#define GPIO_D_PUPDR ((volatile unsigned int *) (GPIO_D+0xC))

#define GPIO_D_IDR_LOW ((volatile unsigned char *) (GPIO_D+0x10))
#define GPIO_D_IDR_HIGH ((volatile unsigned char *) (GPIO_D+0x11))

#define GPIO_D_ODR_LOW ((volatile unsigned char *) (GPIO_D+0x14))
#define GPIO_D_ODR_HIGH ((volatile unsigned char *) (GPIO_D+0x15))

void kbd_active(unsigned int row);
int kbd_get_col(void); 
unsigned short keyb_alt_ctrl(void);
void keypad_init(void);