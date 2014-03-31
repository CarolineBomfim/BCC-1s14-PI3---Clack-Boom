#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>
#include <stdlib.h>
#include <stdio.h>

#include "ArquivoLog.h"
#include "../camera.h"
#include "libs.h"

double MAXIMO(double r, double g, double b);
double MINIMO(double r, double g, double b);
void RGBparaHSL(double *RGB, double *HSL);
void HSLparaRGB(double *HSL, double *RGB);
void CapturaContorno(double *RGB, camera *cam);

void TratamentoDaImagem(
camera *cam,
ALLEGRO_BITMAP *esquerda,
ALLEGRO_BITMAP *direita,
ALLEGRO_EVENT_QUEUE *EventoQueue,
ALLEGRO_TIMER *temporizador,
ALLEGRO_DISPLAY *display){

	unsigned char ***CAMERA = camera_aloca_matriz(cam);
	unsigned char ***matriz = camera_aloca_matriz(cam);

	al_register_event_source(EventoQueue, al_get_timer_event_source(temporizador));
	al_register_event_source(EventoQueue, al_get_display_event_source(display));
	
	ArquivoLog("Entrou em TratamentoDaImagem");
	
	int largura = cam->largura;
	int altura = cam->altura;

	int EventoDetectado = 0;
	int laco = 0;

	double *RGB =(double *)malloc(3*sizeof(long int));
	double *HSL =(double *)malloc(3*sizeof(long int));
	
	al_register_event_source(EventoQueue, al_get_timer_event_source(temporizador));
	al_register_event_source(EventoQueue, al_get_display_event_source(display));

	while(laco != 1){
	ALLEGRO_EVENT evento;
	al_wait_for_event(EventoQueue, &evento);

	switch(evento.type){
		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			laco = 1;
			ArquivoLog("Finalizado pelo usuario!");
			break;

		case ALLEGRO_EVENT_TIMER:
			EventoDetectado = 1;
			break;
		
		default:
			ArquivoLog("Evento desconhecido!");
	}
	if(laco == 1){
		break;
	}
	
	if(EventoDetectado == 1 && al_is_event_queue_empty(EventoQueue)) {
		EventoDetectado = 0;
		camera_atualiza(cam);
		for(int y = 0; y < altura; y++){
			for(int x = 0; x < largura; x++){
				//Essa atribuição define os valores respectivos de cada cor
				RGB[0] = cam->quadro[y][x][0];
				RGB[1] = cam->quadro[y][x][1];
				RGB[2] = cam->quadro[y][x][2];
				//Zona de tratamento
				//Mudança do padrão de cor para ignorar a luz
				RGBparaHSL(RGB, HSL);
				HSLparaRGB(HSL, RGB);
				
				//Camptando a borda
				
				CAMERA[y][x][0] = RGB[0];
				CAMERA[y][x][1] = RGB[1];
				CAMERA[y][x][2] = RGB[2];
				//Algoritimo de Roberts

				// double BordaRed, Red_Aux1, Red_Aux2;
				// Red_Aux1 =(double) (CAMERA[y][x][0]-CAMERA[y-1][x+1][0]);
				// Red_Aux2 =(double) (CAMERA[y][x][0]-CAMERA[y-1][x-1][0]);
				// Red_Aux1 =(double) Red_Aux1*Red_Aux1;
				// Red_Aux2 =(double) Red_Aux2*Red_Aux2;
				// BordaRed = sqrt(Red_Aux1+Red_Aux2);
				// RGB[0] = (int)BordaRed;
				
				// double BordaGreen, Green_Aux1, Green_Aux2;
				// Green_Aux1 = CAMERA[y][x][0]-CAMERA[y-1][x+1][0];
				// Green_Aux2 = CAMERA[y][x][0]-CAMERA[y-1][x-1][0];
				// BordaGreen = sqrt((Green_Aux1*Green_Aux1)+(Green_Aux2*Green_Aux2));
				// RGB[1] = (int)BordaGreen;
				
				// double BordaBlue, Blue_Aux1, Blue_Aux2;
				// Blue_Aux1 = CAMERA[y][x][0]-CAMERA[y-1][x+1][0];
				// Blue_Aux2 = CAMERA[y][x][0]-CAMERA[y-1][x-1][0];
				// BordaBlue = sqrt((Blue_Aux1*Blue_Aux1)+(Blue_Aux2*Blue_Aux2));
				// RGB[2] = (int)BordaBlue;

				//Fim da zona de tratamento
				//Imagem inauterada para saber a diferença
				matriz[y][x][0] = cam->quadro[y][x][0];
				matriz[y][x][1] = cam->quadro[y][x][1]; 
				matriz[y][x][2] = cam->quadro[y][x][2]; 
				
				//Define a imagem que irá sair no fim
				CAMERA[y][x][0] = RGB[0];
				CAMERA[y][x][1] = RGB[1];
				CAMERA[y][x][2] = RGB[2];
				}
			}
			camera_copia(cam, CAMERA, direita);
			camera_copia(cam, matriz, esquerda);
			al_flip_display();
		}
	}

	free(HSL);
	free(RGB);
	camera_libera_matriz(cam, CAMERA);
	camera_libera_matriz(cam, matriz);
	return;
}


