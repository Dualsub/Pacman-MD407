#include "pacman.h"
#include "keypad.h"

void pacman_move(OBJECT* obj, POINT* points, unsigned char num_points)
{
    obj->clear(obj);
    char c;
    c = keyb();
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
	pacman_wall_overlap(obj, points, num_points);
    
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

void pacman_wall_overlap(OBJECT* obj, POINT* points, unsigned char num_points)
{
    for(int i=0; i < num_points; i++)
    {
        POINT wall_point = points[i];
        // Kontrollerar om "Pacman" överlappar med någon vägg.
        char overlap_x1 = (obj->posx <= wall_point.x && obj->posx + obj->geo->sizex >= wall_point.x);  
        char overlap_x2 = (wall_point.x <= obj->posx && wall_point.x + UNIT_SIZE >= obj->posx);  
        char overlap_y1 = (obj->posy <= wall_point.y && obj->posy + obj->geo->sizey >= wall_point.y);
        char overlap_y2 = (wall_point.y <= obj->posy && wall_point.y + UNIT_SIZE >= obj->posy);
        // Om de överlappar, placera "Pacman" på rätt plats.
        if((overlap_x1 || overlap_x2) && (overlap_y1 || overlap_y2))
        {
            if(overlap_x1)
            {
                obj->posx -= (obj->posx + obj->geo->sizex) - wall_point.x;
            }
            else if(overlap_x2)
            {
                obj->posx += (wall_point.x + UNIT_SIZE) - obj->posx;
            }
            if(overlap_y1)
            {
                obj->posy -= (obj->posy + obj->geo->sizey) - wall_point.y;
            }
            else if(overlap_y2)
            {
                obj->posy += (wall_point.y + UNIT_SIZE) - obj->posy;
            }
            obj->dirx = 0;
            obj->diry = 0;
        }
    }
}