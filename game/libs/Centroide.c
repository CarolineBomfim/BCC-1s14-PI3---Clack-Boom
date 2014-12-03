#include <stdlib.h>
#include "camera.h"

#define TRUE 1
#define FALSE 0


/**
* @param red
* @param green
* @param blue
* @param *h
* @param *s
* @param *v
* 
* A RGB2HSV ira dividir cada um dos 3 valores que compoe o rgb
* o calculo feito retorna a saturacao, valor e o hue.
* R/255, G/255 e B/255
* Após a conversão de valores subtrai o menor do maior valor dentre os 3 valores resultantes
* A = Maximo - Minimo;
* São usados para calcular os valores que compõe o HSV
* H é o calculo dentre os valores, se o R for igual ao Maximo, verificase qual dos valores é o maior
* entre G/255 e B/255, o menor desses valores subtrai o maio e o resultado é dividido por A
* após obter o resultado da multiplicação por A, esse resultado é multiplicado por 60 obtendo assim
* a variação de cor.
* s = (A/Maximo) * 100;
* v = Maximo * 100;
*/

void RGB2HSV(int red, int green, int blue, int *h, int *s, int *v){
	float r = (float)red/255;
	float g = (float)green/255;
	float b = (float)blue/255;
	float cMax, cMin;
	if(r >= b && r >= g){
		if(g > b){
			cMin = b;
		}
		else{
			cMin = g;
		}
		cMax = r;
	}
	else if(b >= g){
		if(g > r){
			cMin = r;
		}

		else{
			cMin = g;
		}

		cMax = b;
	}

	else{
		if(r > b){
			cMin = b;
		}

		else{
			cMin = r;
		}

		cMax = g;
	}

	float variacaoCor = cMax - cMin;

	if(variacaoCor != 0){ 
		if(cMax == r){
				if(g >= b){
					*h = 60 * ((g - b) / variacaoCor);
				}
	
				else{
					*h = 60 * ((g - b) / variacaoCor) + 360;
				}

		}
	
		else if(cMax == g){
			*h = 60 * ((b - r) / variacaoCor) + 120;
		}
	
		else{
			*h = 60 * ((r - g) / variacaoCor) + 240;
		}
	}

	else{
		*h = 0;
	}

	*s = variacaoCor/cMax * 100;	
	*v = cMax * 100;
}

/*
 * @param *cam é o ponteiro com a largura, altura e a informação da cor por pixel do quadro.
 * @param *coordenada contem o ponto em x e y 
 * A função 
 */
int Centroid(camera *cam, int *coordenada, int type){
	unsigned char ***imagem = cam->quadro;
	int altura = cam->altura;
	int largura = cam->largura;
	int px = coordenada[0];
	int py = coordenada[1];
	int markx = 0, marky = 0, cn = 0;
	int h, s, v, hsv;
	for(int a = 0; a < altura; a++){
		for(int b = 0; b < largura; b++){
			RGB2HSV(
				imagem[a][b][0],
				imagem[a][b][1],
				imagem[a][b][2],
				&h, &s, &v
			);

			if (type == 1) {
				// red
				hsv = ((h < 25 && s > 75 && v > 75) ? TRUE : FALSE); 
			} else if (type == 0 ){
				// white
				hsv = ((h < 25 && s < 25 && v > 75) ? TRUE : FALSE);
			}

			if(hsv){
				marky += a;
				markx += b;
				cn++;
			}
		}
	}
	if( cn > 0){
		coordenada[0] = markx / cn;
		coordenada[1] = marky / cn;
	}
	if(px == coordenada[0] && py == coordenada[1]){
		return 0;
	}
	return 1;
}
