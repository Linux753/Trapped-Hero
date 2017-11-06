#ifndef GENERATEUR_CARTE_ALEA_H_INCLUDED
#define GENERATEUR_CARTE_ALEA_H_INCLUDED
#include "structure.h"
#define VIDE 0
#define CHEMIN 1
#define MUR 2
#define ESCALIER 3
#define SOL_SALLE 4
#define MUR_SALLE 5
#define PORTE 6
#define MUR_CHEMIN 7
void initialiserCarte(Carte *carte);
Carte* generateurCarteAlea(int largeur , int hauteur );
void quitterGenerateur(Carte *carte);

#endif // GENERATEUR_CARTE_ALEA_H_INCLUDED
