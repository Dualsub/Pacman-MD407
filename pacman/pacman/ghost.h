#ifndef GHOST_HclTabCtrl
#define GHOST_H

#include "object.h"
#include "graphics.h"

#define GHOST_SPEED 2

void ghost_move(OBJECT* obj, POINT* walls, unsigned char num_walls);
void ghost_draw(OBJECT* obj);
void ghost_wall_overlap(OBJECT* obj, POINT* walls, unsigned char num_walls);
char ghost_pacman_collide(OBJECT* ghost, OBJECT* pacman);
void ghost_clear(OBJECT* obj);
#endif