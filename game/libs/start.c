#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_primitives.h>
#include "ArquivoLog.h"

void StartGame(){

	if(!al_init()){
		erro("Falha ao iniciar o Allegro.\n");
	}

	if(!al_init_image_addon()){
		erro("Falha ao iniciar a biblioteca de imagens do Allegro.\n");
	}

	if(!al_init_primitives_addon()){
		erro("Falha ao carregar primitive_addons.\n");
	}
	al_init_font_addon();
	if(!al_init_ttf_addon()){
		erro("Falha ao carregar ttf_addons.\n");
	}
	if(!al_install_audio()){
		erro("Falha ao carregar audio.");
	}
	if (!al_reserve_samples(1)){
		erro("Falha ao reservar audio simples");
	}

}

void EndGame(){
	al_shutdown_font_addon();
	al_shutdown_primitives_addon();
	al_shutdown_image_addon();
	al_uninstall_audio();
	al_uninstall_system();
}
