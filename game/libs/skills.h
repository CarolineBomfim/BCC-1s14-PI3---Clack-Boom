#ifndef _SKILL_H_
#define _SKILL_H_

typedef struct _skill {
	int *actual;
	int *power;
	int *capacity;
	image image;
} skill;

//Constructor
void setSkillCapacity(skill this, int c);
void setSkillPower(skill this, int p);
int getSkillPower(skill this);
void setSkillActual(skill this, int a);
int getSkillActual(skill this);
void drawSkill(skill itIs, int x, int y);
void setPositionSkill(skill select, int x, int y);
void alocaSkill(skill this, int p, int c);
void clearSkill(skill this);
skill newSkill(ALLEGRO_BITMAP *img, int p, int c);

#endif
