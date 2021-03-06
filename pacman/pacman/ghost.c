#include "ghost.h"

// Uppdaterar positionen för ett spöke.
void ghost_move(OBJECT* obj, POINT* walls, unsigned char num_walls)
{
    
    obj->posx = obj->posx + obj->dirx;
	obj->posy = obj->posy + obj->diry;
    ghost_wall_overlap(obj, walls, num_walls);
    
	ghost_clear(obj);
    obj->draw(obj);
}

// Avmålar spöket.
void ghost_clear(OBJECT* obj)
{
	// Rensar de pixlar som sparats i bufferten. 
	// Rensar ej om ett bär finns på pixeln.
	for(int i = 0; i < obj->geo->numpoints; i++)
	{
		POINT p = obj->px_buffer[i];
        // Säkerställer att randen inte avmålas.
        if(p.x > 1 && p.y > 1)
        {
            graphics_pixel_clear(p.x, p.y);
        }
	}
}

// Målar ut spöket
void ghost_draw(OBJECT* obj)
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

// Kontrollerar om kollision mellan spöke och vägg,
// vid kollision, flytta tillbaka spöket och ändra rörelseriktningen.
void ghost_wall_overlap(OBJECT* obj, POINT* walls, unsigned char num_walls)
{
    for(int i=0; i < num_walls; i++)
    {
        POINT wall_point = walls[i];
        // Kontrollerar om "Pacman" överlappar med någon vägg.
        char overlap_x1 = ((obj->posx <= wall_point.x * 7) && (obj->posx + obj->geo->sizex >= wall_point.x * 7));  
        char overlap_x2 = ((wall_point.x * 7 <= obj->posx) && (wall_point.x * 7 + UNIT_SIZE >= obj->posx));  
        char overlap_y1 = ((obj->posy <= wall_point.y * 7) && (obj->posy + obj->geo->sizey >= wall_point.y * 7));
        char overlap_y2 = ((wall_point.y * 7 <= obj->posy) && (wall_point.y * 7 + UNIT_SIZE >= obj->posy));
        // Om de överlappar, placera "Pacman" på rätt plats.
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
                obj->dirx = 0;
                // Slumpar fram en ny riktning.
				obj->diry = GHOST_SPEED * (obj->posy % 2 ?  1:-1);
                
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
                obj->diry = 0;
                // Slumpar fram en ny riktning.
				obj->dirx = GHOST_SPEED * (obj->posx % 2 ?  1:-1);
			}
        }
		if(obj->posx < 1)
		{
			obj->posx = 1;
			obj->dirx = GHOST_SPEED;
		}
		else if(obj->posx + UNIT_SIZE > 128)
		{
			obj->posx = 128 - UNIT_SIZE;
			obj->dirx = -GHOST_SPEED;
		}
		if(obj->posy < 1)
		{
			obj->posy = 1;
			obj->diry = GHOST_SPEED;
		}
		else if(obj->posy + UNIT_SIZE > 64)
		{
			obj->posy = 64 - UNIT_SIZE;
			obj->diry = -GHOST_SPEED;
		}
    }
}
// Kontrollerar kollision mellan ett spöke och "pacman". 
char ghost_pacman_collide(OBJECT* ghost, OBJECT* pacman)
{
        char overlap_x1 = ((ghost->posx <= pacman->posx) && (ghost->posx + UNIT_SIZE >= pacman->posx));  
        char overlap_x2 = ((pacman->posx <= ghost->posx) && (pacman->posx + UNIT_SIZE >= ghost->posx));  
        char overlap_y1 = ((ghost->posy <= pacman->posy) && (ghost->posy + UNIT_SIZE >= pacman->posy));
        char overlap_y2 = ((pacman->posy <= ghost->posy) && (pacman->posy + UNIT_SIZE >= ghost->posy));
        
        return ((overlap_x1 || overlap_x2) && (overlap_y1 || overlap_y2));
}