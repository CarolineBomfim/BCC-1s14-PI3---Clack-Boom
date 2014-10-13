#ifndef _CHARACTERS_H_
#define _CHARACTERS_H_

typedef struct _character {
	int hp;
	int width;
	int height;
	int speed;
	int direction;
	int positionx;
	int positiony;
	ALLEGRO_BITMAP *image;
}character;

//Constructor
character newCharacter(ALLEGRO_BITMAP *img, int life);

void drawCharacter(character isIt, int y, int x);

void speedCharacterUp(character isIt, int newSpeed);

void speedCharacterDown(character isIt, int newSpeed);

void setPositionCharacter(character isIt, int y, int x);

void hpCharacterUp(character isIt, int newHp);

void hpCharacterDown(character isIt, int newHp);

#endif
