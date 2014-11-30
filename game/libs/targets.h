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

target newTarget(ALLEGRO_BITMAP *img);

void drawTarget(target select, int x, int y);

void setPositionTarget(target select, int x, int y);

#endif
