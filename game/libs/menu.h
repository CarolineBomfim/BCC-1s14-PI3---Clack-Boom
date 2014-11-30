//Começa a inicializar o MENU
#ifndef _MENU_H_
#define _MENU_H_

int Menu(camera *cam, ALLEGRO_DISPLAY *display, int tentativas);
/**
* @param continua = 0 significa que o usuário quer continuar a jogar.
* Caso continua = 1 o usuário irá encerrar o jogo; 
*/
void Congratulation(camera *cam, ALLEGRO_DISPLAY *display);

#endif
