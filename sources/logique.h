int supressionBassin(int *nbBassin, int *productionBiomasse, int *argent);
int ajoutBassin(int *nbBassin, int *productionBiomasse, int *argent);
int chNiveau (int *pointeurNiveau [NB_BLOCS_LARGEUR] [NB_BLOCS_HAUTEUR] [NB_PARAMETRE], int newNiveau, int y, int x, int saisons);
int calculsProduction(int *pointeurNiveau [NB_BLOCS_LARGEUR] [NB_BLOCS_HAUTEUR] [NB_PARAMETRE], int *nbBassin, int *nbBassinBas, int *nbBassinMoyen, int *nbBassinHaut, int *productionBio);
int nouvelAnnee(int *argent, int nbBassin, int productionAnuel);
int recolte(int *pointeurNiveau [NB_BLOCS_LARGEUR] [NB_BLOCS_HAUTEUR] [NB_PARAMETRE], SDL_Rect *positionMario, int producTotal, int *mod);
int mouvementDeMario(int *tableau[NB_BLOCS_HAUTEUR][NB_BLOCS_LARGEUR], SDL_Rect *positionMario, int mouvement, int *etatMario);