#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
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

int Allegro(camera *cam, ALLEGRO_DISPLAY *display){	
	
	int LARGURA = cam->largura;
	int ALTURA = cam->altura;

	ALLEGRO_TIMER *temporizador = al_create_timer(1.0/FPS);
	if(!temporizador)
		erro("Falha ao criar temporizador.");

	ALLEGRO_EVENT_QUEUE *EventoQueue = al_create_event_queue();
	if(!EventoQueue)
		erro("Falha ao criar evento QUEUE");

	al_register_event_source(EventoQueue, al_get_timer_event_source(temporizador));
	al_register_event_source(EventoQueue, al_get_display_event_source(display));
	ArquivoLog("Registro de eventos!");
	ALLEGRO_FONT *Comics = al_load_font("../res/fonts/comic.ttf", 20, 0);
	ALLEGRO_BITMAP *background = al_load_bitmap("../res/img/background.jpg");
	ALLEGRO_BITMAP *bexiga = al_load_bitmap("../res/img/bexiga.png");
	ALLEGRO_BITMAP *robot = al_load_bitmap("../res/img/robot.png");
	ALLEGRO_BITMAP *target = al_load_bitmap("../res/img/target.png");
	ALLEGRO_BITMAP *target1 = al_load_bitmap("../res/img/target1.png");
	ALLEGRO_BITMAP *hpBar = al_load_bitmap("../res/img/hpBar.png");
	ALLEGRO_BITMAP *powerBar = al_load_bitmap("../res/img/powerBar.png");


	if(/*!background || !bomb ||*/ !bexiga || !robot || !target || !target1){
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
	//  Tamanho em escala ALTURA que a imagem deve se ajustaral_get_bitmap_height(background),
	//  0, 0,
	//  /*Largura que a imagem irá se adequar*/ (float)posicao_x,
	//  /*Altura que a imagem irá se adequar*/(float)posicao_y, 0);
	int DROBO = 60;
	int ciclos = 0;
	double rVelocidade = 5.0;
	int aux_x = LARGURA/2;
	int aux_y = ALTURA/2;
	int direcao_y = -1;
	int direcao_x = 1;
	int uPower = 0;
	int hpRobo = 100;
	int nBexigas = 25;
	int *coordenadas = malloc(2*sizeof(int));
	// ALLEGRO_COLOR blue = al_map_rgb(0,0,255);
	ALLEGRO_COLOR green = al_map_rgb(0,255,0);
	ALLEGRO_COLOR red = al_map_rgb(255,0,0);
	// ALLEGRO_COLOR bexiga = al_map_rgb(255,0,255);
	// ALLEGRO_COLOR circle = al_map_rgb(0,255,255);
	ALLEGRO_COLOR reset = al_map_rgb(0,0,0);
	// ALLEGRO_BITMAP *buffer = al_get_backbuffer(display);
	// ALLEGRO_BITMAP *esquerda = al_create_sub_bitmap(buffer, 0, 0, LARGURA, ALTURA);
	// ------------------------------------------------------------------------------------------//
	while(1){
		ALLEGRO_EVENT evento;
		int finalizar = 0;
		al_wait_for_event(EventoQueue, &evento);
		switch(evento.type){
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				finalizar = 1;
				ArquivoLog("Finalizado pelo usuario!");
			break;
			default:
			ArquivoLog("Evento desconhecido!");
		}
		if(finalizar == 1){
			return 1;
		}
		int hp;
		int power;
		al_draw_bitmap(background, 0, 0, 0);
		while(1){
			if(((hp/10)*5) >= hpRobo){
				hp = 0;
				break;
			}
			al_draw_bitmap(hpBar, hp, 10,0);
			hp+=30;
		}
		while(1){
			if(((power/10)*5) >= uPower){
				power = 0;
				break;
			}
			al_draw_bitmap(powerBar, power*-(LARGURA-power), 60, 0);
			power+=30;
		}
		ciclos++;
		camera_atualiza(cam);
		// SegmentacaoCorte(imagem, ALTURA, LARGURA);
		int MovDetected = Centroid(cam->quadro, cam->altura, cam->largura, coordenadas);
		al_draw_bitmap(robot, aux_x, aux_y, 0);
		if(MovDetected == 1){
			al_draw_bitmap(target, coordenadas[0] - 30,coordenadas[1] - 30, 0);
		}
		int targetx = coordenadas[0];
		int targety = coordenadas[1];
		if(nBexigas > 0){
			if(uPower == 100){
				al_draw_bitmap(bexiga, coordenadas[0], coordenadas[1], 0);
				nBexigas--;
				if((targetx < aux_x + 30 && targetx > aux_x - 30) && (targety < aux_y + 30 && targety > aux_y - 30)){
					hpRobo-=5;
					al_draw_text(Comics,green, LARGURA/2, ALTURA/2, 0, "Acertou!");
					al_flip_display();
					uPower = 0;
				}
				else{
					uPower = 0;
					al_draw_text(Comics,red, LARGURA/2, ALTURA/2, 0, "Errou!");
					al_flip_display();
				}
			}
		}
		if(nBexigas == 0){
			ArquivoLog("Acabou as bexigas!");
			break;
		}
		if(uPower < 100){
			uPower++;
		}
		if(targetx < aux_x + 50 && targetx > aux_x - 50 && targety < aux_y + 50 && targety > aux_y - 50){
			al_draw_bitmap(target1, coordenadas[0] - 30,coordenadas[1] - 30, 0);
		}
		al_flip_display();
		al_clear_to_color(reset);
		if(aux_x >= LARGURA){
			aux_x -= 10;
		}
		if(aux_y >= ALTURA){
			aux_y -= 10; 

		}
		aux_x += rVelocidade * direcao_x;
		aux_y += rVelocidade * direcao_y;
		if (aux_x > LARGURA - (DROBO + 30)){
			direcao_x = -1;
			aux_x = LARGURA - DROBO;
		}
		else if (aux_x < (DROBO + 30)){
			direcao_x = 1;
			aux_x = DROBO;
		}

		if(aux_y > ALTURA - DROBO){
			direcao_y = -1;
			aux_y = ALTURA - DROBO;
		}
		else if(aux_y < DROBO){
			direcao_y = 1;
			aux_y = DROBO; 	
		}
		if(ciclos == 80){
			ciclos = 0;
			rVelocidade+=5;
		}
		if(rVelocidade == 50){
			break;
		}
		if(aux_y == -1){
			aux_y++;
		}
		else{
			aux_y--;
		}
		if(aux_x == -1){
			aux_x++;
		}
		else{
			aux_x--;
		}
		
	}
	free(coordenadas);
	al_unregister_event_source(EventoQueue, al_get_timer_event_source(temporizador));
	al_unregister_event_source(EventoQueue, al_get_display_event_source(display));
	al_stop_timer(temporizador);
	al_destroy_bitmap(background);
	al_destroy_bitmap(bexiga);
	al_destroy_bitmap(robot);
	al_destroy_bitmap(target);
	al_destroy_bitmap(target1);
	al_destroy_timer(temporizador);
	al_destroy_event_queue(EventoQueue);
	
	return 0;
}