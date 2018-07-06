#ifndef MOVE_CHARACTER_H_INCLUDED
#define MOVE_CHARACTER_H_INCLUDED
#include "structure.h"

int moveCharacter(Carte *carte,CarteSDL* carteSDL );
Carte* floorDown(Carte *carte , CarteSDL* carteSDL);
Carte* floorUp(Carte* carte , CarteSDL *carteSDL);
Carte* loadFloor(Carte* carte , CarteSDL* carteSDL, int change );
int eventPerso(CarteSDL* carteSDL , Carte *carte , int event);
#endif // MOVE_CHARACTER_H_INCLUDED
