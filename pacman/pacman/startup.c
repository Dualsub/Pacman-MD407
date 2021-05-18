/*
 * 	startup.c
 *
 */
 
 #include "graphics.h"
 #include "delay.h"
 #include "keypad.h"
 #include "object.h"
 #include "pacman.h"
 
__attribute__((naked)) __attribute__((section (".start_section")) )
void startup ( void )
{
__asm__ volatile(" LDR R0,=0x2001C000\n");		/* set stack */
__asm__ volatile(" MOV SP,R0\n");
__asm__ volatile(" BL main\n");					/* call main */
__asm__ volatile(".L1: B .L1\n");				/* never return */
}

#define NUM_WALLS 56

void main(void)
{
    graphics_init();
    keypad_init();
    
    ascii_display("High Score:", 1);
    ascii_display("12765", 2);
    
	GEOMERTY pacman_sprite = { 
	37, 
	5, 5,
	{
	{2,0},
	{3,0},
	{4,0},
	{1,1},
	{2,1},
	{3,1},
	{4,1},
	{5,1},
	{0,2},
	{1,2},
	{2,2},
	{3,2},
	{4,2},
	{5,2},
	{6,2},
	{0,3},
	{1,3},
	{2,3},
	{3,3},
	{4,3},
	{5,3},
	{6,3},
	{0,4},
	{1,4},
	{2,4},
	{3,4},
	{4,4},
	{5,4},
	{6,4},
	{1,5},
	{2,5},
	{3,5},
	{4,5},
	{5,5},
	{2,6},
	{3,6},
	{4,6}
	}
	};
	
	OBJECT pacman = { 
		&pacman_sprite, 
		0, 0,
		56, 28,
		pacman_draw,
		clear_object,
		pacman_move,
		set_object_speed
		};
	
	POINT level[NUM_WALLS] = {
/*		{2,2},
		{2,3},
		{2,4},
		{2,5}
*/	{4,0},
	{13,0},
	{1,1},
	{2,1},
	{4,1},
	{6,1},
	{7,1},
	{8,1},
	{9,1},
	{10,1},
	{11,1},
	{13,1},
	{15,1},
	{16,1},
	{1,2},
	{16,2},
	{1,3},
	{3,3},
	{4,3},
	{6,3},
	{7,3},
	{10,3},
	{11,3},
	{13,3},
	{14,3},
	{16,3},
	{6,4},
	{11,4},
	{1,5},
	{3,5},
	{4,5},
	{6,5},
	{7,5},
	{8,5},
	{9,5},
	{10,5},
	{11,5},
	{13,5},
	{14,5},
	{16,5},
	{1,6},
	{16,6},
	{1,7},
	{2,7},
	{4,7},
	{6,7},
	{7,7},
	{8,7},
	{9,7},
	{10,7},
	{11,7},
	{13,7},
	{15,7},
	{16,7},
	{4,8},
	{13,8}
};
	
	GEOMERTY wall_sprite = 
	{
		16,
		7,7,
		{
		{1,1},{1,2},{1,3},{1,4},{1,5},
		{2,5},{3,5},{4,5},{5,5},
		{2,1},{3,1},{4,1},{5,1},
		{5,2},{5,3},{5,4}
		}
	};
	
	
	for(int i = 0; i < NUM_WALLS; i++)
	{
		POINT p = level[i];
		
		OBJECT wall = { 
		&wall_sprite, 
		0,0,
		p.x * 7, p.y * 7,
		pacman_draw,
		clear_object,
		pacman_move,
		set_object_speed
		};
		
		wall.draw(&wall);
	}
	
	while(1)
	{
		pacman_move(&pacman, level, NUM_WALLS);
	}
	
	
}

