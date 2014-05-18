#ifndef _CONVEXHULL_H_
#define _CONVEXHULL_H_
typedef struct {
	int x, y;
}Ponto;
typedef struct {
	Ponto p1, p2;
}Linha;
typedef struct {
	Linha l1, l2, l3;
}Poligono;

void ColorPoli(unsigned char **imagem, int altura, int largura, Poligono *poli, int n){
	int count = 0;
	for(int a = 0; a < altura; a++){
		for(int b = 0; b < largura; b++){
			if(
					(
						(poli[count].l1.p1.x > a && poli[count].l1.p1.x < a)
						&&
						(poli[count].l1.p2.y > b && poli[count].l1.p2.y < b)
					)
					&&
					(
						(poli[count].l2.p1.x > a && poli[count].l2.p1.x < a)
						&&
						(poli[count].l2.p2.y > b && poli[count].l2.p2.y < b)
					)
					&&
					(
						(poli[count].l3.p1.x > a && poli[count].l3.p1.x < a)
						&&
						(poli[count].l3.p2.y > b && poli[count].l3.p2.y < b)
					)
					&&
					(count <= n)
				)
			{
				fprintf(stderr, "Oie\n");
				imagem[a][b] = 126;
				count++;
			}
		}
	}
}
// Estou usando Triangulos por se adaptar mais facilmente a formas mais complexas, usando o Algoritmo de Van Gogh
void SearchPoli(Linha *l1, int nLines, Poligono *poli){
	int nPoli = 0;
	int n = nLines/3;	
	int a = 0;
	while(a <= n){
		poli[nPoli].l1.p1 = l1[a].p1;
		poli[nPoli].l1.p2 = l1[a].p2;
		poli[nPoli].l2.p1 = l1[a+1].p1;
		poli[nPoli].l2.p2 = l1[a+1].p2;
		poli[nPoli].l3.p1 = l1[a+2].p1;
		poli[nPoli].l3.p2 = l1[a+2].p2;
		nPoli++;
		a += 3;
	}
}
// Fazendo as ligações entre os pontos.
void SearchLine(Ponto *p1, Linha *l1, int np, Poligono *poli){
	int nl = 0;
	int np2 = np/2;
	int a = 0;
	while(a <= np2){
		l1[nl].p1 = p1[np2];
		l1[nl].p2 = p1[np2++];
		nl++;
		a+=2;
	}
	SearchPoli(l1, np2, poli);
}
void ConvexHull(unsigned char **imagem, int altura, int largura){
	Ponto *p1 = malloc((largura*altura)*sizeof(Ponto));
	int np=0;
	for(int a = 0; a < altura; a++){
		for(int b = 0; b < largura; b++){
			if(imagem[a][b] == 255 && a < altura - 10 && b < largura - 10){
				p1[np].x = a;
				p1[np].y = b;
				np++;
				a += 10;
				b += 10;
			}
			// Essa condição irá garantir que a função SearchLine seja executada somente uma vez.
			if(b == largura-2 && a == altura-2){
				Linha *l1 = malloc(((largura*altura)/2)*sizeof(Linha));
				Poligono *poli = malloc(((largura*altura)/4)*sizeof(Poligono));
				SearchLine(p1, l1, np, poli);
				ColorPoli(imagem, altura, largura, poli, np/3);
				free(l1);
				free(poli);
			}
		}
	}
	free(p1);
}
#endif