
#include <stdlib.h>
#include <allegro5/allegro.h>
#include "../../libs/start.h"
#include "../../libs/ArquivoLog.h"
#include "../../libs/AllegroThread.h"
#include "../../libs/camera.h"

int main(){
	//Iniciando
	StartGame();
	ArquivoLog("Jogo Iniciado!");
	camera *cam = camera_inicializa(0);
	ALLEGRO_DISPLAY *display = al_create_display(cam->largura, cam->altura);
	int finaliza = 0;
	while(1){
		// Menu(cam, display);
		if(finaliza == 1){
			break;
		}
		else{
			Allegro(cam, display);
		}
	}
	camera_finaliza(cam);
	al_destroy_display(display);
	EndGame();
	ArquivoLog("Jogo finalizado com sucesso!");
	return 0;
}