#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "images.h"
#include "skills.h"

void setSkillCapacity(skill this, int c) {
	this.capacity[0] = c;
}

int getSkillCapacity(skill this){
	return this.capacity[0];
}
void setSkillPower(skill this, int p) {
	this.power[0] = p;
}

int getSkillPower(skill this){
	return this.power[0];
}

void setSkillActual(skill this, int a) {
	this.actual[0] = a;
}

int getSkillActual(skill this){
	return this.actual[0];
}

void drawSkill(skill itIs, int x, int y){
	setPositionSkill(itIs, x, y);
	draw(itIs.image);
}

void setPositionSkill(skill select, int x, int y){
	setPositionx(select.image, x - getPositionx(select.image));
	setPositiony(select.image, y - getPositiony(select.image));
}

void alocaSkill(skill this, int p, int c) {
	this.power = malloc(sizeof(int));
	this.capacity = malloc(sizeof(int));
	setSkillCapacity(this, c);
	setSkillPower(this, p);
	setSkillActual(this, c);
}
void clearSkill(skill this) {
	clearImage(this.image);
	free(this.capacity);
	free(this.power);
	free(this.actual);
}

//Constructor
skill newSkill(ALLEGRO_BITMAP *img, int p, int c) {
	skill nSkill;
	nSkill.image = newImage(img);
	alocaSkill(nSkill, p, c);
	return nSkill;
}
