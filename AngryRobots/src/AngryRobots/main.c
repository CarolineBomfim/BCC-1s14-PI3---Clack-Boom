#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include "../../libs/start.h"
#include "../../libs/define.h"
#include "../../libs/camera.h"
#include "../../libs/Aleatorio.h"
#include "../../libs/ArquivoLog.h"
#include "../../libs/OpenCVThread.h"
#include "../../libs/AllegroThread.h"
#include "../../libs/TratamentoDaImagem.h"

int main(){
	//Iniciando
	ALLEGRO_THREAD *allegro = al_create_thread(Allegro, NULL);
	ALLEGRO_THREAD *opencv = al_create_thread(OpenCV, NULL);
	ArquivoLog("Jogo Iniciado!");
	al_start_thread(opencv);
	al_start_thread(allegro);
	al_destroy_thread(opencv);
	al_destroy_thread(allegro);
	ArquivoLog("Jogo finalizado com sucesso!");
	return 0;
}