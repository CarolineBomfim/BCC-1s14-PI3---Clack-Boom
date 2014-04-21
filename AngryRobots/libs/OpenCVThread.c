#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "ArquivoLog.h"
#include "start.h"
#include "camera.h"
#include "define.h"
typedef struct {
	double x, y;
	camera *cam;
} XY;
void *OpenCV(void *xy){
	fprintf(stderr, "Hello World\n");
}