/*
* ------------------------------------------------------------------------------------------ *
* ------------------------------------------------------------------------------------------ *
* ------------------------------------------------------------------------------------------ *
* ------------------------------------------------------------------------------------------ *
* ------------------------------------------------------------------------------------------ *
* ------------------------------------------------------------------------------------------ *
* ------------------------------------------------------------------------------------------ *
* ------------------------------------------------------------------------------------------ *
* ------------------------------------------------------------------------------------------ *
*/


/*
* Calculando qual é o maior nas variaveis r,g,b.
*/
double MAXIMO(double r, double g, double b) {
	if(r >= g && r >= b)
		return r;
	else {
		if(g >= r && g >= b)
			return g;
		else
			if(b >= r && b >= g)
				return b;
	}
	return r;
}

/*
* Calculando qual é o menor nas variaveis r,g,b.
*/

double MINIMO(double r, double g, double b) {
	if(r <= g && r <= b)
		return r;
	else {
		if(g <= r && g <= b)
			return g;
		else
			if(b <= r && b <= g)
				return b;
	}
	return r;
}

/*
* Essa conversão está sendo feita para que 
* possamos ignorar a luz, dessa forma teremos
* um melhor desempenho do rastramento.
*/
void RGBparaHSL(double *RGB, double *HSL) {
	double MAX = MAXIMO(RGB[0], RGB[1], RGB[2]);
	double MIN = MINIMO(RGB[0], RGB[1], RGB[2]);
	double CHROMA = MAX - MIN;
	HSL[2] = 0.5 * (MAX + MIN);

	if(CHROMA != 0.0) {
		if( MAX == RGB[0])
			HSL[0] = fmod(((RGB[1] - RGB[2])/ CHROMA), 6.0);

		else if(MAX == RGB[1])
			HSL[0] = ((RGB[2] - RGB[0]) / CHROMA) + 2.0;

		else if(MAX == RGB[2])
			HSL[0] = ((RGB[0] - RGB[2]) / CHROMA) + 4.0;
	}

	HSL[0] *= 60.0;
	HSL[1] = CHROMA / (1.0 - fabs(2.0 * HSL[2] - 1.0));
}

/*
* Converte HSL para HUE
*/
double HUEparaRGB(double a, double b, double c){
	if(c < 0)
		c += 1;

	if(c > 1)
		c -= 1;

	if(c < 1/6)
		return a + ( b - a) * 6 * c;

	if(c < 1/2)
		return b;

	if( c < 2/3)
		return a + (b - a) * ( 2/3 - c) * 6;

	return a;
}
/*
* Restaurando valores HSL para RGB
*/
void HSLparaRGB(double *HSL, double *RGB) {
	double r;
	double g;
	double b;

	if( HSL[1] == 0) {
		r = HSL[2];
		g = HSL[2];
		b = HSL[2];
	}

	else {
		double q = HSL[2] < 0.5 ? HSL[2] * (1 + HSL[1]) : HSL[2] + HSL[1] - HSL[2] * HSL[1];
		double p = 2 * HSL[2] - q;
		r = HUEparaRGB(p, q, HSL[0] + 1/3);
		g = HUEparaRGB(p, q, HSL[0]);
		b = HUEparaRGB(p, q, HSL[0] - 1/3);
	}

	RGB[0] = r * 255;
	RGB[1] = g * 255;
	RGB[2] = b * 255;

}
/*
void CapturaContorno(double *RGB, camera *cam) {
	double aux1;
	double aux2;
	double DIV = 0;
	float **g;
	g = malloc(altura * sizeof(float *));
	for(i = 0; i < largura; i++){
		g[i] = malloc(largura * sizeof(float *));
		for(j = 0; j < altura; j++){
			aux1 = cam->quadro[i-1][j-1] - cam->quadro[i-1][j+1];
			aux1 += 2*cam->quadro[i][j-1] - 2*cam->quadro[i][j+1];
			aux1 += cam->quadro[i+1][j-1] - cam->quadro[i+1][j+1];
			
			aux2 = cam->quadro[i-1][j-1] - cam->quadro[i+1][j-1];
			aux2 += 2*cam->quadro[i -1][j] - 2*cam->quadro[i+1][j];
			aux2 +=  cam->quadro[i-1][j+1] - cam->quadro[i+1][j+1];

			g[i][j] = sqrt(aux1*aux1 + aux2*aux2);

			if(DIV < g[i][j])
				DIV = g[i][j];

			else
				g[i][j] = 0;
		}
	}
	return;
}*/