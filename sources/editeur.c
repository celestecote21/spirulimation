#include <stdio.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "define.h"
#include "jeu.h"
#include "editeur.h"



int editeur(SDL_Surface *screen){
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));
    int continuer = 1;
    
    
 
    int x,y;
    int map [NB_BLOCS_LARGEUR] [NB_BLOCS_HAUTEUR] = {0};
    int objetActuel;
    
    // lecture du fichier level
    lectureFichier(map);

    
   

  
    SDL_Rect positioTemp;
  
    SDL_Surface* sol = NULL;
    SDL_Surface* bassin = NULL;
    SDL_Surface* mario = NULL;
    SDL_Surface* caisse_OK = NULL;
    SDL_Surface* objectif = NULL;
    sol = IMG_Load("data/sol.png");
    bassin = IMG_Load("data/bassin1.png");
    caisse_OK = IMG_Load("data/caisse_ok.jpg");
    mario = IMG_Load("data/mario_bas.gif");
    objectif = IMG_Load("data/objectif.png");
    

   //boucle principal:
   //                   affichage de l'ecran
   //                   detection des cliques 
   //                   detection des keystrokes
   //                   reaction par rapport a ca
    
   

    // pas sa place ici. mouvement mario a finir
    while(continuer){
        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));
       
        //boucle affichage de l'ecran
        for(y=0; y < NB_BLOCS_LARGEUR; y++){
            for(x=0; x < NB_BLOCS_HAUTEUR; x++){
                positioTemp.x= x * TAILLE_BLOCK;
                positioTemp.y= y * TAILLE_BLOCK;
                switch(map[y][x]){ // on teste tout les lignes et colone du tableau et on Blit suivant ce que c'est
                    case MUR:
                        SDL_BlitSurface(bassin,NULL,screen,&positioTemp);
                    break;
                    case VIDE:
                        SDL_BlitSurface(sol,NULL,screen,&positioTemp);
                    break;
                    case BASSIN:
                        SDL_BlitSurface(bassin,NULL,screen,&positioTemp);
                    break;
                    
                    case MARIO:
                        SDL_BlitSurface(mario,NULL,screen,&positioTemp);
                    break;
                    case OBJECTIF:
                        SDL_BlitSurface(objectif,NULL,screen,&positioTemp);
                    break;
                }
        
            }
        }

        SDL_Flip(screen);

        SDL_Event event;
        
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    continuer = 0;
                break;
                case SDL_MOUSEBUTTONDOWN:
                    if(event.button.button == 1){                   
                    map[event.button.y / TAILLE_BLOCK ][event.button.x / TAILLE_BLOCK ] = objetActuel;
                    }
                    else{
                        map[event.button.y / TAILLE_BLOCK ][event.button.x / TAILLE_BLOCK ] = VIDE;
                    }

                break;
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym){
                        case SDLK_u:
                            objetActuel = MUR;
                        break;
                        case SDLK_o:
                            objetActuel = OBJECTIF;
                        break;
                        case SDLK_c:
                            objetActuel = BASSIN;
                        break;
                        case SDLK_s:
                            sauvegarde(map);
                        break;
                        case SDLK_a:
                            objetActuel = MARIO;
                        break;
                        case SDLK_ESCAPE:
                            return 1;
                        break;
                    }
            }
        }
               


    }



    SDL_FreeSurface(sol);
    SDL_FreeSurface(bassin);
    SDL_FreeSurface(caisse_OK);
    SDL_FreeSurface(objectif);
    SDL_FreeSurface(mario);
    

    return 0;



}



void lectureFichier(int *map[NB_BLOCS_HAUTEUR][NB_BLOCS_LARGEUR]){
    FILE* file;
    int x,y;

    file = fopen(FILE_PATH, "r");

    for(y=0; y < NB_BLOCS_LARGEUR; y++){
        for(x=0; x < NB_BLOCS_HAUTEUR; x++){
           map[y][x] = fgetc(file);
           fprintf(stderr,"%d \n", map[y][x]);
    
        }
    }

    fclose(file);
    
}

void sauvegarde (int *map[NB_BLOCS_HAUTEUR][NB_BLOCS_LARGEUR]){
    FILE* file;
    int x,y;

    file = fopen(FILE_PATH, "w");

    for(y=0; y < NB_BLOCS_LARGEUR; y++){
        for(x=0; x < NB_BLOCS_HAUTEUR; x++){
           //fprintf(file, " %d ", map[y][x]);
           fputc(map[y][x], file);
    
        }
    }

    fclose(file);


}