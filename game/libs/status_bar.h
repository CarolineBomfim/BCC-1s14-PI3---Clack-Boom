#ifndef _STATUS_BAR_H_
#define _STATUS_BAR_H_

typedef struct _barstatus {
	int total;
	int atual;
	int positiony;
	ALLEGRO_BITMAP *image;
}barstatus;

//Constructor
barstatus newBar(int allcapacity, int starting, int position, ALLEGRO_BITMAP *barimage);

void drawStatusBar(barstatus bar);

void reduceBar(barstatus bar, int reduced);

void updateBar(barstatus bar, int up);


#endif
