#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "targets.h"

//Constructor
target newTarget(ALLEGRO_BITMAP *img) {
	target targetNew;
	targetNew.image 				= img;
	targetNew.height 				= al_get_bitmap_height(img);
	targetNew.width 				= al_get_bitmap_width(img);
	targetNew.positionx 		= 0;
	targetNew.positiony 		= 0;
	return targetNew;
}

void drawTarget(target select, int x, int y) {
	setPositionTarget(select, x, y);
	al_draw_bitmap(select.image, select.positionx, select.positiony, 0);
}

void setPositionTarget(target select, int x, int y){
	select.positionx = x;
	select.positiony = y;
}
