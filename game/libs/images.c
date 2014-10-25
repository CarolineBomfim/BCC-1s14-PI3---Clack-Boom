#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "images.h"

int getWidth(ALLEGRO_BITMAP *img){
	return al_get_bitmap_width(img);
}

int getHeight(ALLEGRO_BITMAP *img) {
	return al_get_bitmap_height(img);
}

int getPositionx(image img) {
	return img.positionx;
}

int getPositiony(image img) {
	return img.positiony;
}

void setPositionx(image img, int newPosition) {
	img.positionx = newPosition;
}

void setPositiony(image img, int newPosition) {
	img.positiony = newPosition;
}

void draw(image img) {
	al_draw_bitmap(img.image, img.positionx, img.positiony, 0);
} 

image newImage(ALLEGRO_BITMAP *img) {
	image imagem;
	imagem.image = img;
	imagem.width = getWidth(img);
	imagem.height = getHeight(img);
	imagem.positiony = 0;
	imagem.positionx = 0;
	return imagem;
}
