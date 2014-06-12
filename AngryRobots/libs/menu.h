//Começa a inicializar o MENU
#ifndef _MENU_H_
#define _MENU_H_

int Menu(camera *cam, ALLEGRO_DISPLAY *display, int tentativas){
	if(!cam){
		erro("Não carregou a camera");
	}
	if(!display){
		erro("Não carregou a tela");
	}
	ArquivoLog("Menu");

	int decisao = 0;
	int LARGURA = cam->largura;
	int ALTURA = cam->altura;

	ALLEGRO_TIMER *temporizador = al_create_timer(1.0/FPS);
	if(!temporizador)
		erro("Falha ao criar temporizador.");

	ALLEGRO_EVENT_QUEUE *EventoQueue = al_create_event_queue();
	if(!EventoQueue)
		erro("Falha ao criar evento QUEUE");

	al_register_event_source(EventoQueue, al_get_timer_event_source(temporizador));
	al_register_event_source(EventoQueue, al_get_display_event_source(display));
	ArquivoLog("Registro de eventos!");
	ALLEGRO_FONT *Comics = al_load_font("../res/fonts/comic.ttf", 35, 0);
	ALLEGRO_BITMAP *background = al_load_bitmap("../res/img/background.jpg");

	ALLEGRO_BITMAP *target = al_load_bitmap("../res/img/target.png");
	ALLEGRO_BITMAP *target1 = al_load_bitmap("../res/img/target1.png");

	if(!background ||/* !bomb || !bexiga || !robot ||*/ !target || !target1){
		erro("Falha ao carregar bitmap.");
	}
	ArquivoLog("Sucesso ao carregar e criar fonte, imagens e eventos.");

	al_register_event_source(EventoQueue, al_get_timer_event_source(temporizador));
	al_register_event_source(EventoQueue, al_get_display_event_source(display));

	ArquivoLog("Registro de eventos!");

	al_start_timer(temporizador);	

	int *coordenadas = malloc(2*sizeof(int));
	ALLEGRO_COLOR green = al_map_rgb(0,255,0);
	ALLEGRO_COLOR red = al_map_rgb(255,0,0);

	// ------------------------------------------------------------------------------------------//
	int finalizar = 0;
	while(1){
		ALLEGRO_EVENT evento;
		al_wait_for_event(EventoQueue, &evento);
		switch(evento.type){
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				finalizar = 1;
				ArquivoLog("Finalizado pelo usuario!");
			break;
			default:
			break;
		}
		if(finalizar == 1){
			return 1;
		}
		al_draw_bitmap(background, 0, 0, 0);
		if(tentativas > 1)
			al_draw_text(Comics, al_map_rgb(0,0,255), LARGURA/2, 100, 0, "Deseja tentar novamente?");
		else if(tentativas == (-1)){
			al_draw_text(Comics, green, LARGURA/2, 100, 0, "Parabens! Deseja tentar novamente? ");
		}
		camera_atualiza(cam);
		int MovDetected = Centroid(cam, coordenadas);
		al_draw_bitmap(target, coordenadas[0] - 30,coordenadas[1] - 30, 0);
		int targetx = coordenadas[0];
		

		al_draw_text(Comics,green, (LARGURA/2) - 300, ALTURA/2 + 30, 0, "Iniciar");
		al_draw_text(Comics,red, (LARGURA/2) + 200, ALTURA/2 - 30, 0, "Sair");

		if(targetx < (LARGURA/2) + 100){
			al_draw_bitmap(target1, coordenadas[0] - 30,coordenadas[1] - 30, 0);
			decisao = 0;
			if(MovDetected == 1){
				break;
			}
		}
		else if(targetx < (LARGURA/2) - 100){
			al_draw_bitmap(target1, coordenadas[0] - 30,coordenadas[1] - 30, 0);
			decisao = 1;
			if(MovDetected == 1){
				break;
			}
		}
		al_flip_display();
	}
	free(coordenadas);
	al_unregister_event_source(EventoQueue, al_get_timer_event_source(temporizador));
	al_unregister_event_source(EventoQueue, al_get_display_event_source(display));
	al_stop_timer(temporizador);
	al_destroy_bitmap(background);
	al_destroy_bitmap(target);
	al_destroy_bitmap(target1);
	al_destroy_timer(temporizador);
	al_destroy_event_queue(EventoQueue);
	
	return decisao;
}
/**
* @param continua = 0 significa que o usuário quer continuar a jogar.
* Caso continua = 1 o usuário irá encerrar o jogo; 
*/
void Congratulation(camera *cam, ALLEGRO_DISPLAY *display){
	ArquivoLog("Sucesso!");
	Menu(cam, display, -1);
}
#endif
