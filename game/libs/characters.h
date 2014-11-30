#ifndef _CHARACTERS_H_
#define _CHARACTERS_H_
#include "images.h"


typedef struct _character {
	int hp;
	image imagem;
	int speed;
	int direction;
}character;

//Constructor
character newCharacter(ALLEGRO_BITMAP *img, int life);

void clearCharacter(character this);

void drawCharacter(character this, int y, int x);

void speedCharacterUp(character this, int newSpeed);

void speedCharacterDown(character this, int newSpeed);

void setPositionCharacter(character this, int y, int x);

void hpCharacterUp(character this, int newHp);

void hpCharacterDown(character this, int newHp);

#endif
