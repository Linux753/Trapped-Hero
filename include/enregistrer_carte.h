#ifndef ENREGISTRER_CARTE_H_INCLUDED
#define ENREGISTRER_CARTE_H_INCLUDED

void quitterEnregistrerCarte(FILE *file);
int lireCarte(Carte *carte ,int choice , CarteSDL* carteSDL);
Carte* loadGame(int choice , CarteSDL* carteSDL);
int majGame(Carte* carte ,CarteSDL* carteSDL , char* pathGame);
void quitterLireCarte(Carte *carte , FILE *file);
int initGame(Carte *carte , CarteSDL* carteSDL);
int enregistrerCarte(Carte *carte);
#endif // ENREGISTRER_CARTE_H_INCLUDED
