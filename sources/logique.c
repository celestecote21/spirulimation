#include <stdio.h>
#include <time.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "define.h"
#include "jeu.h"
#include "editeur.h"




int ajoutBassin(int *nbBassin, int *productionBiomasse, int *argent){
    ///demander si il est sur de vouloir en mettre un, le prix que ca coute......
    if (*argent <= 5){
        //pasArgent();
        return 0;
    }
    *argent = *argent - 6;
    *nbBassin = *nbBassin + 1;
    *productionBiomasse = *productionBiomasse + 810;

    return 1;
}

int supressionBassin(int *nbBassin, int *productionBiomasse, int *argent){
    ///demander si il est sur de vouloir en mettre un, le prix que ca coute......
    if (*argent <= 2){
        //pasArgent();
        return 0;
    }

    *argent = *argent - 3;
     *nbBassin = *nbBassin - 1;
    *productionBiomasse = *productionBiomasse - 810;

    return 1;
}


// le dernier parametre du tableau c'est pour mettre : 
//                                                  case 0 : son etat ==> si bas moyen ou haut
//                                                  case 1 : la derniere fois que l'etat a ete changer
//                                                  case 2 : amount de spiruline
//                                                  case 3 : la dernier fois qu'un ajout a ete fait


// revoir le controle avec le temps probleme avec les type de variable
// pas d'affichage differennt suivant les niveau des bassin
// voir pour la supression des bassins 
// modification de la production de biomasse car pour l'instand les nveau ne servent a rien

int chNiveau (int *pointeurNiveau [NB_BLOCS_LARGEUR] [NB_BLOCS_HAUTEUR] [NB_PARAMETRE], int newNiveau, int y, int x, int saisons){
     
    int j, i;
    int mod = 0; /// pour savoir si qqlch a ete modifer pour apres appeler la fontion qui fait les modifications sur les variables 
    
    if (newNiveau == 1){
        pointeurNiveau[y][x][0] = 1;
        pointeurNiveau[y][x][1] = (int) clock()/CLOCKS_PER_SEC;
        pointeurNiveau[y][x][3] = (int) clock()/CLOCKS_PER_SEC;
        mod = 1;
    }
    else if (newNiveau == 0){
        pointeurNiveau[y][x][0] = 0;
        mod = 1;
        
    }
    if (newNiveau == 10){
        for(j=0; j < NB_BLOCS_LARGEUR; j++){
            for(i=0; i < NB_BLOCS_HAUTEUR; i++){
                //if ((int)clock()/CLOCKS_PER_SEC - (long)pointeurNiveau[j][i][1] > TEMPS_CH_LEVEL && pointeurNiveau[j][i][0] != 0){
                    if (pointeurNiveau[j][i][2] > 728){
                        pointeurNiveau[j][i][0] = MORTE;
                        pointeurNiveau[j][i][2] = 0;
                        mod = 1;
                    }
                    else if (pointeurNiveau[j][i][2] > 607){
                        pointeurNiveau[j][i][0] = HAUTE;
                        mod = 1; 
                    }
                    else if (pointeurNiveau[j][i][2] > 121){
                        pointeurNiveau[j][i][0] = MOYENNE;
                        mod = 1;
                    } 
                    else if (pointeurNiveau[j][i][2] < 121 && pointeurNiveau[j][i][0] != MORTE && pointeurNiveau[j][i][0] != 0){
                        pointeurNiveau[j][i][0] = BASSE;
                        mod = 1;
                    } 

                                  
                //}
                if ((int)clock()/CLOCKS_PER_SEC - (long)pointeurNiveau[j][i][3] > TEMPS_PRODUCTION && pointeurNiveau[j][i][0] != 0 &&  pointeurNiveau[j][i][0] != 4){
                    if (saisons == ETE){
                        pointeurNiveau[j][i][2] = pointeurNiveau[j][i][2] + PRODUCTION_ETE;
                        pointeurNiveau[j][i][3] = (int) clock()/CLOCKS_PER_SEC;
                    }
                    else if (saisons == MILIEU_SAISON){
                        pointeurNiveau[j][i][2] = pointeurNiveau[j][i][2] + PRODUCTION_MILIEU_SAISON;
                        pointeurNiveau[j][i][3] = (int) clock()/CLOCKS_PER_SEC;
                    }
                    else if (saisons == HIVER){
                        pointeurNiveau[j][i][3] = (int) clock()/CLOCKS_PER_SEC;
                    }
                    
                                  
                }
            
        
            }
        }
        
    }

    return mod;
    
}



