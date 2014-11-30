#ifndef _SKILL_H_
#define _SKILL_H_

typedef struct _skill{
	int power;
	int capacity;
	image image;
}skill;

//Constructor
skill newSkill(ALLEGRO_BITMAP *img, int p, int c);

void clearSkill(skill this);

void drawSkill(skill itIs, int x, int y);

void setPositionSkill(skill select, int x, int y);

#endif
