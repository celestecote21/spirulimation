/*
Auteur : Cote celeste
coder dans le cadre des TPE de 1er S de l'année 2018 / 2019
jeu nommer spirumimation, il consiste a simulé un culture de spiruline on l'on doit s'occuper 
des bassins, faire secher la spiruline et la vendre.
les donnée importante
810g/m²/ans


*/

#include <stdio.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "define.h"
#include "jeu.h"
#include <Windows.h>

void cleanup()
{
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* argv[])
{

    FreeConsole();
    SDL_Surface* screen = NULL; // Ecran principal
    
    char mustContinue = 1; // Indicateur boolean pour la boucle principale

    int imgFlags = IMG_INIT_JPG|IMG_INIT_PNG|IMG_INIT_TIF; // Flags pour charger le support du JPG, PNG et TIF
   
    SDL_Surface* menu = NULL;
    SDL_Surface* ligne[5];
    SDL_Rect blitDestination;
    TTF_Font* font = NULL;
    const char* fontPath = "./data/font.ttf";
    SDL_Color fontColor = {99, 140, 222};
    SDL_Rect texteDestination;
    int i = 0;






    // Demarre SDL avec tout les tests
    if ( SDL_Init(SDL_INIT_VIDEO) == -1 )
    {
        fprintf(stderr,"Erreur lors de l'initialisation de la SDL\n");
        return -1;
    }
    if ( IMG_Init(imgFlags) != imgFlags )
    {
        fprintf(stderr,"Erreur lors de l'initialisation de la SDL_image : '%s'\n",IMG_GetError());
        cleanup();
        return -1;
    }
    if ( TTF_Init() == -1 )
    {
        fprintf(stderr,"Erreur lors de l'initialisation de la SDL_TTF : '%s'\n",TTF_GetError());
        cleanup();
        return -1;
    }

    // Creer la fenetre
    screen = SDL_SetVideoMode(LARGEUR_SCREEN,HAUTEUR_SCREEN,32,SDL_SWSURFACE | SDL_DOUBLEBUF);
	if ( screen == NULL )
	{
	    fprintf(stderr,"Erreur lors de l'ouverture de la fenetre\n");
	    cleanup();
        return -2;
	}
    

    font = TTF_OpenFont(fontPath, 20);
     
    //creation du menu
    ligne[0] = TTF_RenderText_Solid(font,"Bonjour, et bienvenue dans notre jeu de simulation de culture de spiruline. \n",fontColor);
    ligne[1] = TTF_RenderText_Solid(font,"Le principe est de faire en sorte que votre culture survive le plus longtemps possible\n",fontColor);
    ligne[0] = TTF_RenderText_Solid(font,"Pour cela il vous suffit de d'acheter des bassin, de vendre vos production\n",fontColor);
    ligne[0] = TTF_RenderText_Solid(font,"mais surtout de faire les bon choix",fontColor);

    menu = IMG_Load("data/menu1.png");
    
    //for(i = 0; i<4; i++){
        
    //}

    blitDestination.x = 0;
    blitDestination.y = 0;

   


    // Boucle principale
	while ( mustContinue )
	{
	   SDL_BlitSurface(menu,NULL,screen,&blitDestination);

        SDL_Flip(screen);

	    SDL_Event event;
	    SDL_WaitEvent(&event);

        // Detecte si on clique sur la croix
	    if( event.type == SDL_QUIT )
	    {
            //On quitte le programme
            mustContinue = 0;
		}
		// Detecte si une touche est appuyee
		else if( event.type == SDL_KEYDOWN )
		{
            switch(event.key.keysym.sym){
                case SDLK_ESCAPE:
                    
                    mustContinue = 0;
                break;
                case SDLK_1:
                    mustContinue = chargeLevel(screen);
                break;
                case SDLK_2:
                    mustContinue = editeur(screen);
                break;
            }
		}
	}

    for(i = 0; ligne[i]; i++){
        SDL_FreeSurface(ligne[i]);
    }
    
    cleanup();

    return 0;
}
