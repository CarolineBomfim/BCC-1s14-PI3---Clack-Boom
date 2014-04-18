#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "ArquivoLog.h"
#include "camera.h"
#include "libs.h"

void borda(unsigned char **imagem, int altura, int largura){
	int x, y;
	double borda1 = 0, borda2 = 0, divisor = 0;
	double **borda = malloc(altura*sizeof(double *));
	for(int a = 0; a<altura; a++){
		borda[a] = malloc(largura*sizeof(double));
	}
	for(y = 0; y < altura; y++){
		for(x = 0; x < largura; x++){
			/*--------------------*/
			//Calculo da borda
			if(y > 0 && y < largura - 1 && x > 0 && x < altura - 1){
				borda1 = imagem[y-1][x-1] - imagem[y-1][x+1];
				borda1 += 2*imagem[y][x-1] - 2*imagem[y][x+1];
				borda1 += imagem[y+1][x-1] - imagem[y][x];
				borda2 = imagem[y-1][x-1] - imagem[y+1][x-1];
				borda2 += imagem[y-1][x] - imagem[y+1][x];
				borda2 += imagem[y-1][x+1] - imagem[y-1][x-1];

				borda[y][x] = sqrt((borda1 * borda1) + (borda2 * borda2));
				if (divisor < borda[x][y]){
					divisor =(float) borda[x][y];
				}
				else if (divisor > borda[x][y]){
					borda[y][x] = 0;
				}
				printf("%f\n", borda[y][x]);
			}
		}
	}
	for (y = 0; y < altura; y++){
		for (x = 0; x < largura; x++){
			imagem[y][x] = (borda[y][x]/divisor) * 255 + 0.5;
		}
	}
	for(int a = 0; a < altura; a++){
		free(borda[a]);
	}
	free(borda);
}

void mediana(unsigned char **imagem, int largura, int altura){
	int x, y;
	for(y = 0; y < altura; y++){
		for(x = 0; x < largura; x++){
			if(y > 0 && y < largura - 1 && x > 0 && x < altura - 1){
			
				//Calculo da mediana
				int aux = 0;
				unsigned char buffer[9];
				for(int dy = -1; dy < 1; dy++){
					for(int dx = -1; dx < 1; dx++, aux++){
						buffer[aux] = imagem[y+dy][x+dx];
					}
				}
				for(aux = 0; aux < 8; aux++){
					for(int l = 0; l < aux; l++){
						if(buffer[l] > buffer[l+1]){
							int n = buffer[l];
							buffer[l] = buffer[l+1];
							buffer[l+1] = n;
						}
					}
				}
				imagem[y][x] = buffer[4];
			}
			else{
				return;
			}
		}
	}
}
void TratamentoDaImagem(
camera *cam,
ALLEGRO_BITMAP *esquerda,
ALLEGRO_BITMAP *direita,
ALLEGRO_EVENT_QUEUE *EventoQueue,
ALLEGRO_TIMER *temporizador,
ALLEGRO_DISPLAY *display,
unsigned char ***CAMERA,
unsigned char ***matriz,
int *cordenada,
int largura,
int altura){

	al_register_event_source(EventoQueue, al_get_timer_event_source(temporizador));
	al_register_event_source(EventoQueue, al_get_display_event_source(display));
	
	int x = 0;
	int y = 0;
	double gray = 0;
	double *RGB = malloc(3*sizeof(double));
	unsigned char **imagem = malloc(altura*sizeof(unsigned char *));
	for(int a = 0; a < altura; a++){
		imagem[a] = malloc(largura*sizeof(unsigned char));
	}
	camera_atualiza(cam);
	for(y = 0; y < altura; y++){
		for(x = 0; x < largura; x++){
			//Essa atribuição define os valores respectivos de cada cor
			RGB[0] = cam->quadro[y][x][0];
			RGB[1] = cam->quadro[y][x][1];
			RGB[2] = cam->quadro[y][x][2];
			imagem[y][x] = RGB[0];
			//Zona de tratamento
			/*-----------------*/

			//Mudança do padrão de cor para ignorar a luz
			gray = ((cam->quadro[y][x][0] * 0.2126)+(cam->quadro[y][x][1] * 0.7154)+(cam->quadro[y][x][2] * 0.0722));
			imagem[y][x] = gray;
			// Calculo da Mediana e Borda
		}
	}
	// mediana(imagem, altura, largura);
	borda(imagem, altura, largura);
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
	free(RGB);
	for(int a = 0; a < altura; a++){
		free(imagem[a]);
	}free(imagem);
	cordenada[0] =(int) largura/2;
	cordenada[1] =(int) altura/2;
	return;
}