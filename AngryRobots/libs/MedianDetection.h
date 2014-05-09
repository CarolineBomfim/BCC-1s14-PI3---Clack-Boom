#ifndef _H_
#define _H_

void mediana(unsigned char **imagem, int altura, int largura){
	int x, y;
	for(y = 0; y < altura; y++){
		for(x = 0; x < largura; x++){
			if(y > 0 && y < largura - 1 && x > 0 && x < altura - 1){
			
				//Calculo da mediana
				int aux = 0;
				unsigned char buffer[9];
				for(int dy = -1; dy < 1; dy++){
					for(int dx = -1; dx < 1; dx++, aux++){
						buffer[aux] = imagem[y+dy][x+dx];
					}
				}
				for(aux = 0; aux < 8; aux++){
					for(int l = 0; l < aux; l++){
						if(buffer[l] > buffer[l+1]){
							int n = buffer[l];
							buffer[l] = buffer[l+1];
							buffer[l+1] = n;
						}
					}
				}
				imagem[y][x] = buffer[4];
			}
			else{
				return;
			}
		}
	}
}
void limiar(unsigned char **imagem, int altura, int largura){
	int x, y;
	for(y = 0; y < altura; y++){
		for(x = 0; x < largura; x++){
			if(imagem[y][x] < 100){
				imagem[y][x] = 0;
			}
			else if(imagem[y][x] > 175 && imagem[y][x] < 200){
				imagem[y][x] = 0;
			}
			else if(imagem[y][x] > 100 && imagem[y][x] < 175){
				imagem[y][x] = 0;
			}
			else{
				imagem[y][x] = 255;
			}
		}
	}
}
#endif