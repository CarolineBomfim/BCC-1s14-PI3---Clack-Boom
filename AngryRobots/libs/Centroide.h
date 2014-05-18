#ifndef _CENTROID_H_
#define _CENTROID_H_

void Centroid(unsigned char **imagem, int altura, int largura, int *coordenada){
	int markx = 0, marky = 0, cn = 0;
	for(int a = 0; a< altura; a++){
		for(int b = 0; b < largura; b++){
			if(imagem[a][b] == 255){
				markx += b;
				marky += a;
				cn++;
			}
		}
	}
	if( cn > 0){
		coordenada[0] = markx / cn;
		coordenada[1] = marky / cn;
	}
}

#endif