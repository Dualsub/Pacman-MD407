#include "pacman.h"
#include "keypad.h"

void pacman_move(OBJECT* obj)
{
    obj->clear(obj);
    char c;
    c = keyb_alt_ctrl();
    switch(c) 
    {
        case 6: obj->set_speed(obj, 2,0); break;
        case 4: obj->set_speed(obj, -2,0); break;
        case 5: obj->set_speed(obj, 0,0); break;
        case 2: obj->set_speed(obj, 0,-2); break;
        case 8: obj->set_speed(obj, 0,2); break;
        default: obj->set_speed(obj, 0,0); break;
    }

	obj->posx = obj->posx + obj->dirx;
	obj->posy = obj->posy + obj->diry;
	
	obj->draw(obj);
}

void pacman_draw(OBJECT* obj)
{
    GEOMERTY* geoptr = obj->geo;
	for(int i = 0; i < geoptr->numpoints; i++)
	{
		POINT p = geoptr->px[i];
		graphics_pixel_set(obj->posx + p.x, obj->posy + p.y);
	}
}
