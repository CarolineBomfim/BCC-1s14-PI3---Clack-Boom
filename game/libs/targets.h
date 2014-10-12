#ifndef _TARGET_H_
#define _TARGET_H_
typedef struct _target {
	int positionx;
	int positiony;
	int height;
	int width;
	ALLEGRO_BITMAP *image;
}target;
//Constructor

target newTarget(ALLEGRO_BITMAP *img) {
	target targetNew;
	targetNew.image = img;
	target.height 	= img->h;
	target.width 		= img->w;
	positiony 			= 0;
	positionx 			= 0;
	return targetNew;
}

void drawTarget(target select, int x, int y) {
	setPosition(select, x, y);
	al_draw_bitmap(select.image, select.positionx, select.positiony, 0);
}

void setPositionTarget(target select, int x, int y){
	select.positionx = x;
	select.positiony = y;
}

#endif
