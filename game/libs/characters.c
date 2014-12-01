#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "images.h"
#include "characters.h"

void setCharacterDirectionx(character this, int x) {
	this.direction[0] = (x > 0 ? 1 : -1);
}

void setCharacterDirectiony(character this, int y) {
	if(y > 0) {
		this.direction[1] = 1;
	} else {
		this.direction[1] = -1;
	}
}

void setCharacterPosition(character this, int x, int y) {
	setPositionx(this.imagem, x);
	setPositiony(this.imagem, y);
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

void moveCharacter(character this) {
	int x = (getPositionx(this.imagem)+getCharacterSpeed(this))*getCharacterDirectionx(this);
	int y = (getPositiony(this.imagem)+getCharacterSpeed(this))*getCharacterDirectiony(this);
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

void alocaCharacter(character this, int hp) {
	this.hp = malloc(sizeof(int));
	this.speed = malloc(sizeof(int));
	this.direction = malloc(2*sizeof(int));
	setCharacterHp(this, hp);
	setCharacterPosition(this, 1, 1);
	setCharacterSpeed(this, 1);
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
	charact.imagem 		 = newImage(img);
	alocaCharacter(charact, life);
	return charact;
}
