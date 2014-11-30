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
	int aux = 0;
	while(status < bar.atual) {
		setPositionx(bar.imagem, aux);
		draw(bar.imagem);
		status++;
		aux += bar.imagem.width;
	}
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
