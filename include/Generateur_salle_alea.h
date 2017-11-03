#ifndef GENERATEUR_SALLE_ALEA_H_INCLUDED
#define GENERATEUR_SALLE_ALEA_H_INCLUDED
#include "structure.h"

void genererSalleAlea(Carte *carte);
int *calculOccupe(int hauteur , int largeur , int position , Carte *carte, Salle *salle);
Salle creerSalle(int position , int largeur , int hauteur , int numeroSalle ,  Carte *carte );
void detruireOccupeMur(Salle *salle);
void collision(Salle *salle , Carte *carte);
void fermerSalle(Carte *carte);

#endif // GENERATEUR_SALLE_ALEA_H_INCLUDED
