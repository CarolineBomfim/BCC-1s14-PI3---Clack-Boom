#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "images.h"
#include "characters.h"


void setCharacterDirectiony(character this, int y) {
	if (y > 0) {
		this.direction[1] = 1;
	} else {
		this.direction[1] = -1;
	}
}

void setCharacterDirectionx(character this, int x) {
	if(x > 0) {
		this.direction[0] = 1;
	} else {
		this.direction[0] = -1;
	}
}

void setCharacterPosition(character this, int x, int y) {
	setPositionx(this.imagem, x);
	setPositiony(this.imagem, y);
}

int getCharacterPositionx(character this) {
	return getPositionx(this.imagem);
}

int getCharacterPositiony(character this) {
	return getPositiony(this.imagem);
}

int getCharacterDirectionx(character this) {
	return this.direction[0];
}

int getCharacterDirectiony(character this) {
	return this.direction[1];
}

void setCharacterHp(character this, int hp) {
	this.hp[0] = hp;
}
int getCharacterHp(character this) {
	return this.hp[0];
}
void setCharacterSpeed(character this, int speed) {
	this.speed[0] = speed;
}

int getCharacterSpeed(character this) {
	return this.speed[0];
}

void hpCharacterUp(character this, int newHp) {
	this.hp[0] += newHp;
}

void hpCharacterDown(character this, int newHp) {
	this.hp[0] -= newHp;
}

void moveCharacter(character this, int moveInX, int moveInY) {
	int x = 0;
	int y = 0;
	if(moveInX) {
		x = (getCharacterPositionx(this)+getCharacterSpeed(this))*getCharacterDirectionx(this);
	} 
	if(moveInY) {
		y = (getCharacterPositiony(this)+getCharacterSpeed(this))*getCharacterDirectiony(this);
	}
	setCharacterPosition(this, x, y);
}

void drawCharacter(character this) {
	draw(this.imagem);
}

void speedCharacterUp(character this, int newSpeed) {
	this.speed += newSpeed;
}

void speedCharacterDown(character this, int newSpeed) {
	this.speed -= newSpeed;
}



void clearCharacter(character this){
	clearImage(this.imagem);
	free(this.speed);
	free(this.direction);
	free(this.hp);
}

//Constructor
character newCharacter(ALLEGRO_BITMAP *img, int life) {
	character charact;	
	charact.imagem = newImage(img);
	charact.hp = malloc(sizeof(int));
	charact.speed = malloc(sizeof(int));
	charact.direction = malloc(2*sizeof(int));
	setCharacterHp(charact, life);
	setCharacterPosition(charact, charact.imagem.width, charact.imagem.height);
	setCharacterSpeed(charact, 1);
	setCharacterDirectiony(charact, 1);
	setCharacterDirectionx(charact, 1);
	return charact;
}
