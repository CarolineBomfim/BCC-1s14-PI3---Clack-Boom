#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "start.h"
#include "define.h"
#include "Aleatorio.h"
#include "ArquivoLog.h"

void Ball(){
	int raio = 50;
	int aux_x = LARGURA/2;
	int aux_y = ALTURA/2;
	int direcao_y = 1;
	int direcao_x = 1;
	int result = Bomb();
	while(1){
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
}
void *Allegro(ALLEGRO_THREAD *trd, void* argumentos){	
	StartGame();
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
	Ball();
	
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
	EndGame();
}