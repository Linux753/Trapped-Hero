#ifndef GENERATEUR_CARTE_ALEA_H_INCLUDED
#define GENERATEUR_CARTE_ALEA_H_INCLUDED
#include "structure.h"
void initialiserCarte(Carte *carte);
Carte* generateurCarteAlea(int largeur , int hauteur );
void quitterGenerateur(Carte *carte);
void quitterJeu(Carte *carte , CarteSDL *carteSDL);

#endif // GENERATEUR_CARTE_ALEA_H_INCLUDED
