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
	ALLEGRO_BITMAP *backgroundImg		= al_load_bitmap("res/img/background.jpg");
	ALLEGRO_BITMAP *bexigaImage			= al_load_bitmap("res/img/bexiga.png");
	ALLEGRO_BITMAP *dogImg		 			= al_load_bitmap("res/img/dog.png");
	ALLEGRO_BITMAP *marvinImg 			= al_load_bitmap("res/img/marvin.png");
	ALLEGRO_BITMAP *marvin2Img 			= al_load_bitmap("res/img/marvin2.png");
	ALLEGRO_BITMAP *scorpImg	 			= al_load_bitmap("res/img/scorp.png");
	ALLEGRO_BITMAP *robotImg				= al_load_bitmap("res/img/robot.png");
	ALLEGRO_BITMAP *targetSimpleImg	= al_load_bitmap("res/img/target.png");
	ALLEGRO_BITMAP *targetSelectedI	= al_load_bitmap("res/img/target1.png");
	ALLEGRO_BITMAP *barRed 					= al_load_bitmap("res/img/hpBar.png");
	ALLEGRO_BITMAP *barBlue 				= al_load_bitmap("res/img/powerBar.png");


	if( !backgroundImg || !bexigaImage || !dogImg || !marvinImg || !marvin2Img || !scorpImg || 
	   !robotImg || !targetSimpleImg || !targetSelectedI || !barRed || !barBlue ) {
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
	int 						MovDetected 				= 0;
	int 						finalizar 					= 0;
	int 						ciclos 							= 1;
	int 						aux_x 							= LARGURA/2;
	int							aux_y 							= ALTURA/2;
	int 						*coordenadas 				= malloc(2*sizeof(int));
	image 					background 					= newImage(backgroundImg);
	skill						bexiga 							= newSkill(bexigaImage, 10, 50);
	target			 		targetSimple 	 			= newTarget(targetSimpleImg);
	target			 		targetSelected 			= newTarget(targetSelectedI);
	barstatus				hp 						 			= newBar(100, 100, 10, barRed);
	barstatus			 	power 				 			= newBar(100, 100, 60, barBlue);
	character 			dog 								= newCharacter(dogImg, 100);
	character 			marvin 							= newCharacter(marvinImg, 100);
	character 			marvin2 						= newCharacter(marvin2Img, 100);
	character 			scorp 							= newCharacter(scorpImg, 100);
	character 			robot 							= newCharacter(robotImg, 100);
	ALLEGRO_COLOR 	blue 								= al_map_rgb(0,0,255);
	ALLEGRO_COLOR 	green 							= al_map_rgb(0,255,0);
	ALLEGRO_COLOR 	red 								= al_map_rgb(255,0,0);
	ALLEGRO_COLOR 	circle 							= al_map_rgb(0,255,255);
	ALLEGRO_COLOR 	reset 							= al_map_rgb(0,0,0);
	ALLEGRO_BITMAP 	*buffer 						= al_get_backbuffer(display);
	ALLEGRO_BITMAP 	*esquerda						= al_create_sub_bitmap(buffer, 0, 0, LARGURA, ALTURA);
	ALLEGRO_EVENT 	evento;

	while(TRUE){
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
		MovDetected = Centroid(cam, coordenadas);

		if(MovDetected){
			setPositionTarget(targetSimple, coordenadas[0], coordenadas[1]);
		}
		// drawBackground(background);
		camera_copia(cam, cam->quadro, esquerda);
		drawStatusBar(hp);
		drawStatusBar(power);
		drawCharacter(marvin);
		drawTarget(targetSimple);
		al_flip_display();
		al_clear_to_color(reset);
	}

	free(coordenadas);
	clearSkill(bexiga);
	clearTarget(targetSimple);
	clearTarget(targetSelected);
	clearBar(hp);
	clearBar(power);
	clearCharacter(dog);
	clearCharacter(marvin);
	clearCharacter(marvin2);
	clearCharacter(scorp);
	clearCharacter(robot);
	clearImage(background);
	al_unregister_event_source(EventoQueue, al_get_timer_event_source(temporizador));
	al_unregister_event_source(EventoQueue, al_get_display_event_source(display));
	al_stop_timer(temporizador);
	al_destroy_bitmap(backgroundImg);
	al_destroy_bitmap(dogImg);
	al_destroy_bitmap(marvinImg);
	al_destroy_bitmap(marvin2Img);
	al_destroy_bitmap(robotImg);
	al_destroy_bitmap(scorpImg);
	al_destroy_bitmap(bexigaImage);
	al_destroy_bitmap(targetSimpleImg);
	al_destroy_bitmap(targetSelectedI);
	al_destroy_timer(temporizador);
	al_destroy_event_queue(EventoQueue);
	
	return 0;
}
