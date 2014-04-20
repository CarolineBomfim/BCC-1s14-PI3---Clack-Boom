#include <stdlib.h>
#include <math.h>
#include "define.h"
#include "camera.h"
#include "ArquivoLog.h"
void OpenCV(){
		//O camera inicializa pode ser modificado, 0 a camera primeria 1 a secundaria e assim por diante.
	camera *cam = camera_inicializa(0);
	if(!cam){
		ArquivoLog("Erro ao iniciar a camera.\n");
	}
	unsigned char ***CAMERA = camera_aloca_matriz(cam);

	camera_libera_matriz(cam, CAMERA);	
	camera_finaliza(cam);
}
