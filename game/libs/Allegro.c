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

	ArquivoLog("All file load success.");

	int 						MovDetected 				= 0;
	int 						finalizar 					= 0;
	int 						ciclos 							= 1;
	int 						*coordenadas 				= malloc(2*sizeof(int));
	image 					background 					= newImage(backgroundImg);
	skill						bexiga 							= newSkill(bexigaImage, 10, 50);
	target			 		targetSimple 	 			= newTarget(targetSimpleImg);
	target			 		targetSelected 			= newTarget(targetSelectedI);
	barstatus				hp 						 			= newBar(100, 100, 10, barRed);
	barstatus			 	power 				 			= newBar(100, 100, ALTURA - 10, barBlue);
	// character 			dog 								= newCharacter(dogImg, 100);
	// character 			marvin 							= newCharacter(marvinImg, 100);
	// character 			marvin2 						= newCharacter(marvin2Img, 100);
	// character 			robot 							= newCharacter(robotImg, 100);
	character 			scorp 							= newCharacter(scorpImg, 100);
	ALLEGRO_COLOR 	blue 								= al_map_rgb(0,0,255);
	ALLEGRO_COLOR 	green 							= al_map_rgb(0,255,0);
	ALLEGRO_COLOR 	red 								= al_map_rgb(255,0,0);
	ALLEGRO_COLOR 	circle 							= al_map_rgb(0,255,255);
	ALLEGRO_COLOR 	reset 							= al_map_rgb(0,0,0);
	ALLEGRO_BITMAP 	*buffer 						= al_get_backbuffer(display);
	ALLEGRO_BITMAP 	*esquerda						= al_create_sub_bitmap(buffer, 0, 0, LARGURA, ALTURA);
	ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;
	int *aux= malloc(2*sizeof(int));
	fila_eventos = al_create_event_queue();
	al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
	al_register_event_source(fila_eventos, al_get_mouse_event_source());
	setCharacterSpeed(scorp, 15);
	while(TRUE){
		if(getBar(hp) == 0 || getBar(power) == 0) {
			fprintf(stderr, "%s\n", "Suas bexigas acabaram =(\n não desista, tente novamente" );
		}
	ALLEGRO_EVENT 	evento;
	al_wait_for_event(fila_eventos, &evento);
 
		ciclos++;
		camera_atualiza(cam);
		// MovDetectedCharacter(scorp, TRUE, TRUE);
		camera_copia(cam, cam->quadro, esquerda);
		// drawBackground(background);

		if(Centroid(cam, coordenadas, 1)){
			setPositionTarget(targetSimple, coordenadas[0], coordenadas[1]);
			setPositionTarget(targetSelected, coordenadas[0], coordenadas[1]);
			drawTarget(targetSimple);
			if(getPositionx(targetSimple.imagem) > (getCharacterPositionx(scorp)-60) &&
			   getPositiony(targetSimple.imagem) > (getCharacterPositiony(scorp)-60) &&
			   getPositionx(targetSimple.imagem) < (getCharacterPositionx(scorp)+60) &&
			   getPositiony(targetSimple.imagem) < (getCharacterPositiony(scorp)+60) ) {
				drawTarget(targetSelected);
			}

		}

		if(evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
//		if(Centroid(cam, aux, 0)) {
			setSkillPosition(bexiga, coordenadas[0], coordenadas[1]);
			setSkillActual(bexiga, getSkillActual(bexiga) - 1);
			if(getPositionx(targetSimple.imagem) > (getCharacterPositionx(scorp) -60) &&
			   getPositiony(targetSimple.imagem) > (getCharacterPositiony(scorp) -60) &&
			   getPositionx(targetSimple.imagem) < (getCharacterPositionx(scorp) +60) &&
			   getPositiony(targetSimple.imagem) < (getCharacterPositiony(scorp) +60) ) {
			   hpCharacterDown(scorp, getSkillPower(bexiga));
			 	 reduceBar(hp, 10);
			}
			drawSkill(bexiga);
			reduceBar(power, 5);
		}

		// If entry in warning zone
/*
*/
		if(getCharacterPositionx(scorp) < (LARGURA-(getImageWidth(scorp.imagem)/10)) &&
	   		getCharacterPositionx(scorp) > getImageWidth(scorp.imagem)) {
					setCharacterPosition(scorp, getCharacterPositionx(scorp)+
					  (getCharacterSpeed(scorp)*getCharacterDirectionx(scorp)), getCharacterPositiony(scorp));				
		} else {
				setCharacterDirectionx(scorp, (getCharacterDirectionx(scorp)*(-1)));
				setCharacterPosition(scorp, getCharacterPositionx(scorp)+
				   (getCharacterSpeed(scorp)*getCharacterDirectionx(scorp)), getCharacterPositiony(scorp));
		}

		if(getCharacterPositiony(scorp) < (ALTURA-(getImageHeight(scorp.imagem)/10)) &&
				getCharacterPositiony(scorp) > getImageHeight(scorp.imagem)) {
					setCharacterPosition(scorp, getCharacterPositionx(scorp),
					  getCharacterPositiony(scorp)+(getCharacterSpeed(scorp)*getCharacterDirectiony(scorp)) );
		} else {
				setCharacterDirectiony(scorp, (getCharacterDirectiony(scorp)*(-1)));
				setCharacterPosition(scorp, getCharacterPositionx(scorp),
				   getCharacterPositiony(scorp)+(getCharacterSpeed(scorp)*getCharacterDirectiony(scorp)) );
			}

		//Draw in interface
		drawCharacter(scorp);
		drawStatusBar(hp);
		drawStatusBar(power);
		al_flip_display();
		al_clear_to_color(reset);
	}
	free(aux);
	free(coordenadas);
	clearSkill(bexiga);
	clearTarget(targetSimple);
	clearTarget(targetSelected);
	clearBar(hp);
	clearBar(power);
	// clearCharacter(dog);
	// clearCharacter(marvin);
	// clearCharacter(marvin2);
	// clearCharacter(robot);
	clearCharacter(scorp);
	clearImage(background);
	al_destroy_event_queue(fila_eventos);
	al_destroy_bitmap(backgroundImg);
	al_destroy_bitmap(dogImg);
	al_destroy_bitmap(marvinImg);
	al_destroy_bitmap(marvin2Img);
	al_destroy_bitmap(robotImg);
	al_destroy_bitmap(scorpImg);
	al_destroy_bitmap(bexigaImage);
	al_destroy_bitmap(targetSimpleImg);
	al_destroy_bitmap(targetSelectedI);
	
	return 0;
}
