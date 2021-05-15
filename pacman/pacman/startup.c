/*
 * 	startup.c
 *
 */
 
 #include "graphics.h"
 #include "delay.h"
 #include "keypad.h"
 #include "object.h"
 
__attribute__((naked)) __attribute__((section (".start_section")) )
void startup ( void )
{
__asm__ volatile(" LDR R0,=0x2001C000\n");		/* set stack */
__asm__ volatile(" MOV SP,R0\n");
__asm__ volatile(" BL main\n");					/* call main */
__asm__ volatile(".L1: B .L1\n");				/* never return */
}

void main(void)
{
    graphics_init();
    keypad_init();
    
    ascii_display("High Score:", 1);
    
    
}

