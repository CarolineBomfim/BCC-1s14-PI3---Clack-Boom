// #include <stdio.h>
// #include <allegro5/allegro.h>
// #include <allegro5/allegro_image.h>
// #include <allegro5/allegro_font.h>
// #include <allegro5/allegro_ttf.h>

// int main(){
// 	ALLEGRO_DISPLAY *display = NULL;
// 	ALLEGRO_FONT *fonte1 = NULL;
// 	ALLEGRO_BITMAP *background = NULL;


// 	al_init();
// 	al_init_image_addon();
// 	al_init_font_addon();
// 	al_init_ttf_addon();

// 	display = al_create_display( 800, 600);
// 	fonte1 = al_load_font("fontes/comic.ttf", 50, 0);
// 	background = al_create_bitmap(800, 600);

// 	int count = 0;

// 	for(count = 0; count < 30; count++) {
// 		al_set_target_bitmap(background);
// 		al_draw_bitmap(al_get_backbuffer(display), 0, 0, 0);
// 		al_set_target_bitmap(al_get_backbuffer(display));
// 		al_draw_tinted_bitmap(background, al_map_rgb(0,0,0), 0, 0, 0);
// 		al_flip_display();
// 		al_draw_textf(fonte1, al_map_rgb(255, 255, 255), 800/2, 600/2, ALLEGRO_ALIGN_CENTER, "Timer: %d", count);
// 		al_flip_display();

// 	}

// 	al_destroy_display(display);
// 	al_destroy_font(fonte1);

// 	return 0;
// }