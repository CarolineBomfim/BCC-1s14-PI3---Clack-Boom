#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "images.h"

int getWidth(ALLEGRO_BITMAP *img){
	return al_get_bitmap_width(img);
}

int getHeight(ALLEGRO_BITMAP *img) {
	return al_get_bitmap_height(img);
}

void setPositionx(image img, int newPosition) {
	img.positionx[0] = newPosition;
}

void setPositiony(image img, int newPosition) {
	img.positiony[0] = newPosition;
}

int getPositionx(image img) {
	return img.positionx[0];
}

int getPositiony(image img) {
	return img.positiony[0];
}

void draw(image img) {
	al_draw_bitmap(img.image, getPositionx(img),getPositiony(img), 0);
}

int *alocaPosition() {
	int *x = malloc(sizeof(int));
	return x;
}

void liberaPosition(int *x) {
	free(x);
}

void clearImage(image img) {
	liberaPosition(img.positionx);
	liberaPosition(img.positiony);
}

image newImage(ALLEGRO_BITMAP *img) {
	image imagem;
	imagem.image = img;
	imagem.width = getWidth(img);
	imagem.height = getHeight(img);
	imagem.positiony = alocaPosition();
	imagem.positionx = alocaPosition();
	setPositionx(imagem, imagem.width);
	setPositiony(imagem, imagem.height);
	return imagem;
}
