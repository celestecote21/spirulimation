
#define TAILLE_BLOCK         32 // Taille d'un bloc (carré) en pixels
#define NB_BLOCS_LARGEUR    20
#define NB_BLOCS_HAUTEUR    20
#define LARGEUR_SCREEN    TAILLE_BLOCK * NB_BLOCS_LARGEUR
#define HAUTEUR_SCREEN    TAILLE_BLOCK * NB_BLOCS_HAUTEUR


#define MARIO_DOWN 1
#define MARIO_UP 2
#define MARIO_LEFT 3
#define MARIO_RIGHT 4

#define BASSIN 1
#define CAISSE_OK 2
#define MARIO 3
#define MUR 4
#define OBJECTIF 5
#define VIDE 0

#define DUREE_MOIS 10 //en seconde

#define BASSE 1
#define MOYENNE 2
#define HAUTE 3
#define MORTE 4

#define NB_PARAMETRE 4

#define TEMPS_CH_LEVEL 15 /// en seconde
#define TEMPS_PRODUCTION 1 //// car le truc se fait trois fois plus
#define TEMPS_SECHAGE 35 /// en seconde

#define ETE 3
#define MILIEU_SAISON 2
#define HIVER 1

#define PRODUCTION_ETE 5 ///600 diviser par 8 diviser par 5
#define PRODUCTION_MILIEU_SAISON 3  //120 diviser par 4 diviser par 5

#define FILE_PATH "level.lvl"
#define USER_PATH "donne.dn"