int calculsProduction(int *pointeurNiveau [NB_BLOCS_LARGEUR] [NB_BLOCS_HAUTEUR] [NB_PARAMETRE], int *nbBassin, int *nbBassinBas, int *nbBassinMoyen, int *nbBassinHaut, int *productionBio){
    int j,i;
    *productionBio = 0;
    
    for(j=0; j < NB_BLOCS_LARGEUR; j++){
        for(i=0; i < NB_BLOCS_HAUTEUR; i++){
           if (pointeurNiveau[j][i][0] == BASSE){
                *nbBassinBas = *nbBassinBas + 1;
                *productionBio = *productionBio + 810;
            }
            else if (pointeurNiveau[j][i][0] == MOYENNE){
                *nbBassinMoyen = *nbBassinMoyen + 1;
                *productionBio = *productionBio + 810;
            }
             else if (pointeurNiveau[j][i][0] == HAUTE){
                *nbBassinHaut = *nbBassinHaut + 1;
                *productionBio = *productionBio + 810;
            }
            
           
    
        }
    }

    return 0;
}



int nouvelAnnee(int *argent, int nbBassin, int productionAnuel){
    float cout = 0;
    cout = cout + nbBassin*0.10;//cout petite reparation
    cout = cout + productionAnuel*0.00015;//cout electriciter
    cout = cout + productionAnuel*0.00003;//cout eau

    *argent = *argent - (int) cout;
    if (*argent < 0){
        return -1;
    }

    ///annoncer qu'il y a eu une facture
}



int affichageBassin(int *pointeurNiveau [NB_BLOCS_LARGEUR] [NB_BLOCS_HAUTEUR] [NB_PARAMETRE], int y, int x, SDL_Surface* screen){
    
    SDL_Rect positionTemp;
    positionTemp.x = x * TAILLE_BLOCK;
    positionTemp.y = y * TAILLE_BLOCK;
    SDL_Surface* bassin = NULL;
    bassin = SDL_CreateRGBSurface(SDL_HWSURFACE, 32, 32, 32, 0, 0, 0, 0);
    SDL_FillRect(bassin,NULL, SDL_MapRGB(bassin->format, 35, 104, 18));///Haute concentration
    
    if (pointeurNiveau[y][x][0] == BASSE){
        SDL_FillRect(bassin,NULL, SDL_MapRGB(bassin->format, 36, 255, 41));///Basse concentration
    }
    else if (pointeurNiveau[y][x][0] == MOYENNE){
        SDL_FillRect(bassin,NULL, SDL_MapRGB(bassin->format, 53, 157, 28));///Moyen concentration
    }
    else if (pointeurNiveau[y][x][0] == HAUTE){
        SDL_FillRect(bassin,NULL, SDL_MapRGB(bassin->format, 35, 104, 18));///Haute concentration
    }
    else if (pointeurNiveau[y][x][0] == MORTE){
        SDL_FillRect(bassin,NULL, SDL_MapRGB(bassin->format, 81, 81, 0));///Haute concentration
    }


    SDL_BlitSurface(bassin,NULL,screen, &positionTemp);

    SDL_FreeSurface(bassin);
}

