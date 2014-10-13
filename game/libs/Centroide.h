#ifndef _CENTROID_H_
#define _CENTROID_H_
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

void RGB2HSV(int red, int green, int blue, int *h, int *s, int *v);

void histograma(int *h, int *s, int *v);

/*
 * @param *cam é o ponteiro com a largura, altura e a informação da cor por pixel do quadro.
 * @param *coordenada contem o ponto em x e y 
 * A função 
 */

int Centroid(camera *cam, int *coordenada);
#endif
