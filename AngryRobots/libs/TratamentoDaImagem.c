#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "start.h"
#include "ArquivoLog.h"
#include "camera.h"
#include "AllegroThread.h"
#include "MedianDetection.h"
#include "BorderDetected.h"
// #include "define.h"
#define FPS 60.0


void TratamentoDaImagem(
camera *cam,
ALLEGRO_BITMAP *esquerda,
ALLEGRO_BITMAP *direita,
ALLEGRO_EVENT_QUEUE *EventoQueue,
ALLEGRO_TIMER *temporizador,
ALLEGRO_DISPLAY *display,
unsigned char ***CAMERA,
int *coordenada,
int largura,
int altura){

	al_register_event_source(EventoQueue, al_get_timer_event_source(temporizador));
	al_register_event_source(EventoQueue, al_get_display_event_source(display));
	
	int x = 0;
	int y = 0;
	double gray = 0;
	unsigned char **imagem = malloc(altura*sizeof(unsigned char *));
	for(int a = 0; a < altura; a++){
		imagem[a] = malloc(largura*sizeof(unsigned char));
	}
	while(1){
		camera_atualiza(cam);
		for(y = 0; y < altura; y++){
			for(x = 0; x < largura; x++){
				//Zona de tratamento
				/*-----------------*/
	
				//Mudança do padrão de cor para ignorar a luz
				gray = ((cam->quadro[y][x][0] * 0.2126)+(cam->quadro[y][x][1] * 0.7154)+(cam->quadro[y][x][2] * 0.0722));
				imagem[y][x] = gray;
				cam->quadro[y][x][0] = imagem[y][x]; 
				cam->quadro[y][x][1] = imagem[y][x]; 
				cam->quadro[y][x][2] = imagem[y][x]; 
				// Calculo da Mediana e Borda
			}
		}
		// borda(imagem, altura, largura);
		limiar(imagem, altura, largura);
		mediana(imagem, altura, largura);
		for(y = 0; y < altura; y++){
			for(x = 0; x < largura; x++){
				/*----------------*/			
				//Define a imagem que irá sair no fim
				CAMERA[y][x][0] = imagem[y][x];
				CAMERA[y][x][1] = imagem[y][x];
				CAMERA[y][x][2] = imagem[y][x];
			}
		}
		camera_copia(cam, CAMERA, direita);
		camera_copia(cam, cam->quadro, esquerda);
		al_flip_display();
	}
	for(int a = 0; a < altura; a++){
		free(imagem[a]);
	}free(imagem);
	coordenada[0] =(int) largura/2;
	coordenada[1] =(int) altura/2;
	return;
}

int main(){

	StartGame();
	camera *cam = camera_inicializa(1);
	int LARGURA = cam->largura;
	int ALTURA = cam->altura;
	
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_BITMAP *background = NULL;

	display = al_create_display(2*LARGURA, ALTURA);
	if(!display)
		

	background = al_create_bitmap(LARGURA, ALTURA);
	if(!background){
		
	}

	ALLEGRO_TIMER *temporizador = al_create_timer(1.0/FPS);
	if(!temporizador){
		
	}

	ALLEGRO_EVENT_QUEUE *EventoQueue = al_create_event_queue();
	if(!EventoQueue){
		
	}

	
	al_register_event_source(EventoQueue, al_get_timer_event_source(temporizador));
	al_register_event_source(EventoQueue, al_get_display_event_source(display));

	

	al_start_timer(temporizador);
    // Todas as bibliotecas e arquivos foram carregados com sucesso!
	

	unsigned char ***matriz = camera_aloca_matriz(cam);

	ALLEGRO_BITMAP *buffer = al_get_backbuffer(display);
	ALLEGRO_BITMAP *esquerda = al_create_sub_bitmap(buffer, 0, 0, LARGURA, ALTURA);
	ALLEGRO_BITMAP *direita = al_create_sub_bitmap(buffer, LARGURA, 0, LARGURA, ALTURA);
	int *coordenada = malloc(2*sizeof(int));
	
	TratamentoDaImagem(cam, esquerda, direita, EventoQueue, temporizador, display, matriz, coordenada, LARGURA, ALTURA);

	free(coordenada);
	al_destroy_bitmap(direita);
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
	
	EndGame();
}