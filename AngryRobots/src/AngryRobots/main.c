
#include <stdlib.h>
#include <allegro5/allegro.h>
#include "../../libs/start.h"
#include "../../libs/ArquivoLog.h"
#include "../../libs/AllegroThread.h"

int main(){
	//Iniciando
	StartGame();
	ALLEGRO_THREAD *allegro = al_create_thread(Allegro, NULL);
	ArquivoLog("Jogo Iniciado!");
	al_start_thread(allegro);
	al_destroy_thread(allegro);
	EndGame();
	ArquivoLog("Jogo finalizado com sucesso!");
	return 0;
}