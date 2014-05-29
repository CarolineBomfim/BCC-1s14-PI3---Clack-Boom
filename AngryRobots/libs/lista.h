#ifndef _LISTA_H_
#define _LISTA_H_

struct _elemento;
typedef struct _elemento elemento;
struct _elemento{
	char id;
	int x, y;
	elemento *anterior;
	elemento *proximo;
};


elemento AlocaPonto(int x, int y, elemento anterior){
	elemento p;
	p.id = (++anterior.id);
	p.anterior.id = anterior.id;
	anterior.proximo.id = p.id;
	p.proximo = NULL;
	p.anterior = (anterior.id);
	p.x = x;
	p.y = y;
}
elemento *RegistroVertices(unsigned char **imagem, int altura, int largura){
	int x = largura/8;
	int y = altura/8;
	int x0 = x*3;
	int x1 = largura - (x*3);
	int y0 = y*3;
	int y1 = altura - (y*3);
	int count = 1;
	elemento *Ponto = malloc(8*sizeof(elemento));
	Ponto[0].id = 'A';
	Ponto[0].x = x;
	Ponto[0].y = y;
	Ponto[0].anterior = NULL;
	Ponto[0].proximo = NULL;
	for(int a = x0; a <= x1; a++){
		for(int b = y0; b <= y1; b++){
			if(imagem[a-1][b-1] == 0 && imagem[a][b] == 255){
				AlocaPonto(a, b, Ponto[count]);
				count++;
				a += x;
				b += y;
			}
		}
	}
	return Ponto;
}
bool VerificaPonto(elemento *Ponto, unsigned char **imagem, int altura, int largura){
	elemento *P2 = RegistroVertices(imagem, altura, largura);
	int count = 0;
	for(int a = 0; a < altura; a++){
		for(int b = 0; b < largura; b++){
			if(P2[count].x < Ponto[count].x && P2[count].x > Ponto[count].x){
				if(P2[count].y < Ponto[count].y && P2[count].y > Ponto[count].y){
					return true;
				}
			}
			else if(P2[count].y < Ponto[count].y && P2[count].y > Ponto[count].y){
				if(P2[count].x < Ponto[count].x && P2[count].x > Ponto[count].x){
					return true;
				}
			}
		}
	}
	return false;
}
#endif