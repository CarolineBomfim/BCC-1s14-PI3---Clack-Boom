#ifndef _G_
#define _G_

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
					fprintf(stderr, "%f\n", (double)borda[y][x]);
				}
				else if (divisor > borda[x][y]){
					borda[y][x] = 0;
				}
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
#endif