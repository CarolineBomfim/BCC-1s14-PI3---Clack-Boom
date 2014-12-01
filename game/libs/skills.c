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

void drawSkill(skill this){
	draw(this.imagem);
}

void setPositionSkill(skill select, int x, int y){
	setPositionx(select.imagem, x - getPositionx(select.imagem));
	setPositiony(select.imagem, y - getPositiony(select.imagem));
}

void clearSkill(skill this) {
	clearImage(this.imagem);
	free(this.capacity);
	free(this.power);
	free(this.actual);
}

//Constructor
skill newSkill(ALLEGRO_BITMAP *img, int power, int capacity) {
	skill nSkill;
	nSkill.imagem = newImage(img);
	nSkill.capacity = malloc(sizeof(int));
	nSkill.power = malloc(sizeof(int));
	nSkill.actual = malloc(sizeof(int));
	setSkillCapacity(nSkill, capacity);
	setSkillPower(nSkill, power);
	setSkillActual(nSkill, capacity);
	return nSkill;
}
