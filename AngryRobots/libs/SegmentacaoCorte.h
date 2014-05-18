#ifndef _SEG_CUT_H_
#define _SEG_CUT_H_
void histograma(unsigned char **imagem, int largura, int altura){
	int **histograma = malloc(largura*sizeof(int **));
	for(int a = 0; a < largura; a++){
		histograma[a] = malloc(altura*sizeof(int*));
		for(int b = 0; b < altura; b++){
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
	int count = 1;
	while(count <= 8){
		int x = larg * count;
		int y = alt * count;
		if(count > 1 && count < (larg*8) && count < (alt * 8)){
			histograma(imagem, x, y);
		}
		count++;
	}

}
#endif