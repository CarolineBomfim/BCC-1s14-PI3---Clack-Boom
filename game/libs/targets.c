#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "images.h"
#include "targets.h"

//Constructor
target newTarget(ALLEGRO_BITMAP *img) {
	target targetNew;
	targetNew.imagem = newImage(img);
	return targetNew;
}

void drawTarget(target select, int x, int y) {
	setPositionTarget(select, x, y);
	draw(select.imagem);
}

void setPositionTarget(target select, int x, int y){
	setPositionx(select.imagem, x);
	setPositiony(select.imagem, y);
}
