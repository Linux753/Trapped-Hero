#ifndef LISTE_OBJET
#define LISTE_OBJET
#include "structure.h"

int chargerTexture(CarteSDL *carteSDL , SDL_Texture *image , Objet *objet);
int calculerProbabilite(Objet *objet);
int creerListe(Carte* carte , CarteSDL* carteSDL);

#endif
