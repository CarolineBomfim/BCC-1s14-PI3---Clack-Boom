#ifndef _IMAGES_H_
#define _IMAGES_H_

typedef struct _image{
	ALLEGRO_BITMAP *image;
	int width;
	int height;
	int positionx;
	int positiony;
}image;

int getWidth(ALLEGRO_BITMAP img);

int getHeight(ALLEGRO_BITMAP img);

int getPositionx(image img);

int getPositiony(image img);

void setPositionx(image img, int newPosition);

void setPositiony(image img, int newPosition);

void draw(image img);

image newImage(ALLEGRO_BITMAP *img);

#endif

