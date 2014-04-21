
#include <stdlib.h>
#include <allegro5/allegro.h>
#include "../../libs/start.h"
#include "../../libs/ArquivoLog.h"
#include "../../libs/AllegroThread.h"

int main(){
	//Iniciando
	StartGame();
	ArquivoLog("Jogo Iniciado!");
	Allegro();
	EndGame();
	ArquivoLog("Jogo finalizado com sucesso!");
	return 0;
}