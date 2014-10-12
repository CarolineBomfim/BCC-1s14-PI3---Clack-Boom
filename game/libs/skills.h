#ifndef _SKILL_H_
#define _SKILL_H_

typedef struct _skill{
	int power;
	int capacity;
	ALLEGRO_BITMAP *image;
}skill;

//Constructor
skill newSkill(ALLEGRO_BITMAP *img, int p, int c) {
	skill nSkill;
	nSkill.image 		= img;
	nSkill.power 		= p;
	nSkill.capacity = c;
	return nSkill;
}

#endif
