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
	// ALLEGRO_AUDIO_STREAM *musica = NULL;
	// // musica = al_load_audio_stream("../res/song/mus.ogg", 4, 1024);
	// if(!musica){
	// 	erro("Falha ao carregar musica.");
	// }
	// al_attach_audio_stream_to_mixer(musica, al_get_default_mixer());
	// al_set_audio_stream_playing(musica, true);
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
	// al_destroy_audio_stream(musica);
 
	camera_finaliza(cam);
	al_destroy_display(display);
	EndGame();
	ArquivoLog("Jogo finalizado com sucesso!");
	return 0;
}
