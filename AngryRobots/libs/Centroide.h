#ifndef _CENTROID_H_
#define _CENTROID_H_

void Centroid(unsigned char **imagem, int altura, int largura, int *coordenada){
	int markx = 0, marky = 0, cn = 0;
	int x0 = largura/8;
	int y0 = altura/8;
	int x1 = largura - x0;
	int y1 = altura - y0;
	for(int a = y0; a< y1; a++){
		for(int b = x0; b < x1; b++){
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
