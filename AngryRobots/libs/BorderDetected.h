#ifndef _BORDER_H_
#define _BORDER_H_

void borda(unsigned char **imagem, int altura, int largura){
	double divisor = 0;
	double b1 = 0;
	double b2 = 0;
	double x1;
	double x2;
	int x = 0, y = 0;
	for(y = 0; y < altura; y++){
		for(x = 0; x < largura; x++){
			if(y > 0 && y < altura - 1 && x > 0 && x < largura){
				b1 = imagem[y-1][x-1] - imagem[y-1][x+1];
				b1 += 2*imagem[y][x-1] - 2*imagem[y][x+1];
				b1 += imagem[y+1][x-1] - imagem[y+1][x+1];

				b2 = imagem[y-1][x-1] - imagem[y+1][x-1];
				b2 += 2*imagem[y-1][x] - 2*imagem[y+1][x];
				b2 += imagem[y-1][x+1] - imagem[y+1][x+1];
				x1 = b1*b1;
				x2 = b2*b2;
				imagem[y][x] = sqrt(x1+x2);

				if(divisor <= imagem[y][x]){
					divisor = imagem[y][x];
				}
				else{
					imagem[y][x] = 0;
				}
				imagem[y][x] = ((imagem[y][x]/divisor)*128 + 0.5);
			}
		}
	}
}
#endif
