#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include "../../include/structure.h"
#include "../../include/Generateur_chemin.h"
#include "../../include/listeObjet.h"


int GenererObjetCoffre(CarteSDL *carteSDL){
    int nbAlea , i=0;
    nbAlea=rand_a_b(1 , carteSDL->numMax);
    printf("Nb alea :%d" , carteSDL->numMax);
    while(!((carteSDL->listeObjet[i].numMin<=nbAlea&&carteSDL->listeObjet[i].numMax>=nbAlea))){
        i++;
    }
    printf("Num choisi : %d\n" , i);
    return i;
}
void generateScale(Carte *carte){
    int positionPerso=0;
    carte->terrain[carte->position[carte->compteur]].objet=malloc(sizeof(Objet));
    carte->terrain[carte->position[carte->compteur]].objet=0;
    carte->compteur--;
    positionPerso=carte->position[carte->compteur];
    carte->terrain[positionPerso].objet=1;
    carte->posPerso=positionPerso;
    carte->compteur--;
}
void generateTreasor(CarteSDL *carteSDL , Carte* carte){
    int i=0;
    for(i=0;i<carte->largeur/7;i++){
        carte->terrain[carte->position[carte->compteur]].tresor=GenererObjetCoffre(carteSDL );
        carte->compteur--;
    }
}
void generateObject(Carte *carte , CarteSDL *carteSDL){
    int i=0;
    Objet *nouveau;
    generateScale(carte);
    for(i=0; i<carteSDL->nbObjet; i++){
        nouveau=&(carteSDL->listeObjet[i]);
        printf("Et ici et %d\n", carteSDL->numMax );
        if(i>1){

            carteSDL->numMax=calculerProbabilite(nouveau , carte , carteSDL->numMax);
        }
        else{
            nouveau->numMin=0;
            nouveau->numMax=0;
        }
    }
    generateTreasor(carteSDL , carte);
}
