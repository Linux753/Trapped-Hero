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
    Carte *carte=NULL;
    int dimension =0 , recommencer=0 , out=0;
    srand(time(NULL));
    dimension=rand_a_b(100 , 120);
    carteSDL=initialiserCarteSDL();
    if(carteSDL==NULL){
        fprintf(stderr , "\nErreur\n");
        return -1;
    }
    out=menu(carteSDL);
    if(out==QUIT){
        quitterJeu(carte , carteSDL);
    }
    else if(out==0){
        carte =generateurCarteAlea(100 , 100 );
        moveCharacter(carte , carteSDL );
        quitterJeu(carte , carteSDL);
    }
    else{
        printf("\nErreur\n");
        return -1;
    }
    return 0;
}
