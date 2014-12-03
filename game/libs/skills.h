#ifndef _SKILL_H_
#define _SKILL_H_

typedef struct _skill {
	int *actual;
	int *power;
	int *capacity;
	image imagem;
}skill;

int getSkillCapacity(skill this);
void setSkillPower(skill this, int p);
int getSkillPower(skill this);
void setSkillActual(skill this, int a);
int getSkillActual(skill this);
void drawSkill(skill this);
void setSkillPosition(skill select, int x, int y);
void clearSkill(skill this);
skill newSkill(ALLEGRO_BITMAP *img, int power, int capacity);
#endif
