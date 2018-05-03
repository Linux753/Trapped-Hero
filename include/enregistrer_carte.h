#ifndef ENREGISTRER_CARTE_H_INCLUDED
#define ENREGISTRER_CARTE_H_INCLUDED

void quitterEnregistrerCarte(FILE *file);
int enregistrerCarte(Carte *carte);
Carte* loadGame(int choice);
int majGame(Carte* carte , char* pathGame);
int lireCarte(Carte *carte);
#endif // ENREGISTRER_CARTE_H_INCLUDED
