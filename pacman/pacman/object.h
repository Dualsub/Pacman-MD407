#ifndef OBJECT_H
#define OBJECT_H

#include "graphics.h"

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

#define WALL_SIZE 8

typedef struct 
{
	int posx,posy;
	unsigned char sizex, sizey;
} WALL;

void pacman_move(OBJECT* obj);
void ghosts_move(OBJECT* obj);


#endif