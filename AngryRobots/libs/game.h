#ifndef _GAME_H_
#define _GAME_H_

int colisao(int *coordenadas, int robo){
	int x = coordenadas[0];
	int x1 = robo;
	if(x1 == x){
		//Causa dano
		//Reduz barra de vida
		//diminui velocidade
		return 1;
	}
	else{
		//Recupera vida
		//Aumenta barra de vida
		//aumenta velocidade
		return 0;
	}
}
#endif 