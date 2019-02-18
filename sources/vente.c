#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <time.h>
#include "define.h"
#include "jeu.h"
#include "editeur.h"
#include "logique.h"
#include "vente.h"



int vente(int *argent, int *productionTotal, int *recolteSec, SDL_Surface* screen){

    TTF_Font* font;
    SDL_Color couleur = {0, 0, 0};
    int continuer = 1;
    SDL_Rect position;
    SDL_Rect positionTemp;
    SDL_Event event;
    font = TTF_OpenFont("data/font.ttf", 18);

    SDL_Surface* text = NULL;
    position.x = 0;
    position.y = 0;
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));
    
    //text = TTF_RenderText_Solid(font, "pret pour la vente? Troix choix s'offre a vous. vous pouvez vendre votre production sec (s), liquide (b) ou la donné(d)", couleur);
    text = IMG_Load("data/menu2.png");
    SDL_BlitSurface(text, NULL, screen, &position);
    SDL_Flip(screen);

    while (continuer){

        while(SDL_PollEvent(&event)){

                switch(event.type){
                    case SDL_QUIT:
                        continuer = 0;
                        return 0;
                    break;                                   
                    case SDL_KEYDOWN:
                        switch(event.key.keysym.sym){
                            case SDLK_ESCAPE:
                                continuer = 0;
                            break;
                            case SDLK_b:                                
                                *argent = *argent + *productionTotal*0.008;
                                *productionTotal = 0;
                                continuer = 0;
                            break;
                            case SDLK_s:
                                *argent = *argent + *recolteSec*0.04;
                                *recolteSec = 0;
                                continuer = 0;
                            break;
                            case SDLK_d:
                                *productionTotal = 0;
                                *recolteSec = 0;
                                continuer = 0;
                            break;
                            }
                        break;
                }
        }


    }

}



int sechage(int *pointeurMap [NB_BLOCS_LARGEUR] [NB_BLOCS_HAUTEUR], int *pointeurNiveau [NB_BLOCS_LARGEUR] [NB_BLOCS_HAUTEUR] [NB_PARAMETRE], int *producTotal, int *producSec,int *mod, SDL_Rect *positionMario, SDL_Surface* screen, int *pointeurSaisons, int *pointeurMois, int *pointeurAnnee, clock_t *tempsDebut){
    int i, j;
    int activSec = 0;
    SDL_Rect positionCarre;
    SDL_Event event;
    int continuer = 1;
    positionCarre.x = positionMario->x - 1;
    positionCarre.y = positionMario->y - 1;
    clock_t timeStart = clock()/CLOCKS_PER_SEC; 
    int mois = *pointeurMois;
    int annee = *pointeurAnnee;
    int saisons = *pointeurSaisons;
    int nouvelleAnnee = 0;
    int productionLiquide = *producTotal;
    int perte = 0;
    SDL_Surface* menu = NULL;
    SDL_Rect positionTemp;
    perte = productionLiquide * 0.10;
    
    for(j=0; j < 3; j++){
        for(i=0; i < 3; i++){
            if (pointeurMap[positionCarre.y + i][positionCarre.x + j] == MUR){
               activSec = 1;
            } 
        } 
    }
    if (activSec){
        menu = IMG_Load("data/menu3.png");
        positionTemp.x = 0;
        positionTemp.y = 0;
        SDL_BlitSurface(menu, NULL, screen, &positionTemp);
        SDL_Flip(screen);
        while(continuer){
            while(SDL_PollEvent(&event)){
                switch(event.type){
                    case SDL_QUIT:
                        continuer = 0;
                        return -1;
                    break;                                   
                    case SDL_KEYDOWN:
                        if(event.key.keysym.sym == SDLK_ESCAPE){
                                continuer = 0;
                                return 0;
                        }
                    break;
                }
            }
            
            *mod = chNiveau(pointeurNiveau, 10, 0,0, saisons);
            if((int)clock()/CLOCKS_PER_SEC - TEMPS_SECHAGE >= timeStart){
                *producSec = productionLiquide - perte;
                *producTotal = 0;
                continuer = 0;
                return 0;
            }

            if ((int)clock()/CLOCKS_PER_SEC - DUREE_MOIS * mois == *tempsDebut/CLOCKS_PER_SEC){
                //producTotal = producTotal + (productionBiomasse*annee)/6;
                mois = mois + 1;
                
            }

            
            if (mois < 9 && mois > 4)
                saisons = ETE;             
            else if( mois < 3 && mois > 1)
                saisons = HIVER;            
            else if( mois == 9 || mois == 10)
                saisons = MILIEU_SAISON;             
            else if( mois == 3 || mois == 4)
                saisons = MILIEU_SAISON;             
            else if( mois == 12 || mois == 11)
                saisons = HIVER;
            else if( mois == 13){
                //nouvelAnnee(&argent, nbBassin, productionBiomasse);
                nouvelleAnnee = 1;
                annee ++;
                mois = 1;
                *tempsDebut = clock();
                
            }
            *pointeurMois = mois;
            *pointeurAnnee = annee;
            *pointeurSaisons = saisons;

        }
    } 
     return nouvelleAnnee;   

}


int communication(char *texte, SDL_Surface* screen){
    SDL_Rect positionTexte1;
    SDL_Rect positionTexte2;
    SDL_Surface* surfaceTexte1 = NULL;
    SDL_Surface* surfaceTexte2 = NULL;
    SDL_Event event;
    TTF_Font* font;
    SDL_Color couleur = {0, 0, 0};
    font = TTF_OpenFont("data/font.ttf", 18);
    int continuer = 1;
    int i = 0;
    char texte1[30];
    char texte2[50];
    int size = calculSize(texte);
    if (size >= 30){
        for(i = 0; i < 30; i++){
            texte1[i] = texte[i];
        }
        while (texte[i] != '\0'){
            texte2[i] = texte[i];
            i++;
        }
        surfaceTexte1 = TTF_RenderText_Solid(font, texte1, couleur);
        surfaceTexte2 = TTF_RenderText_Solid(font, texte2, couleur);
    }
    else{
        i = 0;
        while(texte[i] != '\0'){
            texte1[i] = texte[i];
            i++;
        }
        surfaceTexte1 = TTF_RenderText_Solid(font, texte1, couleur);
    }

    //surfaceTexte1 = TTF_RenderText_Solid(font, texte, couleur);
    //surfaceTexte2 = TTF_RenderText_Solid(font, texte2, couleur);
    positionTexte1.x = 5*TAILLE_BLOCK;
    positionTexte1.y = 10*TAILLE_BLOCK;
    positionTexte2.x = 2*TAILLE_BLOCK;
    positionTexte2.y = 13*TAILLE_BLOCK;

    SDL_BlitSurface(surfaceTexte1, NULL, screen, &positionTexte1);
    SDL_BlitSurface(surfaceTexte2, NULL, screen, &positionTexte2);

    SDL_Flip(screen);
    while (continuer){
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    continuer = 0;
                    return -1;
                break;                                   
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym){
                        case SDLK_ESCAPE:
                            continuer = 0;
                            return 0;
                        break;
                    }
                    
                break;
            }
        }
    }

}



int calculSize(char *texte){
    int i = 0;
    while(texte[i]){
        i++;
    }
    return i;
}