#ifndef _TratamentoDaImagem_H_
#define _TratamentoDaImagem_H_
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
int altura);
#endif