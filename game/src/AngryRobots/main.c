#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "../../libs/start.h"
#include "../../libs/camera.h"
#include "../../libs/ArquivoLog.h"
#include "../../libs/screen_methods.h"

#define TRUE 1
#define FALSE 0
#define FPS 180.0

int main(){
	//Iniciando
	StartGame();
	ArquivoLog("Jogo Iniciado!");
	camera 								*cam					= camera_inicializa(0);
	if(!cam){
		ArquivoLog("Error!!!! Camera not initialization!");
	}
	int 									altura				= cam->altura;
	int 									largura				= cam->largura;
	int										finalizar			= 0;
	ALLEGRO_TIMER 				*temporizador = al_create_timer(1.0/FPS);
	ALLEGRO_DISPLAY 			*display 			= al_create_display((largura*2), altura);
	ALLEGRO_BITMAP 				*buffer 			= al_get_backbuffer(display);
	ALLEGRO_BITMAP 				*esquerda			= al_create_sub_bitmap(buffer, 0, 0, largura, altura);
	ALLEGRO_EVENT_QUEUE 	*EventoQueue 	= al_create_event_queue();
	ALLEGRO_EVENT 				evento;
	

	al_start_timer(temporizador);
	al_register_event_source(EventoQueue, al_get_timer_event_source(temporizador));
	al_register_event_source(EventoQueue, al_get_display_event_source(display));
	while(TRUE) {
		camera_atualiza(cam);
		al_wait_for_event(EventoQueue, &evento);
		switch(evento.type){
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				finalizar = 1;
				ArquivoLog("Finalizado pelo usuario!");
				break;

			default:
				ArquivoLog("Evento desconhecido!");
				break;
		}
		if(finalizar == 1){
			return 1;
		}
		
		screen_methods(cam);
		camera_copia(cam, cam->quadro, esquerda);
		al_flip_display();
	}
	camera_finaliza(cam);
	al_destroy_display(display);
	EndGame();
	ArquivoLog("Jogo finalizado com sucesso!");
	return 0;
}

