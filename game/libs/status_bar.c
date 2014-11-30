#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "status_bar.h"

#define TRUE  1
#define FALSE 0
//Constructor
barstatus newBar(int allcapacity, int starting, int position, ALLEGRO_BITMAP *barimage) {
	barstatus newbarstatus;
	newbarstatus.total = allcapacity;
	newbarstatus.atual = starting;
	newbarstatus.positiony = position;
	newbarstatus.image = barimage;
	return newbarstatus;
}

void drawStatusBar(barstatus bar) {
	int status = 0;
	if(bar.total == bar.atual){
		return;
	} else if (bar.total > bar.atual) {
		while(TRUE) {
			if(status < bar.atual) {
				al_draw_bitmap(bar.image, status, bar.positiony, 0);
				status += status;
			} else {
				break;
			}
		}
	}
	return;
}

void reduceBar(barstatus bar, int reduced) {
	bar.atual -= reduced;
}

void updateBar(barstatus bar, int up) {
	bar.atual += up;
}
