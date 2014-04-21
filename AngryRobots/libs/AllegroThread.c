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
#include "OpenCVThread.h"
typedef struct {
	double x, y;
	camera *cam;
} XY;
void Ball(camera *cam);
void *Allegro(){	
		camera *cam = camera_inicializa(0);
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

	ALLEGRO_BITMAP *background = al_load_bitmap("../res/img/bg_f1.jpg");
	ALLEGRO_BITMAP *bomb = al_load_bitmap("../res/img/bomb.png");
	ALLEGRO_BITMAP *ball = al_load_bitmap("../res/img/ball.png");
	ALLEGRO_BITMAP *robot = al_load_bitmap("../res/img/robot.png");
	ALLEGRO_BITMAP *target = al_load_bitmap("../res/img/target.png");

	if(!background || !bomb ||!ball || !robot || !target){
		erro("Falha ao carregar bitmap.");
	}
	ArquivoLog("Sucesso ao carregar e criar fonte, imagens e eventos.");

	al_register_event_source(EventoQueue, al_get_timer_event_source(temporizador));
	al_register_event_source(EventoQueue, al_get_display_event_source(display));

	ArquivoLog("Registro de eventos!");

	al_start_timer(temporizador);	
	// al_draw_scaled_bitmap(background,
	//  0, 0, 
	//  /*Tamanhao em escala horizontal que a imagem deve se ajustar*/al_get_bitmap_width(background), 
	//  Tamanho em escala altura que a imagem deve se ajustaral_get_bitmap_height(background),
	//  0, 0,
	//  /*Largura que a imagem irá se adequar*/ (float)posicao_x,
	//  /*Altura que a imagem irá se adequar*/(float)posicao_y, 0);
	
	Ball(cam);
	camera_finaliza(cam);
	al_unregister_event_source(EventoQueue, al_get_timer_event_source(temporizador));
	al_unregister_event_source(EventoQueue, al_get_display_event_source(display));
	al_stop_timer(temporizador);
	al_destroy_bitmap(background);
	al_destroy_bitmap(bomb);
	al_destroy_bitmap(ball);
	al_destroy_bitmap(robot);
	al_destroy_bitmap(target);
	al_destroy_timer(temporizador);
	al_destroy_event_queue(EventoQueue);
	al_destroy_display(display);
	
}

void Ball(camera *cam){
	camera_atualiza(cam);
	int raio = 50;
	int aux_x = LARGURA/2;
	int aux_y = ALTURA/2;
	int direcao_y = 1;
	int direcao_x = 1;
	int result = Bomb();
	int *coordenadas = malloc(sizeof(int));
	while(1){
		captura(cam, coordenadas);
		al_draw_circle(coordenadas[0],coordenadas[1], 100, al_map_rgb(0,255,0), 1);
		
		if(result%3 <= 2){
			al_draw_filled_circle(aux_x, aux_y, raio, al_map_rgb(255,0,0));
		}
		else{
			al_draw_filled_circle(aux_x, aux_y, raio, al_map_rgb(0,0,255));
		}
		al_flip_display();
		al_clear_to_color(al_map_rgb(0,0,0));
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
		al_rest(0.0000001);
	}
	free(coordenadas);
}

void captura(camera *cam, int *coordenadas){
	camera_atualiza(cam);
	//Iniciando
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

      if(
         (r > 200)
         &&
         (b > 75)
         &&
         (g > 75)
         ) {
				marca_y += y;
				marca_x += x;
				cn++;

			}

			else{
				marca_y = marca_y;
				marca_x = marca_x;
			}
		}
	}
	if(cn > 0){
		coordenadas[0] = marca_x / cn;
		coordenadas[1] = marca_y / cn;
	}
}