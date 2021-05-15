#ifndef PACMAN_H
#define PACMAN_H

#include "object.h"
#include "graphics.h"

void pacman_move(OBJECT* obj, POINT* points, unsigned char num_points);
void pacman_draw(OBJECT* obj);
void pacman_wall_overlap(OBJECT* obj, POINT* points, unsigned char num_points);

#endif