#ifndef GHOST_HclTabCtrl
#define GHOST_H

#include "object.h"
#include "graphics.h"

void ghost_move(OBJECT* obj, POINT* points, unsigned char num_points);
void ghost_draw(OBJECT* obj);

#endif