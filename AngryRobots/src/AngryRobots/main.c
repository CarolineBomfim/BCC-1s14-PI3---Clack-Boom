#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

#include "../../libs/camera.h"
#include "../../libs/libs.h"
#include "../../libs/Aleatorio.h"
#include "../../libs/TratamentoDaImagem.h"

int main(){
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_FONT *fonte1 = NULL;
	ALLEGRO_BITMAP *background = NULL;

//Iniciando
	//O camera inicializa pode ser modificado, 0 a camera primeria 1 a secundaria e assim por diante.
	camera *cam = camera_inicializa(0);

	int LARGURA = cam->largura;
	int ALTURA = cam->altura;

	if(!cam)
		erro("Erro ao iniciar a camera.");

	if(!al_init())
		erro("Falha ao iniciar o Allegro.");

	if(!al_init_image_addon())
		erro("Falha ao iniciar a biblioteca de imagens do Allegro.");

	if(!al_init_primitives_addon())
		erro("Falha ao carregar primitive_addons.");
	
	al_init_font_addon();

	if(!al_init_ttf_addon())
		erro("Falha ao iniciar a biblioteca de ttf do Allegro.");

	display = al_create_display(2*LARGURA, ALTURA);
	if(!display)
		erro("Falha ao criar display.");

	fonte1 = al_load_font("fontes/comic.ttf", 50, 0);
	if(!fonte1)
		erro("Falha ao carregar a fonte1.");

	background = al_create_bitmap(LARGURA, ALTURA);
	if(!background)
		erro("Falha ao criar bitmap brackground.");

	ALLEGRO_TIMER *temporizador = al_create_timer(1.0/FPS);
	if(!temporizador)
		erro("Falha ao criar temporizador.");

	ALLEGRO_EVENT_QUEUE *EventoQueue = al_create_event_queue();
	if(!EventoQueue)
		erro("Falha ao criar evento QUEUE");

	ArquivoLog("Sucesso ao carregar e criar fonte, imagens e eventos.");

	al_register_event_source(EventoQueue, al_get_timer_event_source(temporizador));
	al_register_event_source(EventoQueue, al_get_display_event_source(display));

	ArquivoLog("Registro de eventos!");

	al_start_timer(temporizador);
    // Todas as bibliotecas e arquivos foram carregados com sucesso!
	ALLEGRO_BITMAP *buffer = al_get_backbuffer(display);
	ALLEGRO_BITMAP *esquerda = al_create_sub_bitmap(buffer, 0, 0, LARGURA, ALTURA);
	ALLEGRO_BITMAP *direita = al_create_sub_bitmap(buffer, LARGURA, 0, LARGURA, ALTURA);

	unsigned char ***CAMERA = camera_aloca_matriz(cam);
	unsigned char ***matriz = camera_aloca_matriz(cam);

  int *cordenada = malloc(2*sizeof(int));
  int EventoDetectado = 0;
	int laco = 0;

	ArquivoLog("Sucesso ao criar buffers bitmap!");
// ------------------------------------------------------------
// ------------------------------------------------------------

	while(1){
		camera_atualiza(cam);
		ALLEGRO_EVENT evento;
		al_wait_for_event(EventoQueue, &evento);
		switch(evento.type){
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				laco = 1;
				ArquivoLog("Finalizado pelo usuario!");
				break;

			case ALLEGRO_EVENT_TIMER:
				EventoDetectado = 1;
				break;
			default:
				ArquivoLog("Evento desconhecido!");
		}
		if(laco == 1){
			break;
		}

		if(EventoDetectado == 1){
			TratamentoDaImagem(
				cam,
				esquerda,
				direita,
				EventoQueue,
				temporizador,
				display,
				CAMERA,
				matriz,
				cordenada,
				LARGURA,
				ALTURA);
			al_flip_display();
		}
	}
// ------------------------------------------------------------
// ------------------------------------------------------------
	
	camera_libera_matriz(cam, CAMERA);
	camera_libera_matriz(cam, matriz);
	
// ------------------------------------------------------------
// ------------------------------------------------------------
	free(cordenada);
	ArquivoLog("Processo de encerramento iniciado!");

	al_destroy_bitmap(direita);
	al_destroy_bitmap(esquerda);

	al_unregister_event_source(EventoQueue, al_get_timer_event_source(temporizador));
	al_unregister_event_source(EventoQueue, al_get_display_event_source(display));

	al_stop_timer(temporizador);
	al_destroy_event_queue(EventoQueue);
	al_destroy_display(display);
	al_destroy_timer(temporizador);

	al_shutdown_primitives_addon();
	al_shutdown_image_addon();
	al_uninstall_system();

	camera_finaliza(cam);
	ArquivoLog("Jogo finalizado com sucesso!");

	return 0;
}
