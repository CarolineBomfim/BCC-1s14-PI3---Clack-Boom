#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include "../../libs/camera.h"
#include "../../libs/ArquivoLog.h"
#include "../../libs/start.h"
#include "../../libs/define.h"
#include "../../libs/Aleatorio.h"
#include "../../libs/Centroide.h"
#include "../../libs/Allegro.h"
#include "../../libs/menu.h"

int main(){
	//Iniciando
	StartGame();
	ArquivoLog("Jogo Iniciado!");
	camera *cam = camera_inicializa(0);
	ALLEGRO_DISPLAY *display = al_create_display(cam->largura, cam->altura);
	int finaliza = 0;
	int tentativas = 0;
	while(1){
		if(finaliza == 0){
			finaliza = Menu(cam, display, tentativas);
		}
		if(finaliza == 1){
			break;
		}
		else{
			finaliza = Allegro(cam, display);
			if(finaliza == 1){
				break;
			}
			else if(finaliza == 2){
				Congratulation(cam, display);
				tentativas = 0;
			}			
		}
		tentativas++;
	}
	camera_finaliza(cam);
	al_destroy_display(display);
	EndGame();
	ArquivoLog("Jogo finalizado com sucesso!");
	return 0;
}