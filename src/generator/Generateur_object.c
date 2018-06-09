#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include "../../include/structure.h"
#include "../../include/Generateur_chemin.h"
#include "../../include/listeObjet.h"


int GenererObjetCoffre(Carte *carte){
    int nbAlea , i=0;
    nbAlea=rand_a_b(1 , carte->numMax);
    printf("Nb alea :%d" , nbAlea);
    while(!((carte->listeObjet[i].numMin<=nbAlea&&carte->listeObjet[i].numMax>=nbAlea))){
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
void generateTreasor(Carte *carte){
    int i=0;

    for(i=0;i<carte->largeur/7;i++){
        carte->terrain[carte->position[carte->compteur]].tresor=GenererObjetCoffre(carte );
        carte->compteur--;
    }
    printf("ICI %d\n" , carte->numMax);
}
void generateObject(Carte *carte , CarteSDL *carteSDL){
    creerListe(carte  , carteSDL);
    generateScale(carte);
    generateTreasor(carte);
}
