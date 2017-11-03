#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/Generateur_chemin.h"
#include "../include/Generateur_carte_alea.h"
#define LARGEUR 100
#define HAUTEUR 100
#include "../include/Afficher_carte.h"
#include "../include/Move_character.h"
#include "../include/menu.h"
int main()
{
    CarteSDL *carteSDL=NULL;
    Carte carte;
    int dimension =0 , recommencer=0;
    srand(time(NULL));
    dimension=rand_a_b(100 , 120);
    carteSDL=initialiserCarteSDL();
    if(carteSDL==NULL){
        fprintf(stderr , "\nErreur\n");
        return -1;
    }
    carte =generateurCarteAlea(100 , 100 );
    moveCharacter(&carte , carteSDL );
    printf("Dimension carte : \nHauteur = %d\nLargeur = %d\n\nMet un 1 si tu veux générer une autre carte , un 0 pour quitter", carte.hauteur , carte.largeur);
    quitterGenerateur(&carte);
    quitterSDL(carteSDL);
    return 0;
}
