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
#include "ArquivoLog.h"
#include "camera.h"
#include "images.h"
#include "status_bar.h"
#include "targets.h"
#include "characters.h"
#include "start.h"
#include "Aleatorio.h"
#include "Centroide.h"
#include "skills.h"

#define TRUE 1
#define FALSE 0
#define FPS 180.0

int Allegro(camera *cam, ALLEGRO_DISPLAY *display){	
    
	int LARGURA = cam->largura;
	int ALTURA = cam->altura;
	
	ALLEGRO_TIMER *temporizador = al_create_timer(1.0/FPS);
	if(!temporizador){
		erro("Falha ao criar temporizador.");
	} else {
		ArquivoLog("Temporizador criado com sucesso");
	}

	ALLEGRO_EVENT_QUEUE *EventoQueue = al_create_event_queue();
	if(!EventoQueue){
		erro("Falha ao criar evento QUEUE");
	} else {
		ArquivoLog("Evento QUEUE criado com sucesso.");
	}

	// ALLEGRO_SAMPLE *sample = al_load_sample("res/song/dispara.wav");;
	ALLEGRO_FONT 	 *Comics 					= al_load_font("res/fonts/comic.ttf", 20, 0);
	ALLEGRO_BITMAP *background 			= al_load_bitmap("res/img/background.jpg");
	ALLEGRO_BITMAP *bexigaImage			= al_load_bitmap("res/img/bexiga.png");
	ALLEGRO_BITMAP *robotImage 			= al_load_bitmap("res/img/robot.png");
	ALLEGRO_BITMAP *targetSimpleImg	= al_load_bitmap("res/img/target.png");
	ALLEGRO_BITMAP *targetSelectedI	= al_load_bitmap("res/img/target1.png");
	ALLEGRO_BITMAP *barRed 					= al_load_bitmap("res/img/hpBar.png");
	ALLEGRO_BITMAP *barBlue 				= al_load_bitmap("res/img/powerBar.png");


	if(/*!background || !bomb ||*/ !bexigaImage || !robotImage
			|| !targetSimpleImg || !targetSelectedI){
		erro("Falha ao carregar bitmap.");
	} else {
		ArquivoLog("Bitmaps carregados com sucesso.");
	}

	// if(!sample){
	// 	erro("Falha ao carregar audio.");
	// } else {
	// ArquivoLog("Audios carregados com sucesso.");
	// }

	ArquivoLog("Sucesso ao carregar e criar fonte, imagens e eventos.");

	al_register_event_source(EventoQueue, al_get_timer_event_source(temporizador));
	al_register_event_source(EventoQueue, al_get_display_event_source(display));

	al_start_timer(temporizador);

	int 						finalizar 					= 0;
	int 						ciclos 							= 1;
	int 						aux_x 							= LARGURA/2;
	int							aux_y 							= ALTURA/2;
	int 						*coordenadas 				= malloc(2*sizeof(int));
	skill						bexiga 							= newSkill(bexigaImage, 10, 50);
	target			 		targetSimple 	 			= newTarget(targetSimpleImg);
	target			 		targetSelected 			= newTarget(targetSelectedI);
	barstatus				hp 						 			= newBar(100, 100, 10, barRed);
	barstatus			 	power 				 			= newBar(100, 100, 60, barBlue);
	character 			robot					 			= newCharacter(robotImage, 100);
	ALLEGRO_COLOR 	blue 								= al_map_rgb(0,0,255);
	ALLEGRO_COLOR 	green 							= al_map_rgb(0,255,0);
	ALLEGRO_COLOR 	red 								= al_map_rgb(255,0,0);
	ALLEGRO_COLOR 	circle 							= al_map_rgb(0,255,255);
	ALLEGRO_COLOR 	reset 							= al_map_rgb(0,0,0);
	ALLEGRO_BITMAP 	*buffer 						= al_get_backbuffer(display);
	ALLEGRO_BITMAP 	*esquerda						= al_create_sub_bitmap(buffer, 0, 0, LARGURA, ALTURA);

	while(TRUE){
		ALLEGRO_EVENT evento;
		al_wait_for_event(EventoQueue, &evento);
		switch(evento.type){
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				finalizar = 1;
				ArquivoLog("Finalizado pelo usuario!");
				break;

			default:
				break;
		}

		if(finalizar == 1){
			return 1;
		}

		camera_atualiza(cam);
		int MovDetected = Centroid(cam, coordenadas);

		if(MovDetected){
			setPositionTarget(targetSimple, coordenadas[0], coordenadas[1]);
		}
		camera_copia(cam, cam->quadro, esquerda);
		drawStatusBar(hp);
		drawStatusBar(power);
		drawTarget(targetSimple);
		al_flip_display();
		al_clear_to_color(reset);
	}

	free(coordenadas);
	clearSkill(bexiga);
	clearCharacter(robot);
	clearTarget(targetSimple);
	clearTarget(targetSelected);
	clearBar(hp);
	clearBar(power);
	al_unregister_event_source(EventoQueue, al_get_timer_event_source(temporizador));
	al_unregister_event_source(EventoQueue, al_get_display_event_source(display));
	al_stop_timer(temporizador);
	al_destroy_bitmap(background);
	al_destroy_bitmap(bexigaImage);
	al_destroy_bitmap(robotImage);
	al_destroy_bitmap(targetSimpleImg);
	al_destroy_bitmap(targetSelectedI);
	al_destroy_timer(temporizador);
	al_destroy_event_queue(EventoQueue);
	
	return 0;
}
