#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "ArquivoLog.h"
#include "camera.h"
#include "define.h"
struct XY{
	double x;
	double y;
};

/*
void *OpenCV(){
	//O camera inicializa pode ser modificado, 0 a camera primeria 1 a secundaria e assim por diante.
	camera *cam = camera_inicializa(0);
	ALLEGRO_COLOR cor = al_map_rgb_f(0, 0, 1);
	if(!cam){
		ArquivoLog("Erro ao iniciar a camera.\n");
	}
	unsigned char ***CAMERA = camera_aloca_matriz(cam);
	while(1){
		camera_atualiza(cam);
		float marca_x = 0;
		float marca_y = 0;
		int cn = 0;
		int y = 0;
		int x = 0;
		for(y = 0; y< ALTURA; y++){
			for(x = 0; x < LARGURA; x++){
				int r = cam->quadro[y][x][0];
				int g = cam->quadro[y][x][1];
				int b = cam->quadro[y][x][2];

				if(r > 200 && g < 200 && b < 200){
					marca_x += x;
					marca_y += y;
					cn++;
				}
			}
		}
		if(cn > 0){
			al_draw_circle(marca_x / cn, marca_y / cn, 100, cor, 1);
		}
	}
	camera_libera_matriz(cam, CAMERA);	
	camera_finaliza(cam);
}
*/

void *OpenCV(void *xy){

	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_BITMAP *background = NULL;

//Iniciando

	camera *cam = camera_inicializa(0);
	if(!cam)
		fprintf(stderr,"Erro ao iniciar a camera.");

	// int LARGURA = cam->largura;
	// int ALTURA = cam->altura;

	if(!al_init())
		fprintf(stderr,"Falha ao iniciar o Allegro.");

	if(!al_init_image_addon())
		fprintf(stderr,"Falha ao iniciar a biblioteca de imagens do Allegro.");

	if(!al_init_primitives_addon())
		fprintf(stderr,"Falha ao carregar primitive_addons.");
	
	display = al_create_display(LARGURA, ALTURA);
	if(!display)
		fprintf(stderr,"Falha ao criar display.");

	background = al_create_bitmap(LARGURA, ALTURA);
	if(!background)
		fprintf(stderr,"Falha ao criar bitmap brackground.");

	ALLEGRO_TIMER *temporizador = al_create_timer(1.0/FPS);
	if(!temporizador)
		fprintf(stderr,"Falha ao criar temporizador.");

	ALLEGRO_EVENT_QUEUE *EventoQueue = al_create_event_queue();
	if(!EventoQueue)
		fprintf(stderr,"Falha ao criar evento QUEUE");


	fprintf(stderr,"Sucesso ao carregar e criar fonte, imagens e eventos.");

	al_register_event_source(EventoQueue, al_get_timer_event_source(temporizador));
	al_register_event_source(EventoQueue, al_get_display_event_source(display));

	fprintf(stderr,"Registro de eventos!");

	al_start_timer(temporizador);
    // Todas as bibliotecas e arquivos foram carregados com sucesso!
	fprintf(stderr,"Passou pelo start_timer");

	unsigned char ***matriz = camera_aloca_matriz(cam);

	ALLEGRO_BITMAP *buffer = al_get_backbuffer(display);
	ALLEGRO_BITMAP *esquerda = al_create_sub_bitmap(buffer, 0, 0, LARGURA, ALTURA);

    
	fprintf(stderr,"Sucesso ao criar buffers bitmap!");
	int laco = 0;
	int marca_rastreada = 0;
// Esse while esta esperando o movimento ou o clique no 'X'
//
	while(1){
		ALLEGRO_EVENT evento;

		al_wait_for_event(EventoQueue, &evento);
		switch(evento.type){
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
			  laco = 1;
			fprintf(stderr,"Finalizado pelo usuario!");
			break;

			case ALLEGRO_EVENT_TIMER:
			marca_rastreada = 1;
			break;
			
			default:
			fprintf(stderr,"Evento desconhecido!");
		}

		if(laco == 1)
			break;
		
		if(marca_rastreada && al_is_event_queue_empty(EventoQueue)) {
			camera_atualiza(cam);

			float marca_x = 0;
			float marca_y = 0;
			
			int cn = 0;
			int y = 0;
			int x = 0;
            //Esse for esta fazendo a atualizacao da tela por frame, dessa forma ele esta atualizando os pixels de cor que esta identificando
			for(y = 0; y < ALTURA; y++){
				for(x = 0; x < LARGURA; x++){
          //Essas variaveis estao recebendo o valor que a camera esta pegando, ou seja o valor rastreado por cada cor
          int r = cam->quadro[y][x][0];
          int g = cam->quadro[y][x][1];
          int b = cam->quadro[y][x][2];
                    
          // Aqui e definido qual as tonalidades de cor que sao captadas
					// r = Red
          // g = Green
          // b = Blue
          // RGB e uma combinacao de cores que definem um tom
          // Esse tom sera rastreado, isso e somente um exemplo
          // Mas e possivel pegar a grande maioria de tons reais.
          // Mas na tela sao pegos todos os tons!
          if(
             (r > 50 && r < 200)
             &&
             (b > 50 && b < 200)
             &&
             (g > 50 && g < 200)
             ) {
						marca_y += y;
						marca_x += x;
						cn++;
            //Aqui esta sendo definido as cores da tela a direita
            //Ou seja, a replica em apenas duas cores
            // r = 255 = vermelho
            // g = 255 = verde
            // b = 255 = azul
            // matriz[y][x][0] = 255; = vermelho
						// matriz[y][x][1] = 255; = verde
						// matriz[y][x][2] = 255; = azul
            // Isso e igual ao preto
						matriz[y][x][0] = 255;
						matriz[y][x][1] = 255;
						matriz[y][x][2] = 255;
					}

					else{
            // Isso e igual ao branco
						matriz[y][x][0] = 0;
						matriz[y][x][1] = 0;
						matriz[y][x][2] = 0;
					}

				}
			}
			camera_copia(cam, matriz, esquerda);

			ALLEGRO_COLOR cor = al_map_rgb_f(0, 0, 1);
			
			struct XY *aux = xy;
			struct XY *resultado = malloc(sizeof(struct XY));
			if(cn > 0){
				al_draw_circle(marca_x / cn, marca_y / cn, 100, cor, 1);
				resultado->x = marca_x / cn;
				resultado->y = marca_y / cn;
				return ((void *)resultado);
			}
			
			al_flip_display();
		}
	}
	al_destroy_bitmap(esquerda);

	camera_libera_matriz(cam, matriz);	
	
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
	fprintf(stderr,"Jogo finalizado com sucesso!");
}