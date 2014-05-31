#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
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
#include "game.h"
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

	al_start_timer(temporizador);	
	// al_draw_scaled_bitmap(background,
	//  0, 0, 
	//  /*Tamanhao em escala horizontal que a imagem deve se ajustar*/al_get_bitmap_width(background), 
	//  Tamanho em escala ALTURA que a imagem deve se ajustaral_get_bitmap_height(background),
	//  0, 0,
	//  /*Largura que a imagem irá se adequar*/ (float)posicao_x,
	//  /*Altura que a imagem irá se adequar*/(float)posicao_y, 0);

	int *coordenadas = malloc(2*sizeof(int));
	camera_atualiza(cam);
	// ------------------------------------------------------------------------------------------//
	ALLEGRO_BITMAP *background = al_load_bitmap("../res/img/bg_f1.jpg");
	ALLEGRO_BITMAP *robot = al_load_bitmap("../res/img/robot.png");
	ALLEGRO_COLOR White = al_map_rgb(255, 255, 255);
	ALLEGRO_COLOR Red = al_map_rgb(255, 0, 0);
	ALLEGRO_FONT *Comics = al_load_font("../res/fonts/comic.ttf", 20, 0);
	if(!Comics){
		fprintf(stderr, "Erro ao carregar fonte\n");
		exit(EXIT_FAILURE);
	}
	int loops = LARGURA;
	int hp_robo = 100;
	int velocidade_robo = 60;
	int power = 100;
	int velocidade_power = 10;
	int robo_x = 0;
	int x = 0;
	int y = 0;
	int ciclos = 0;
	double gray = 0;
	unsigned char **imagem = malloc(ALTURA*sizeof(unsigned char *));
	int ***registro = malloc(ALTURA*sizeof(int **));
	for(int a = 0; a < ALTURA; a++){
		registro[a] = malloc(LARGURA*sizeof(int *));
		for(int b = 0; b < LARGURA; b++){
			registro[a][b] = malloc(loops*sizeof(int));
		}
		imagem[a] = malloc(LARGURA*sizeof(unsigned char));
	}

	while(1){
		al_clear_to_color(White);
		al_draw_bitmap(background,0,0,0);
		camera_atualiza(cam);
		for(y = 0; y < ALTURA; y++){
			for(x = 0; x < LARGURA; x++){
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
		SegmentacaoCorte(imagem, ALTURA, LARGURA);
		ConvexHull(imagem, ALTURA, LARGURA);
		Centroid(imagem, ALTURA, LARGURA, coordenadas);
		// if(ciclos == 20){
		// 	Registra(imagem, ALTURA, LARGURA, registro);
		// }
		// else if(ciclos == 90){
		// 	LimpaTela(imagem, ALTURA, LARGURA, registro);
		// 	ciclos = 0;
		// }
		int newPosition = Bomb();
		if(newPosition > LARGURA){
			newPosition = LARGURA - 100.0;
		}
		else if(newPosition < 0){
			newPosition = 100;
		}
		if(newPosition > robo_x){
			al_draw_bitmap(robot, robo_x, ALTURA/2, 0);
			robo_x+=velocidade_robo;		
		}
		else{
			al_draw_bitmap(robot, robo_x, ALTURA/2, 0);
			robo_x-=velocidade_robo;
		}
		if(colisao(coordenadas, robo_x) == 1){
			hp_robo -= 10;
			velocidade_robo += 10;
			power = 0;
			velocidade_power += 10;
		}
		else{
			power = 0;
			velocidade_power -= 30;
		}
		if(velocidade_robo > 60){
			velocidade_robo = 60;
		}
		else if( velocidade_robo < 10){
			velocidade_robo = 10;
		}
		power+= velocidade_power;
		if(velocidade_power <= 0){
			velocidade_power = 1;
		}
		else if(velocidade_power > 50 ){
			velocidade_power = 50;
		}
		if(power < 100){
			power += velocidade_power;
			if(power > 100){
				power = 100;
			}
		}
		else if(power < 0){
			power = 0;
		}
		if(hp_robo <= 0){
			fprintf(stderr, "congratulation\n");
			break;
		}
		else{
			velocidade_robo += 10;
		}
		ciclos++;
		al_draw_text(Comics,Red, 10.0, 10.0, 0, "rRobo:");
		al_draw_textf(Comics,Red, 70.0, 10.0, 0, "%d%%", hp_robo);
		al_draw_text(Comics, White, LARGURA - (500.0 - 370), ALTURA - 30.0, 0, "Power:");
		al_draw_textf(Comics, White, LARGURA -( 430.0 - 370), ALTURA - 30.0, 0, "%d%%", power);
		al_flip_display();
	}
	for(int a = 0; a < ALTURA; a++){
		free(imagem[a]);
		for(int b = 0; b < LARGURA; b++){
			free(registro[a][b]);
		}
		free(registro[a]);
	}
	free(imagem);
	free(registro);
	free(coordenadas);
	camera_finaliza(cam);
	al_unregister_event_source(EventoQueue, al_get_timer_event_source(temporizador));
	al_unregister_event_source(EventoQueue, al_get_display_event_source(display));
	al_stop_timer(temporizador);
	al_destroy_timer(temporizador);
	al_destroy_event_queue(EventoQueue);
	al_destroy_display(display);
}