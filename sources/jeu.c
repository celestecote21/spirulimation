#include <stdio.h>
#include <time.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "define.h"
#include "jeu.h"
#include "editeur.h"
#include "logique.h"
#include "vente.h"


/*
editeur : cote celeste
affichage d'un interface faite par une fonction. !!!!! charger a partir d'un fichier a faire
mouvement de Mario sur les surface vide OK


*/


int chargeLevel (SDL_Surface* screen){

    clock_t tempsDebut, tempsPartie;
    tempsDebut = clock();
    tempsPartie = clock() - tempsDebut;

    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));
    int continuer = 1;
    int etatMario = 1;
    int mouvementMario = 5;
    int i, j;
    int x,y;
    int quadriage [NB_BLOCS_LARGEUR] [NB_BLOCS_HAUTEUR] = {0};
    int niveau [NB_BLOCS_LARGEUR] [NB_BLOCS_HAUTEUR] [NB_PARAMETRE]= {0};
    int saisons = 1;
    int rejoue = 1;
    float CO2 = 0;
    int productionBiomasse = 0;
    float flProductionAnuel =0;
    int producTotal = 0;
    float flProducTotal =0;
    int producSec = 0;
    float flProducSec = 0;
    int nbBassin = 0;
    int nbBassinBas = 0;
    int nbBassinMoyen = 0;
    int nbBassinHaut = 0;
    int mod = 0;
    int argent = 150;
    int annee = 0;
    int mois = 0;
    int r = 0;
    
    int temp = 0;
    int quitte = 0;
    int nouvelleAnnee = 0;
    char charProduct[100];
    char charArgent[100];
    char charNbBassin[100];
    char charAnnee[100];
    char charProducTotal[100];
    char charMois[20];
    char charCO2[20];

    TTF_Font* font;
    SDL_Color couleur = {0, 0, 0};
    SDL_Surface* ecriture = NULL;
    SDL_Surface* ecriture2 = NULL;
    SDL_Surface* ecriture3 = NULL;
    SDL_Surface* ecriture4 = NULL;
    SDL_Surface* ecriture5 = NULL;

    SDL_Rect coordFont;
    SDL_Rect positionCarre;

    coordFont.x = 20;
    coordFont.y = 20;
    font = TTF_OpenFont("data/font.ttf", 18);
    

    

    int imgFlags = IMG_INIT_JPG|IMG_INIT_PNG|IMG_INIT_TIF; // Flags pour charger le support du JPG, PNG et TIF
   
 //fichier(quadriage);
  
    SDL_Rect positioTemp;
    SDL_Rect positionMario;
    SDL_Surface* vide = NULL;
    SDL_Surface* mur = NULL;
    SDL_Surface* bassin = NULL;
    SDL_Surface* mario = NULL;
    SDL_Surface* mario_BAS = NULL;
    SDL_Surface* mario_HAUT = NULL;
    SDL_Surface* mario_DROITE = NULL;
    SDL_Surface* mario_GAUCHE = NULL;
    SDL_Event event;

    SDL_Surface* bassin_OK = NULL;
    SDL_Surface* objectif = NULL;
    vide = IMG_Load("data/terre.png");
    mur = IMG_Load("data/batiment.png");
    bassin = IMG_Load("data/bassin1.png");
    bassin_OK = IMG_Load("data/bassin_ok.jpg");
    mario = IMG_Load("data/mario_bas.gif");
    mario_BAS = IMG_Load("data/mario_bas.gif");
    mario_HAUT = IMG_Load("data/mario_haut.gif");
    mario_DROITE = IMG_Load("data/mario_droite.gif");
    mario_GAUCHE = IMG_Load("data/mario_gauche.gif");
    objectif = IMG_Load("data/objectif.png");

    int objetActuel;
   /* if ( TTF_Init() == -1 )
    {
        fprintf(stderr,"Erreur lors de l'initialisation de la SDL_TTF : '%s'\n",TTF_GetError());
        cleanup();
        return -1;
    }*/
    

   tempsDebut = clock();
    
   

    while(rejoue != 0){
         continuer = 1;
        if (rejoue == 2){
            editeur(screen);
             continuer = 0;
            
        }

        rejoue = 0;
        ecritureTableau(quadriage, niveau);  /// charger aussi la map avec les parametre 
       
        while(continuer){
            SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));

            
            if ((int)clock()/CLOCKS_PER_SEC - DUREE_MOIS * mois >= tempsDebut/CLOCKS_PER_SEC){
                //producTotal = producTotal + (productionBiomasse*annee)/6;
                mois ++;
                
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
                nouvelAnnee(&argent, nbBassin, productionBiomasse);
                annee ++;
                mois = 1;
                tempsDebut = clock();
                //communication("c'est la nouvelle annee bravo", screen);
            } 
            
            mod = chNiveau(niveau, 10, 0,0, saisons);

            //boucle affichage de l'ecran
            for(y=0; y < NB_BLOCS_LARGEUR; y++){
                for(x=0; x < NB_BLOCS_HAUTEUR; x++){
                    positioTemp.x= x * TAILLE_BLOCK;
                    positioTemp.y= y * TAILLE_BLOCK;
                    switch(quadriage[y][x]){ // on teste tout les lignes et colone du tableau et on Blit suivant ce que c'est
                        case MUR:
                            SDL_BlitSurface(mur,NULL,screen,&positioTemp);
                        break;
                        case VIDE:
                            SDL_BlitSurface(vide,NULL,screen,&positioTemp);
                            
                        break;
                        case BASSIN:
                            //SDL_BlitSurface(bassin,NULL,screen,&positioTemp);
                            affichageBassin(niveau, y, x, screen);
                        break;
                        case MARIO:
                            SDL_BlitSurface(mario,NULL,screen,&positioTemp);
                            positionMario.x = x;
                            positionMario.y = y;
                        break;
                        case OBJECTIF:
                            SDL_BlitSurface(objectif,NULL,screen,&positioTemp);
                            
                        break;
                    }
            
                }
            }
            mouvementMario = 5;
            positionCarre.x = positionMario.x - 1;
            positionCarre.y = positionMario.y - 1;

            
            while(SDL_PollEvent(&event)){

                switch(event.type){
                    case SDL_QUIT:
                        continuer = 0;
                        return 0;
                    break;
                    case SDL_MOUSEBUTTONDOWN:
                        if(event.button.button == 1){
                            if(objetActuel == BASSIN){
                                if (quadriage[event.button.y / TAILLE_BLOCK ][event.button.x / TAILLE_BLOCK ] == MARIO || quadriage[event.button.y / TAILLE_BLOCK ][event.button.x / TAILLE_BLOCK ] == BASSIN || quadriage[event.button.y / TAILLE_BLOCK ][event.button.x / TAILLE_BLOCK ] == MUR)
                                    break;                                                                    
                                
                                if (ajoutBassin(&nbBassin, &productionBiomasse, &argent) == 1){
                                    quadriage[event.button.y / TAILLE_BLOCK ][event.button.x / TAILLE_BLOCK ] = objetActuel;
                                    mod = chNiveau(niveau, 1, event.button.y / TAILLE_BLOCK, event.button.x / TAILLE_BLOCK, saisons);
                                }
                                    
                                
                                                        
                            }
                            else if (objetActuel == VIDE){ 
                                /*if (quadriage[event.button.y / TAILLE_BLOCK ][event.button.x / TAILLE_BLOCK ] == MARIO ){
                                    {      
                                        objetActuel = VIDE;                          
                                        break;
                                                                        
                                    }*/
                                if (quadriage[event.button.y / TAILLE_BLOCK ][event.button.x / TAILLE_BLOCK ] == BASSIN){
                                    if(supressionBassin(&nbBassin, &productionBiomasse, &argent) == 1)
                                        quadriage[event.button.y / TAILLE_BLOCK ][event.button.x / TAILLE_BLOCK ] = VIDE;
                                        mod = chNiveau(niveau, 0, event.button.y / TAILLE_BLOCK, event.button.x / TAILLE_BLOCK, saisons);
                                }
                            }
                            
                        }
                    break;                
                    case SDL_KEYDOWN:
                        switch(event.key.keysym.sym){
                            case SDLK_ESCAPE:
                                return 1;
                            break;
                            case SDLK_DOWN:
                                mouvementMario = MARIO_DOWN;
                                mario = mario_BAS;
                            break;
                            case SDLK_UP:
                                mouvementMario = MARIO_UP;
                                mario = mario_HAUT;
                            break;
                            case SDLK_LEFT:
                                mouvementMario = MARIO_LEFT;
                                mario = mario_GAUCHE;
                                
                            break;
                            case SDLK_RIGHT:
                                mouvementMario = MARIO_RIGHT;
                                mario = mario_DROITE;
                            break;
                            case SDLK_v:
                                objetActuel = VIDE;
                            break;                            
                            case SDLK_b:
                                objetActuel = BASSIN;
                            break;
                            case SDLK_h:
                                sauvegarde(quadriage);
                            break;
                            case SDLK_r:
                                for(j=0; j < 3; j++){
                                    for(i=0; i < 3; i++){
                                        if(niveau[positionCarre.y + j][positionCarre.x + i][0] == HAUTE || niveau[positionCarre.y + j][positionCarre.x + i][0] == MOYENNE){
                                            r = r + niveau[positionCarre.y + j][positionCarre.x + i][2];
                                            /*CO2 = CO2 + ((float)niveau[positionCarre.y + j][positionCarre.x + i][2])*1,7;*/
                                            niveau[positionCarre.y + j][positionCarre.x + i][2] = 0;
                                        }
                                    }
                                }
                                producTotal = producTotal + r;
                                CO2 = CO2 + r*1.7;
                                r = 0;
                            break;
                            case SDLK_e:
                                vente(&argent, &producTotal, &producSec, screen);
                            break;
                            case SDLK_s:
                                nouvelleAnnee = sechage(quadriage, niveau, &producTotal, &producSec, &mod, &positionMario, screen, &saisons, &mois, &annee, &tempsDebut);
                            break;
                            
                            
                        }
                }
            }
            if (mod){
                calculsProduction(niveau, &nbBassin, &nbBassinBas, &nbBassinMoyen, &nbBassinHaut, &productionBiomasse);
                mod = 0;
            }
            if (nouvelleAnnee == 1){
                nouvelAnnee(&argent, nbBassin, productionBiomasse);
            }

            flProductionAnuel = (float)productionBiomasse/ 1000;
            flProducTotal = (float)producTotal/ 1000;
            flProducSec = (float)producSec/ 1000;
             
            
            sprintf(charProduct,"Production annuelle: %f kg/an", flProductionAnuel);
            sprintf(charProducTotal,"Production totale: %f kg    Production seche: %f kg", flProducTotal, flProducSec);
            sprintf(charAnnee,"Annee: %d ans       Mois: %d            Saisons: %d", annee, mois, saisons);
            sprintf(charNbBassin,"Nombre de bassins: %d ", nbBassin);
            sprintf(charArgent,"Argent: %d euros", argent);
            sprintf(charCO2,"CO2 absorbe: %f kg", CO2/1000);
            coordFont.x = 20;
            coordFont.y = 20;
            ecriture = TTF_RenderText_Solid(font, charProduct, couleur);
            SDL_BlitSurface(ecriture, NULL, screen, &coordFont);
             
            coordFont.y = 40;
            ecriture2 = TTF_RenderText_Solid(font, charAnnee, couleur);
            SDL_BlitSurface(ecriture2, NULL, screen, &coordFont);
            
            coordFont.y = 60;
            ecriture3 = TTF_RenderText_Solid(font, charNbBassin, couleur);
            SDL_BlitSurface(ecriture3, NULL, screen, &coordFont);

            coordFont.y = 80;
            ecriture4 = TTF_RenderText_Solid(font, charProducTotal, couleur);
            SDL_BlitSurface(ecriture4, NULL, screen, &coordFont);

            coordFont.y = 100;
            ecriture5 = TTF_RenderText_Solid(font, charCO2, couleur);
            SDL_BlitSurface(ecriture5, NULL, screen, &coordFont);

            coordFont.y = 120;
            ecriture5 = TTF_RenderText_Solid(font, charArgent, couleur);
            SDL_BlitSurface(ecriture5, NULL, screen, &coordFont);
        
            SDL_Flip(screen);
            SDL_FreeSurface(screen);
            SDL_FreeSurface(ecriture5);
            SDL_FreeSurface(ecriture4);
            SDL_FreeSurface(ecriture3);
            SDL_FreeSurface(ecriture2);
            SDL_FreeSurface(ecriture);
            /*SDL_FreeSurface(bassin);
            SDL_FreeSurface(vide);*/
            mouvementDeMario(quadriage,&positionMario, mouvementMario, &etatMario);

            


        }

        
    }



    SDL_FreeSurface(mur);
    SDL_FreeSurface(ecriture);
    SDL_FreeSurface(ecriture2);
    SDL_FreeSurface(ecriture3);
    SDL_FreeSurface(ecriture4);
    SDL_FreeSurface(ecriture5);
    SDL_FreeSurface(bassin);
    SDL_FreeSurface(bassin_OK);
    SDL_FreeSurface(objectif);
    SDL_FreeSurface(mario);
    
    //SDL_Quit();
    
    return 1;

}



//met le fichier dans une tableau 
int ecritureTableau (int *pointeurTableau[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR], int *pointeurNiveau [NB_BLOCS_LARGEUR] [NB_BLOCS_HAUTEUR] [NB_PARAMETRE]){
    FILE* file;
    int x,y;

    file = fopen(FILE_PATH, "r");

    for(y=0; y < NB_BLOCS_LARGEUR; y++){
        for(x=0; x < NB_BLOCS_HAUTEUR; x++){
           pointeurTableau[y][x] = fgetc(file);
           if (pointeurTableau[y][x] == BASSIN){
                pointeurNiveau[y][x][0] = BASSE;
           }
    
        }
    }

    fclose(file);
    

}

int chDonnee(int argent, int product, int nbBassin){
    FILE* fileDonnee;

    fileDonnee = fopen(USER_PATH, "w");

    fprintf(fileDonnee,"%d", product);

    fclose(fileDonnee);
}


    
    

    

    

