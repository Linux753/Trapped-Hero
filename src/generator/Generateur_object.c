#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include "../../include/structure.h"

void generateScale(Carte *carte){
    int positionPerso=0;
    carte->terrain[carte->position[carte->compteur]].object=ESCALIER_BAS;
    carte->compteur--;
    positionPerso=carte->position[carte->compteur];
    carte->terrain[positionPerso].object=ESCALIER_HAUT;
    carte->posPerso=positionPerso;
    carte->compteur--;
}
void generateTreasor(Carte *carte){
    int i=0;
    for(i=0;i<carte->largeur/7;i++){
        carte->terrain[carte->position[carte->compteur]].object=COFFRE;
        carte->compteur--;
    }
}
void generateObject(Carte *carte){
    generateScale(carte);
    generateTreasor(carte);
}