/// probleme au niveau de la recole ca multipli par 4 le recolte total !!!!!!! a reparer!!!!!
int recolte(int *pointeurNiveau [NB_BLOCS_LARGEUR] [NB_BLOCS_HAUTEUR] [NB_PARAMETRE], SDL_Rect *positionMario, int producTotal, int *mod){

    int i, j;
    
    int productionRecolter = producTotal;
    SDL_Rect positionCarre;
    positionCarre.x = positionMario->x - 1;
    positionCarre.y = positionMario->y - 1;

        
    
    //for(j=0; j < 3; j++){
        //for(i=0; i < 3; i++){
            //productionRecolter = *producTotal;
            if (pointeurNiveau[positionCarre.y][positionCarre.x][0] == MOYENNE  || pointeurNiveau[positionCarre.y][positionCarre.x][0] == HAUTE){
                productionRecolter = producTotal +pointeurNiveau[positionCarre.y][positionCarre.x][2];
                pointeurNiveau[positionCarre.y][positionCarre.x][2] = 0;
                //pointeurNiveau[positionCarre.y][positionCarre.x][0] == BASSE;
                //mod = 1;
            }
            
            
           
    
        //}
    //} 
    *mod = 1;
    return productionRecolter;    
}





int mouvementDeMario(int *tableau[NB_BLOCS_HAUTEUR][NB_BLOCS_LARGEUR], SDL_Rect *positionMario, int mouvement, int *etatMario){
    // fprintf(stderr,"%d    %d    %d  \n", tableau[positionMario->x][positionMario->y], positionMario->x, positionMario->y);
    switch(mouvement){
        case MARIO_DOWN:
            if(tableau[positionMario->y + 1][positionMario->x] == 0 && positionMario->y != NB_BLOCS_HAUTEUR){
                // c'est bon il peu aller en bas
                tableau[positionMario->y][positionMario->x] =  VIDE;
                tableau[positionMario->y + 1][positionMario->x] = MARIO;
                return 5;
                
            }      
            else{
                etatMario = MARIO_DOWN;
            }
        break;
        case MARIO_UP:
            if(tableau[positionMario->y - 1][positionMario->x] == VIDE && positionMario->y != 0){
                // c'est bon il peu aller en bas
                tableau[positionMario->y][positionMario->x] =  VIDE;
                tableau[positionMario->y - 1][positionMario->x] = MARIO;
                return 5;
                
            }
            else{
                etatMario = MARIO_UP;
            }
        break;
        case MARIO_LEFT:
            if(tableau[positionMario->y][positionMario->x - 1] == VIDE && positionMario->x != 0){
                // c'est bon il peu aller en bas
                tableau[positionMario->y][positionMario->x] =  VIDE;
                tableau[positionMario->y][positionMario->x - 1] = MARIO;
                return 5;
                
            }
            
            else{
                etatMario = MARIO_LEFT;
            }
        break;
        case MARIO_RIGHT:
            if(tableau[positionMario->y][positionMario->x + 1] == VIDE && positionMario->x != 19){
                // c'est bon il peu aller en bas
                tableau[positionMario->y][positionMario->x] =  VIDE;
                tableau[positionMario->y][positionMario->x + 1] = MARIO;
                return 5;
                
            }
            else{
                etatMario = MARIO_LEFT;
            }
        break;
    }
    return 5;
}




/* ancienne version fonction recolte 
productionRecolter = *producTotal;
           if (/*pointeurNiveau[positionCarre.y + i][positionCarre.x + j][0] == HAUTE ||*//* pointeurNiveau[positionCarre.y + i][positionCarre.x + j][0] == MOYENNE){
                pointeurNiveau[positionCarre.y + i][positionCarre.x + j][0] = BASSE;
                pointeurNiveau[positionCarre.y + i][positionCarre.x + j][1] = (int) clock()/CLOCKS_PER_SEC;
                mod = 1;
                *producTotal = productionRecolter + pointeurNiveau[positionCarre.y + i][positionCarre.x + j][2];
                //producTotal = productionRecolter + 10;
                pointeurNiveau[positionCarre.y + i][positionCarre.x + j][2] = 0;
            }*/
