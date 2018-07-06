#ifndef STRUCTURE_H_INCLUDED
#define STRUCTURE_H_INCLUDED
#define VIDE 0
#define CHEMIN 1
#define ESCALIER 2
#define SOL_SALLE 3
#define PORTE 4
#define MUR 5
#define MUR_CHEMIN 6
#define MUR_SALLE 7
#define HAUT 1
#define BAS 2
#define GAUCHE 3
#define DROITE 4
#define HORIZONTALE 5
#define VERTICALE 6
#define ESCALIER_HAUT 1
#define ESCALIER_BAS 2
#define COFFRE 3
#define TREASOR_OPEN 4
#define QUIT 100
#define PLAY 101
#define LOAD 102
#define VISITED 1
#define HIDDEN 2
#define SHOW 3
#define PATH "carte/carte%d/carte1.txt"
#include <SDL2/SDL.h>

typedef enum Type Type;
enum Type{
    Rien ,Or , Epe , Armure , Arc , Baton , BatonMagique , Parchemin , Potion , Porte , EscalierBas , EscalierHaut , Tresor , Fleche , Massue
};
typedef enum TypeAttaque TypeAttaque;
enum TypeAttaque{
    Nulle , Arcane , Tranchant , Froid , Feu , Perforant , Contendant
};
typedef struct Objet Objet;
struct Objet{
    char nom[50];
    Type type;
    TypeAttaque typeAttaque;
    float poids;
    int resistance;//D'une armure ou d'un bouclier
    int resistanceMagique;
    int attaque;
    int attaqueMax;
    int caracteristiqueCritique;
    int precision;
    int habilete;
    int magie;
    char description[5000];
    int probabilite;
    int rarete;
    int niveau;
    int nbEtage;
    int x;
    int y;
    int numMin;
    int numMax;
    int resistanceOriginale;
    int protection;//D'une armure ou alors le coefficient de protection du bouclier (le plus souvent de 1 à 10%)
    SDL_Texture *texture;
};
typedef struct Personnage Personnage;
struct Personnage{
    //Inventaire
    int *inventaireArme;
    int *inventaireBaton;
    int *inventaireArmure;
    int *inventairePotion;
    int *inventaireParchemin;
    int nbObjets;
    int masseObjet;
    //Caracteristique
    int vie;
    int force;
    int habilete;
    int precision;
    int magie;
    int agilite;
    //Objets
    Objet armure;
    int armureNum;
    Objet arme;
    int attaque;
    int attaqueMax;
    int protection;
    int poidsMax;
    Objet argent;
    //Autre
    SDL_Texture *texture;
};
typedef struct Terrain Terrain;
struct Terrain{
    Type type;
    int tresor;//Corespond a la case de l'objet que le tresor contient -1
    int objet;//Corespond a la case de l'objet -1
    int numeroSalle;
    char numeroTile;
    char voile;
};
typedef struct Salle Salle;
struct Salle{
    int position;
    int hauteur;
    int largeur;
    int *occupeAvecMur;
    int *occupeSansMur;
    int numeroSalle;
};
typedef struct Carte Carte;
struct Carte{
    Terrain *terrain;
    int largeur;
    int hauteur;
    int nbSalle;
    int compteur;
    int *position;
    int *blackListRoom;
    int nbBlackListRoom;
    int posPerso;
    int numGame;
    int floor;
    int nbFloor;
    char path[50];
};
typedef struct CarteSDL CarteSDL;
struct CarteSDL{
    int numMax;
    Objet *listeObjet;
    int nbObjet;
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture **mur;
    SDL_Texture **chemin;
    SDL_Texture *porte;
    SDL_Texture *vide;
    SDL_Texture *escalierHaut;
    SDL_Texture *escalierBas;
    SDL_Texture *treasor;
    SDL_Texture *treasorOpen;
    SDL_Texture *personnage;
    Personnage *perso;
};
typedef struct Button Button;
struct Button{
    SDL_Rect rectText;
    SDL_Rect rectSelect;
    SDL_Texture *text;
    int select;
};


#endif // STRUCTURE_H_INCLUDED
