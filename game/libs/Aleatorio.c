#include <stdlib.h>
#include <stdio.h>
#include <time.h>
void Coordenadas(int *coordenada){
	int divisor = 20;
	int x = (int)rand() % divisor;
	int y = (int)rand() % divisor;
	if(x <= 0){
		x = 1;
	}
	if(y <= 0){
		y = 1;
	}
	coordenada[0] = x;
	coordenada[1] = y;
}

int Bomb(){return ((int)rand()%20);}