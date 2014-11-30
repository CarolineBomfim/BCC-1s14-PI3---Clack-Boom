#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_primitives.h>
#include "../../libs/camera.h"
#include "../../libs/status_bar.h"
#include "../../libs/targets.h"
#include "../../libs/characters.h"
#include "../../libs/ArquivoLog.h"
#include "../../libs/start.h"
#include "../../libs/Aleatorio.h"
#include "../../libs/Centroide.h"
#include "../../libs/Allegro.h"
#include "../../libs/menu.h"

#define TRUE 1
#define FALSE 0

int main(){
	//Iniciando
	StartGame();
	ArquivoLog("Jogo Iniciado!");
	camera *cam = camera_inicializa(0);
	ALLEGRO_DISPLAY *display = al_create_display(cam->largura, cam->altura);
	int finaliza = 1;
	int tentativas = 0;
	finaliza = Allegro(cam, display);
	camera_finaliza(cam);
	al_destroy_display(display);
	EndGame();
	ArquivoLog("Jogo finalizado com sucesso!");
	return 0;
}
