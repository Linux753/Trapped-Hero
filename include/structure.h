#ifndef STRUCTURE_H_INCLUDED
#define STRUCTURE_H_INCLUDED
#define VIDE 0
#define CHEMIN 1
#define MUR 2
#define ESCALIER 3
#define SOL_SALLE 4
#define MUR_SALLE 5
#define PORTE 6
#define MUR_CHEMIN 7
#define HAUT 1
#define BAS 2
#define GAUCHE 3
#define DROITE 4
#define HORIZONTALE 5
#define VERTICALE 6
#define NORMAL 1
#define SANS_FUSIONNEMENT 2
#define ESCALIER_HAUT 1
#define ESCALIER_BAS 2
#define COFFRE 3
#define TREASOR_OPEN 4
#include <SDL2/SDL.h>

typedef struct Terrain Terrain;
struct Terrain{
    int type;
    int numeroSalle;
    int orientation;
    int object;
    int numeroTile;
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
};
typedef struct CarteSDL CarteSDL;
struct CarteSDL{
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
};
#endif // STRUCTURE_H_INCLUDED
