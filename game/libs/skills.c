#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "images.h"
#include "skills.h"
//Constructor
skill newSkill(ALLEGRO_BITMAP *img, int p, int c) {
	skill nSkill;
	nSkill.image 		= newImage(img);
	nSkill.power 		= p;
	nSkill.capacity = c;
	return nSkill;
}

void drawSkill(skill itIs, int x, int y){
	setPositionSkill(itIs, x, y);
	draw(itIs.image);
}

void setPositionSkill(skill select, int x, int y){
	setPositionx(select.image, x - select.image.positionx);
	setPositiony(select.image, y - select.image.positiony);
}
