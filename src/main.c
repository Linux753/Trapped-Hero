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
#include "../include/enregistrer_carte.h"
int main()
{
    CarteSDL *carteSDL=NULL;
    Carte *carte=NULL;
    int dimension =0 , recommencer=0 , out=0 , choice=0;
    srand(time(NULL));
    dimension=rand_a_b(100 , 120);
    carteSDL=initialiserCarteSDL();
    if(carteSDL==NULL){
        fprintf(stderr , "\nErreur\n");
        return -1;
    }
    out=menu(carteSDL , &choice);
    if(out==QUIT){
        quitterJeu(carte , carteSDL);
    }
    else if(out!=-1){
        if(out==PLAY){
            carte =generateurCarteAlea(100 , 100 );
            sprintf(carte->path , "carte/carte%d/carte1.txt" , choice);
            carte->numGame=choice;
        }
        else if(out==LOAD){
            carte=lireCarte(choice);
        }
        moveCharacter(carte , carteSDL );
        enregistrerCarte(carte);
        quitterJeu(carte , carteSDL);
    }
    else{
        printf("\nErreur\n");
        return -1;
    }
    return 0;
}
