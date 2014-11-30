#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "status_bar.h"
#include "images.h"

#define TRUE  1
#define FALSE 0
//Constructor
barstatus newBar(int allcapacity, int starting, int position, ALLEGRO_BITMAP *barimage) {
	barstatus newbarstatus;
	newbarstatus.total = allcapacity;
	newbarstatus.atual = starting;
	newbarstatus.imagem = newImage(barimage);
	setPositiony(newbarstatus.imagem, position);
	setPositionx(newbarstatus.imagem, starting);
	return newbarstatus;
}

void clearBar(barstatus this){
	clearImage(this.imagem);
}

void drawStatusBar(barstatus bar) {
	int status = 0;
	if(bar.total == bar.atual){
		return;
	} else if (bar.total > bar.atual) {
		while(TRUE) {
			if(status < bar.atual) {
				setBarPosition( bar, status, getPositiony(bar.imagem));
				draw(bar.imagem);
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

void setBarPosition(barstatus it, int x, int y) {
	setPositionx(it.imagem, x);
	setPositiony(it.imagem, y);
}
