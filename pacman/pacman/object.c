#include "object.h"

void set_object_speed(OBJECT* obj, int x, int y)
{
    obj->dirx = x;
	obj->diry = y;
}

void clear_object(OBJECT* obj)
{
	for(int i = 0; i < obj->geo->numpoints; i++)
	{
		POINT p = obj->px_buffer[i];
		graphics_pixel_clear(p.x, p.y);
	}
}