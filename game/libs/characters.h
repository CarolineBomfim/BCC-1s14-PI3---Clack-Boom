#ifndef _CHARACTERS_H_
#define _CHARACTERS_H_
#include "images.h"

typedef struct _character {
	image imagem;
	int *hp;
	int *speed;
	int *direction;
}character;

void setCharacterDirectionx(character this, int x);

void setCharacterDirectiony(character this, int y);

void setCharacterPosition(character this, int x, int y);

int getCharacterDirectionx(character this);

int getCharacterDirectiony(character this);

void setCharacterHp(character this, int hp);

int getCharacterHp(character this);

void setCharacterSpeed(character this, int speed);

int getCharacterSpeed(character this);

void hpCharacterUp(character this, int newHp);

void hpCharacterDown(character this, int newHp);

void moveCharacter(character this);

void drawCharacter(character this);

void speedCharacterUp(character this, int newSpeed);

void speedCharacterDown(character this, int newSpeed);

void alocaCharacter(character this, int hp);

void clearCharacter(character this;

character newCharacter(ALLEGRO_BITMAP *img, int life);

#endif
