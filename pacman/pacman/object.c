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
		// För att randen av banan inte ska försvinna.
		if(p.x > 1 && p.y > 1)
			graphics_pixel_clear(p.x, p.y);
	}
}