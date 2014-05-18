#ifndef _SEG_CUT_H_
#define _SEG_CUT_H_
void histograma(unsigned char **imagem, int x0, int x1, int y0, int y1){
	int largura = x1-x0;
	int altura = y1-y0;
	int **histograma = malloc(largura*sizeof(int **));
	for(int a = 0; a+x0 < largura; a++){
		histograma[a] = malloc(altura*sizeof(int*));
		for(int b = 0; b+y0 < altura; b++){
			histograma[a][b] = imagem[a][b];
		}
	}
	int count1 = 1;
	int count2 = 1;
	while(count1 < largura){
		while(count2 < altura){
			if(histograma[count1][count2] <= 128){
				imagem[count1][count2] = 0;
			}
			else{
				imagem[count1][count2] = 255;
			}
			count2++;
		}
		count2 = 1;
		free(histograma[count1]);
		count1++;
	}
	free(histograma);
}
void SegmentacaoCorte(unsigned char **imagem, int largura, int altura){
	int larg = largura/8;
	int alt = altura/8;
	int count = 1, count1 = 1;
	while(count1 <= 8){
		int x0 = 0; 
		int x1 = larg;
		while(count <= 8){
			int y0 = 0;
			int y1 = alt;
			if(x0 != 0 && y0 != 0){
				histograma(imagem, x0, x1, y0, y1);
			}
			y0 += y1;
			y1 += alt;
			count++;
		}
		x0 += x1;
		x1 += larg;
		count1++;
	}
}
#endif