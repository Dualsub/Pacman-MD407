#include "object.h"

void set_object_speed(OBJECT* obj, int x, int y)
{
    obj->dirx = x;
	obj->diry = y;
}

void clear_object(OBJECT* obj)
{
    GEOMERTY* geoptr = obj->geo;
	for(int i = 0; i < geoptr->numpoints; i++)
	{
		POINT p = geoptr->px[i];
		graphics_pixel_clear(obj->posx + p.x, obj->posy + p.y);
	}
}