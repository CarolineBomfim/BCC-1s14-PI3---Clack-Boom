#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "characters.h"

//Constructor
character newCharacter(ALLEGRO_BITMAP *img, int life) {
	character charact;
	
	charact.hp				= life;
	charact.image 		= img;
	charact.width 		= al_get_bitmap_width(img);
	charact.height 		= al_get_bitmap_height(img);
	charact.speed 		= 1;
	charact.direction = 1;
	charact.positionx = 0;
	charact.positiony = 0;

	return charact;
}

void drawCharacter(character isIt, int y, int x) {
	setPositionCharacter(isIt, y, x);
	al_draw_bitmap(isIt.image, isIt.positionx, isIt.positiony, 0);
}

void speedCharacterUp(character isIt, int newSpeed) {
	isIt.speed += newSpeed;
}

void speedCharacterDown(character isIt, int newSpeed) {
	isIt.speed -= newSpeed;
}

void setPositionCharacter(character isIt, int y, int x) {
	isIt.positionx = x - isIt.width;
	isIt.positiony = y - isIt.height;
}

void hpCharacterUp(character isIt, int newHp) {
	isIt.hp += newHp;
}

void hpCharacterDown(character isIt, int newHp) {
	isIt.hp -= newHp;
}
