#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "start.h"
#include "camera.h"
#include "define.h"
#include "Aleatorio.h"
#include "ArquivoLog.h"
#include "MedianDetection.h"
#include "BorderDetected.h"
#include "SegmentacaoCorte.h"
#include "ConvexHull.h"
#include "Centroide.h"
void captura(camera *cam, int *coordenadas);
void Ball(camera *cam, ALLEGRO_DISPLAY *display);
void Allegro(){	
		camera *cam = camera_inicializa(0);
		int ALTURA = cam->altura;
		int LARGURA = cam->largura;
	if(!cam)
		fprintf(stderr,"Erro ao iniciar a camera.");

	ALLEGRO_DISPLAY *display = al_create_display(LARGURA, ALTURA);
	if(!display)
		erro("Falha ao criar display.");

	ALLEGRO_TIMER *temporizador = al_create_timer(1.0/FPS);
	if(!temporizador)
		erro("Falha ao criar temporizador.");

	ALLEGRO_EVENT_QUEUE *EventoQueue = al_create_event_queue();
	if(!EventoQueue)
		erro("Falha ao criar evento QUEUE");

	al_register_event_source(EventoQueue, al_get_timer_event_source(temporizador));
	al_register_event_source(EventoQueue, al_get_display_event_source(display));
	ArquivoLog("Registro de eventos!");

	// ALLEGRO_BITMAP *background = al_load_bitmap("../res/img/bg_f1.jpg");
	// ALLEGRO_BITMAP *bomb = al_load_bitmap("../res/img/bomb.png");
	// ALLEGRO_BITMAP *ball = al_load_bitmap("../res/img/ball.png");
	// ALLEGRO_BITMAP *robot = al_load_bitmap("../res/img/robot.png");
	// ALLEGRO_BITMAP *target = al_load_bitmap("../res/img/target.png");

	// if(!background || !bomb ||!ball || !robot || !target){
	// 	erro("Falha ao carregar bitmap.");
	// }
	ArquivoLog("Sucesso ao carregar e criar fonte, imagens e eventos.");

	al_register_event_source(EventoQueue, al_get_timer_event_source(temporizador));
	al_register_event_source(EventoQueue, al_get_display_event_source(display));

	ArquivoLog("Registro de eventos!");

	al_start_timer(temporizador);	
	// al_draw_scaled_bitmap(background,
	//  0, 0, 
	//  /*Tamanhao em escala horizontal que a imagem deve se ajustar*/al_get_bitmap_width(background), 
	//  Tamanho em escala ALTURA que a imagem deve se ajustaral_get_bitmap_height(background),
	//  0, 0,
	//  /*Largura que a imagem irá se adequar*/ (float)posicao_x,
	//  /*Altura que a imagem irá se adequar*/(float)posicao_y, 0);
	int raio = 50;
	int aux_x = LARGURA/2;
	int aux_y = ALTURA/2;
	int direcao_y = 1;
	int direcao_x = 1;
	int result = Bomb();
	int *coordenadas = malloc(sizeof(int));
	ALLEGRO_COLOR blue = al_map_rgb(0,0,255);
	ALLEGRO_COLOR green = al_map_rgb(0,255,0);
	ALLEGRO_COLOR red = al_map_rgb(255,0,0);
	ALLEGRO_COLOR ball = al_map_rgb(255,0,255);
	ALLEGRO_COLOR circle = al_map_rgb(0,255,255);
	ALLEGRO_COLOR reset = al_map_rgb(0,0,0);

	ALLEGRO_BITMAP *buffer = al_get_backbuffer(display);
	ALLEGRO_BITMAP *esquerda = al_create_sub_bitmap(buffer, 0, 0, LARGURA, ALTURA);
	camera_atualiza(cam);
	// ------------------------------------------------------------------------------------------//
while(1){
int x = 0;
	int y = 0;
	double gray = 0;
	unsigned char **imagem = malloc(ALTURA*sizeof(unsigned char *));
	for(int a = 0; a < ALTURA; a++){
		imagem[a] = malloc(LARGURA*sizeof(unsigned char));
	}
	
		camera_atualiza(cam);
		for(y = 0; y < ALTURA; y++){
			for(x = 0; x < LARGURA; x++){
				//Zona de tratamento
				/*-----------------*/
	
				//Mudança do padrão de cor para ignorar a luz
				gray = ((cam->quadro[y][x][0] * 0.2126)+(cam->quadro[y][x][1] * 0.7154)+(cam->quadro[y][x][2] * 0.0722));
				imagem[y][x] = gray;
				cam->quadro[y][x][0] = gray;
				cam->quadro[y][x][1] = gray; 
				cam->quadro[y][x][2] = gray; 
			}
		}
		limiar(imagem, ALTURA, LARGURA);
		mediana(imagem, ALTURA, LARGURA);
		ConvexHull(imagem, ALTURA, LARGURA);
		SegmentacaoCorte(imagem, ALTURA, LARGURA);
		Centroid(imagem, ALTURA, LARGURA, coordenadas);
		for(y = 0; y < ALTURA; y++){
			for(x = 0; x < LARGURA; x++){
				/*----------------*/			
				//Define a imagem que irá sair no fim
				cam->quadro[y][x][0] = imagem[y][x];
				cam->quadro[y][x][1] = imagem[y][x];
				cam->quadro[y][x][2] = imagem[y][x];
			}
		}

		camera_copia(cam, cam->quadro, esquerda);
		al_flip_display();
	
	for(int a = 0; a < ALTURA; a++){
		free(imagem[a]);
	}
	free(imagem);	
	// //
	camera_copia(cam, cam->quadro, esquerda);		
	if(result%3 <= 2){
		al_draw_filled_circle(aux_x, aux_y, raio, red);
	}
	else{
		al_draw_filled_circle(aux_x, aux_y, raio, blue);
	}
	al_draw_circle(coordenadas[0],coordenadas[1], raio, circle, 10);
	if((coordenadas[0] <= aux_x+50) && (coordenadas[1] <= aux_y+50)){
		if((coordenadas[0] == aux_x) && (coordenadas[1] == aux_y)){
			al_draw_circle(coordenadas[0],coordenadas[1], raio, ball, 10);
		}
		al_draw_circle(coordenadas[0],coordenadas[1], raio, green, 10);
	}
	else if((coordenadas[0] > aux_x+50) && (coordenadas[1] > aux_y+50)){
		al_draw_circle(coordenadas[0],coordenadas[1], raio, blue, 10);
	}
	al_flip_display();
	al_clear_to_color(reset);
	aux_x += 1.0 * direcao_x;
	aux_y += 1.0 * direcao_y;

	if (aux_x > LARGURA - raio){
		direcao_x = -1;
		aux_x = LARGURA - raio;
	}
	else if ( aux_x < raio){
		direcao_x = 1;
		aux_x = raio;
	}

	if(aux_y > ALTURA - raio){
		direcao_y = -1;
		aux_y = ALTURA - raio;
	}
	else if(aux_y < raio){
		direcao_y = 1;
		aux_y = raio;
	}
	}
	free(coordenadas);
	camera_finaliza(cam);
	al_unregister_event_source(EventoQueue, al_get_timer_event_source(temporizador));
	al_unregister_event_source(EventoQueue, al_get_display_event_source(display));
	al_stop_timer(temporizador);
	// al_destroy_bitmap(background);
	// al_destroy_bitmap(bomb);
	// al_destroy_bitmap(ball);
	// al_destroy_bitmap(robot);
	// al_destroy_bitmap(target);
	al_destroy_timer(temporizador);
	al_destroy_event_queue(EventoQueue);
	al_destroy_display(display);
	
}