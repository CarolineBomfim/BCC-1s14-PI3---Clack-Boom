#include <stdlib.h>
#include <stdio.h>
#include <time.h>
int Calc(){
	srand((unsigned)time(NULL));
	int x = 0;
	do{
		x = rand() % 10;
		if(0 < x && x < 4)
			return x;

	}while(1);
}

void IntAleatorio(int *valor){
	//int *valor;
	int x = 0, y = 0;
	do{
		x = Calc();
		y = Calc();
		if( x < 4 && y < 4)
			if(x != y)
				break;
	}while(1);
	valor[0] = x;
	valor[1] = y;
}

//int main(){
//	int *result;
//	result = malloc(sizeof(int));
//	IntAleatorio(result);
//	//result = IntAleatorio();
//	printf("\n%d\t%d\n", result[0], result[1]);
//	free(result);
//	return 0;
//}