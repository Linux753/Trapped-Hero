#ifndef MONSTER_H
#define MONSTER_H
#include "structure.h"
    int initialiserPersonnage(CarteSDL* carteSDL);
    int initialiserPersoInventaire(CarteSDL* carteSDL);
    int takeObject(CarteSDL* carteSDL , Carte* carte, int objet , int position);
    void afficherInventaire(CarteSDL *carteSDL);
    void calculerInventaire(CarteSDL *carteSDL , Type type);
    void quitCreateWindowStatsButton(SDL_Texture* texture1 , SDL_Texture *texture2);
    char *createTextWithSize(CarteSDL *carteSDL ,char *text , int tailleMax , int *num , int *wPhrase , int *hPhrase);
#endif
