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

void clearCharacter(character this){
	clearImage(this.imagem);
}

void drawCharacter(character this, int y, int x) {
	setPositionCharacter(this, y, x);
	draw(this.imagem);
}

void speedCharacterUp(character this, int newSpeed) {
	this.speed += newSpeed;
}

void speedCharacterDown(character this, int newSpeed) {
	this.speed -= newSpeed;
}

void setPositionCharacter(character this, int y, int x) {
	setPositionx(this.imagem, x - this.imagem.width );
	setPositiony(this.imagem,  y - this.imagem.height);
}

void hpCharacterUp(character this, int newHp) {
	this.hp += newHp;
}

void hpCharacterDown(character this, int newHp) {
	this.hp -= newHp;
}
