#ifndef UTILITAIRE_H_INCLUDED
#define UTILITAIRE_H_INCLUDED
#define HAUT 1
#define BAS 2
#define GAUCHE 3
#define DROITE 4
#define HORIZONTALE 5
#define VERTICALE 6
#define NORMAL 1
#define SANS_FUSIONNEMENT 2
#include "structure.h"

int rand_a_b(int minimum , int maximum);
int dessinerChemin(Carte *carte , int position , int nbCase,  int direction , int *collision , int numero);
void dessinerPorte(Carte* carte);
void pointAleatoire(Carte *carte);
int pointAleatoireEntreBorne(Carte *carte , int debut , int fin );
void murChemin(Carte *carte , int position , int orientation);
int aller(Carte *carte , int position , int destination , int *numero);
int contourner(Carte *carte , int position , int directionDest , int destination , int numeroContourner );
void fermerChemin(Carte *carte , int position , int direction);
int eloignerPorte(Carte *carte ,int *position , int *direction);
void murCheminSalle(Carte *carte , int position , int orientation);
void fermerCheminSalle(Carte *carte , int position , int direction);
#endif // UTILITAIRE_H_INCLUDED
