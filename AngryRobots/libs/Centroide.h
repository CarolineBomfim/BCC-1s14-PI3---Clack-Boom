#ifndef _CENTROID_H_
#define _CENTROID_H_

void RGB2HSV(int red, int green, int blue, int *h, int *s, int *v){
	float r = (float)red/255;
	float g = (float)green/255;
	float b = (float)blue/255;
	float cMax, cMin;
	if(r >= b && r >= g){
		if(g > b){
			cMin = b;
		}
		else{
			cMin = g;
		}
		cMax = r;
	}
	else if(b >= g){
		if(g > r){
			cMin = r;
		}

		else{
			cMin = g;
		}

		cMax = b;
	}

	else{
		if(r > b){
			cMin = b;
		}

		else{
			cMin = r;
		}

		cMax = g;
	}

	float variacaoCor = cMax - cMin;

	if(variacaoCor != 0){ 
		if(cMax == r){
				if(g >= b){
					*h = 60 * ((g - b) / variacaoCor);
				}
	
				else{
					*h = 60 * ((g - b) / variacaoCor) + 360;
				}

		}
	
		else if(cMax == g){
			*h = 60 * ((b - r) / variacaoCor) + 120;
		}
	
		else{
			*h = 60 * ((r - g) / variacaoCor) + 240;
		}
	}

	else{
		*h = 0;
	}

	*s = variacaoCor/cMax * 100;	
	*v = cMax * 100;
}

int Centroid(unsigned char ***imagem, int altura, int largura, int *coordenada){
	int px = coordenada[0];
	int py = coordenada[1];
	int markx = 0, marky = 0, cn = 0;
	int h, s, v;
	for(int a = 0; a < altura; a++){
		for(int b = 0; b < largura; b++){
			RGB2HSV(
				imagem[a][b][0],
				imagem[a][b][1],
				imagem[a][b][2],
				&h, &s, &v
			);

			if((h > 226 && h < 250) && s > 85 && v == 100){
				marky += a;
				markx += b;
				cn++;
			}else{
				h = 0;
				s = 0;
				v = 0;				
			}
		}
	}
	if( cn > 0){
		coordenada[0] = markx / cn;
		coordenada[1] = marky / cn;
	}
	if(px == coordenada[0] && py == coordenada[1]){
		return 0;
	}
	return 1;
}
#endif
