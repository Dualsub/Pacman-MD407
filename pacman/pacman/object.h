#ifndef OBJECT_H
#define OBJECT_H

#include "graphics.h"

// Definerar storlek på en ruta i rutnätet.
#define UNIT_SIZE 7

// Definerar ett objekt med geometri, position och riktning.
typedef struct tObj 
{
	GEOMERTY* geo;
	int dirx,diry;
	int posx,posy;
	void (* draw) (struct tObj *);
	void (* clear) (struct tObj *);
	void (* move) (struct tObj *);
	void (* set_speed) (struct tObj *, int, int);
} OBJECT, *POBJECT;

typedef struct 
{
	int posx,posy;
	unsigned char sizex, sizey;
} WALL;

void set_object_speed(OBJECT* obj, int x, int y);
void clear_object(OBJECT* obj);

#endif