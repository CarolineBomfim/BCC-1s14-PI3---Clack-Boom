#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "skills.h"
//Constructor
skill newSkill(ALLEGRO_BITMAP *img, int p, int c) {
	skill nSkill;
	nSkill.image 		= img;
	nSkill.power 		= p;
	nSkill.capacity = c;
	nSkill.height 	= al_get_bitmap_height(img);
	nSkill.width 		= al_get_bitmap_width(img);
	return nSkill;
}

void drawSkill(skill itIs, int x, int y){
	setPositionSkill(itIs, x, y);
	al_draw_bitmap(itIs.image, itIs.positionx, itIs.positiony, 0);
}

void setPositionSkill(skill select, int x, int y){
	select.positionx = x;
	select.positiony = y;
}
