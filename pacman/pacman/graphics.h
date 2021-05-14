#ifndef GRAPHICS_H
#define GRAPHICS_H

#define MAX_POINTS

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
	POINT px[MAX_POINTS]
} GEOMERTY;

void graphics_initalize ( void );
void graphics_clear_screen ( void );
void graphics_pixel_set ( int x, int y );
void graphics_pixel_clear ( int x, int y );

#endif
