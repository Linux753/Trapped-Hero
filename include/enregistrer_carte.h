#ifndef ENREGISTRER_CARTE_H_INCLUDED
#define ENREGISTRER_CARTE_H_INCLUDED

void quitterEnregistrerCarte(FILE *file);
int lireCarte(Carte *carte ,int choice , CarteSDL* carteSDL);
Carte* loadGame(int choice , CarteSDL* carteSDL);
int majGame(Carte* carte , char* pathGame);
void quitterLireCarte(Carte *carte , FILE *file);
#endif // ENREGISTRER_CARTE_H_INCLUDED
