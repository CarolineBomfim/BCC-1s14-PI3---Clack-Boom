//Começa a inicializar o MENU

void loadingTela()
{
	Display = al_create_display(Largura_Tela, Altura_Tela);

	if(!Display)
	{
	    fprintf(stderr, "Falha, não conseguiu criar janela.\n");
	}

	fundoDisplay = al_load_bitmap(Imagens/AngryRobots.png);

	if(!fundoDisplay)
	{
		fprintf(stderr, "Falha,não conseguiu criar o fundo.\n");
	}

	al_set_window_title(Display,"AngryRobots");

    inicializarMenu = al_criate_bitmap(250,60)

    if(!inicializarMenu
    {
    	fprintf(stderr, "Falha, não conseguiu conseguiu criar o bitmap.\n");
    	al_destroy_display(Display);
    }
    
    saindoMenu = al_create_bitmap(130,55);

    if(!saindoMenu)
    {
        fprintf(stderr, "Falha, não conseguiu criar o botão de saída.\n");
        al_destroy_display(Display);
    }

    if(!iniciarRobots)
    {  
        AngryMenu = al_load_bitmap(Imagens /* Imagem - Robo Raivoso*/);
        fprintf(stderr,"Falha ao carregar imagem AngryMenu\n");
    }
    else
    {
        RobotsMenu = al_load_bitmap(Imagens /* Imagem - Robo Cyborg*/);
        fprintf(stderr, "Falha ao carregar imagem RobotsMenu\n");
    }

    al_set_target_bitmap(al_get_backbuffer(Display));
    al_draw_bitmap(fundoDisplay,0,0,0);
    al_draw_bitmap(inicializarMenu,300 ,170 , 0);
    al_draw_bitmap(continuarMenu, 290,250,0);
    al_draw_bitmap(saindoMenu,360,320,0);
    // Atualizando tela
    al_flip_display();
   

}