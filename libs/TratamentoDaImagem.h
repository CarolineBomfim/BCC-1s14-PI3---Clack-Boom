#ifndef _TratamentoDaImagem_H_
#define _TratamentoDaImagem_H_

void TratamentoDaImagem(unsigned char ***matriz,
	camera *cam,
	ALLEGRO_BITMAP *esquerda,
	ALLEGRO_BITMAP *direita,
	ALLEGRO_EVENT_QUEUE *EventoQueue);
#endif