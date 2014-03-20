#include "ArquivoLog.h"
#include "../camera.h"
#include "libs.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>

void TratamentoDaImagem(unsigned char ***matriz, camera *cam,
ALLEGRO_BITMAP *esquerda,
ALLEGRO_BITMAP *direita){
	camera_atualiza(cam);
    float x_0 = ALTURA / 3;
    float x_1 = 2*(ALTURA / 3);
    float x_2 = ALTURA;
    float y_0 = LARGURA / 3;
    float y_1 = 2*(LARGURA / 3);
    float y_2 = LARGURA;
	int r = 0;
	int g = 0;
	int b = 0;
	int x = 0;
	int y = 0;
	int mark = 0;
	float mark_x, mark_y;
	for(y = 0; y < ALTURA; y++){
		for(x = 0; x < LARGURA; x++){
			//Essa atribuição define os valores respectivos de cada cor
			r = cam->quadro[y][x][0];
			g = cam->quadro[y][x][1];
			b = cam->quadro[y][x][2];	
			//Nesse ponto é feita toda a identificação de posicionamento independente do que está sendo rastreado
			//A identificação que estou fazendo é puramente com base na cor
		    if((r > 190) && (g < 128) && (b < 128)) {
		    	mark_x += x;
		    	mark_y += y;
		    	mark++;
			
			    //Aqui esta sendo definido as cores da tela a direita
			    //Ou seja, a replica em apenas duas cores
			    // r = 255 = vermelho
			    // g = 255 = verde
			    // b = 255 = azul
			    // matriz[y][x][0] = 255; = vermelho
				// matriz[y][x][1] = 255; = verde
				// matriz[y][x][2] = 255; = azul
		
				matriz[y][x][0] = 0;
				matriz[y][x][1] = 255;
				matriz[y][x][2] = 255;

			}
			
			else{
				matriz[y][x][0] = 255;
				matriz[y][x][1] = 255;
				matriz[y][x][2] = 255;
			}
		}
	}
	camera_copia(cam, matriz, direita);
	if( mark > 0){
    	ALLEGRO_COLOR marcacao = al_map_rgb_f(1, 0, 0);
    	//ALLEGRO_COLOR marcacao2 = al_map_rgb_f(1, 0, 0);
        al_draw_circle((mark_x/mark)+LARGURA, (mark_y/mark), 50, marcacao, 1);
        //printf("mark_x/mark = %f\tmark_y/mark = %f\n",mark_x/mark, mark_y/mark);
        //al_draw_circle((mark_x/mark), (mark_y/mark), 50, marcacao2, 1);

        if((mark_x / mark) < x_0){
        	printf("Cordenada do alvo: X = 0 - ");
        	if((mark_y / mark) < y_0){
        		printf("Y = 0\n");
        	}

        	else if((mark_y / mark) < y_1 && (mark_y / mark) > y_0 ){
        		printf("Y = 1\n");
        	}

        	else if((mark_y / mark) < y_2 && (mark_y / mark) > y_1){
        		printf("Y = 2\n");
        	}
        }

        else if((mark_x / mark) < x_1 && (mark_x / mark) > x_0){
        	printf("Condenada do alvo: X = 1 - ");
        	if((mark_y / mark) < y_0){
        		printf("Y = 0\n");
        	}

        	else if((mark_y / mark) < y_1 && (mark_y / mark) > y_0 ){
        		printf("Y = 1\n");
        	}

        	else if((mark_y / mark) < y_2 && (mark_y / mark) > y_1){
        		printf("Y = 2\n");
        	}
        }

        else if((mark_x / mark) < x_2 && (mark_x / mark) > y_1){
        	printf("Condenada do alvo: X = 2 - ");
			if((mark_y / mark) < y_0){
        		printf("Y = 0\n");
        	}

        	else if((mark_y / mark) < y_1 && (mark_y / mark) > y_0 ){
        		printf("Y = 1\n");
        	}

        	else if((mark_y / mark) < y_2 && (mark_y / mark) > y_1){
        		printf("Y = 2\n");
        	}
        }
	}
	camera_copia(cam, cam->quadro, esquerda);
	al_flip_display();
	return;
}
