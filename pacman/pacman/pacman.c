#include "pacman.h"
#include "keypad.h"

// Uppdaterar positionen för "Pacman".
void pacman_move(OBJECT* obj, POINT* points, unsigned char num_points)
{	
   char c;
    c = keyb();
    switch(c) 
    {
        case 6: obj->set_speed(obj, BASE_SPEED,0); break;
        case 4: obj->set_speed(obj, -BASE_SPEED,0); break;
        case 5: obj->set_speed(obj, 0,0); break;
        case 2: obj->set_speed(obj, 0,-BASE_SPEED); break;
        case 8: obj->set_speed(obj, 0,BASE_SPEED); break;
        default: obj->set_speed(obj, 0,0); break;
    }
	obj->posx = obj->posx + obj->dirx;
	obj->posy = obj->posy + obj->diry;
	pacman_wall_overlap(obj, points, num_points);
    
	obj->clear(obj);
	obj->draw(obj);
}

void pacman_draw(OBJECT* obj)
{
    GEOMERTY* geoptr = obj->geo;
	for(int i = 0; i < geoptr->numpoints; i++)
	{
		POINT p = geoptr->px[i];
		POINT buffer_p = {obj->posx + p.x, obj->posy + p.y};
		obj->px_buffer[i] = buffer_p;
		graphics_pixel_set(obj->posx + p.x, obj->posy + p.y);
	}
}

// Kontrollerar om kollision mellan "Pacman" och vägg,
// vid kollision, flytta tillbaka "Pacman".
void pacman_wall_overlap(OBJECT* obj, POINT* points, unsigned char num_points)
{
    for(int i=0; i < num_points; i++)
    {
        POINT wall_point = points[i];
        // Kontrollerar om "Pacman" överlappar med vägg i någon riktning.
        char overlap_x1 = ((obj->posx <= wall_point.x * 7) && (obj->posx + obj->geo->sizex >= wall_point.x * 7));  
        char overlap_x2 = ((wall_point.x * 7 <= obj->posx) && (wall_point.x * 7 + UNIT_SIZE >= obj->posx));  
        char overlap_y1 = ((obj->posy <= wall_point.y * 7) && (obj->posy + obj->geo->sizey >= wall_point.y * 7));
        char overlap_y2 = ((wall_point.y * 7 <= obj->posy) && (wall_point.y * 7 + UNIT_SIZE >= obj->posy));
        // Om de överlappar, placera "Pacman" utanför objecktet.
        if((overlap_x1 || overlap_x2) && (overlap_y1 || overlap_y2))
        {
			if(obj->dirx != 0)
			{
				if(overlap_x1)
				{
					obj->posx -= (obj->posx + obj->geo->sizex + 1) - wall_point.x * 7;
				}
				else if(overlap_x2)
				{
					obj->posx += (wall_point.x * 7 + UNIT_SIZE) - obj->posx + 1;
				}
			} 
			else if(obj->diry != 0)
			{
				if(overlap_y1)
				{
					obj->posy -= (obj->posy + obj->geo->sizey + 1) - wall_point.y * 7;
				}
				else if(overlap_y2)
				{
					obj->posy += (wall_point.y * 7 + UNIT_SIZE) - obj->posy + 1;
				}
			}
        }
		if(obj->posx < 1)
		{
			obj->posx = 1;
		}
		else if(obj->posx + UNIT_SIZE > 128)
		{
			obj->posx = 128 - UNIT_SIZE;
		}
		if(obj->posy < 1)
		{
			obj->posy = 1;
		}
		else if(obj->posy + UNIT_SIZE > 64)
		{
			obj->posy = 64 - UNIT_SIZE;
		}
    }
}

void pacman_berries_collide_and_draw(OBJECT* obj, POINT* berries, unsigned char num_berries, unsigned char* points_ptr)
{
	for(int i = 0; i < 106; i++)
	{
		POINT berry_point = berries[i];
		if(berry_point.x != 0xFF && berry_point.y != 0xFF)
		{
			char overlap_x = ((obj->posx <= berry_point.x * 7 + 4) && (obj->posx + UNIT_SIZE >= berry_point.x * 7 + 4));   
			char overlap_y = ((obj->posy <= berry_point.y * 7 + 4) && (obj->posy + UNIT_SIZE >= berry_point.y * 7 + 4));
			if(overlap_x && overlap_y)
			// Om pacman kolliderar med ett bär skall det inte målas ut igen. 
			{
				(*points_ptr)++;
				// Markerar bäret som taget.
				POINT p = { 0xFF, 0xFF };
				berries[i] = p;
				graphics_pixel_clear(berry_point.x * 7 + 4, berry_point.y * 7 + 4);
			}
			else 
			{
				graphics_pixel_set(berry_point.x * 7 + 4, berry_point.y * 7 + 4);
			}
		}
	}
}