#ifndef OBJECT_H
#define OBJECT_H

// Definerar ett objekt med geometri, position och riktning.
typedef struct tObj 
{
	PGEOMERTY geo;
	int dirx,diry;
	int posx,posy;
	void (* draw) (struct tObj *);
	void (* clear) (struct tObj *);
	void (* move) (struct tObj *);
	void (* set_speed) (struct tObj *, int, int);
} OBJECT, *POBJECT;

#endif