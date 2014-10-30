#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "images.h"
#include "characters.h"
//Constructor
character newCharacter(ALLEGRO_BITMAP *img, int life) {
	character charact;	
	charact.hp				= life;
	charact.imagem 		= newImage(img);
	charact.speed 		= 1;
	charact.direction = 1;
	return charact;
}

void drawCharacter(character isIt, int y, int x) {
	setPositionCharacter(isIt, y, x);
	draw(isIt.imagem);
}

void speedCharacterUp(character isIt, int newSpeed) {
	isIt.speed += newSpeed;
}

void speedCharacterDown(character isIt, int newSpeed) {
	isIt.speed -= newSpeed;
}

void setPositionCharacter(character isIt, int y, int x) {
	setPositionx(isIt.imagem, x - isIt.imagem.width );
	setPositiony(isIt.imagem,  y - isIt.imagem.height);
}

void hpCharacterUp(character isIt, int newHp) {
	isIt.hp += newHp;
}

void hpCharacterDown(character isIt, int newHp) {
	isIt.hp -= newHp;
}
