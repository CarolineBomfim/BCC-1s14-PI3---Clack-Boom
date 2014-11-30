#ifndef _SKILL_H_
#define _SKILL_H_

typedef struct _skill{
	int power;
	int capacity;
	int width;
	int height;
	int positionx;
	int positiony;
	ALLEGRO_BITMAP *image;
}skill;

//Constructor
skill newSkill(ALLEGRO_BITMAP *img, int p, int c);

void drawSkill(skill itIs, int x, int y);

void setPositionSkill(skill select, int x, int y);
#endif
