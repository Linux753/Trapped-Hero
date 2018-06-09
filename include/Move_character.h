#ifndef MOVE_CHARACTER_H_INCLUDED
#define MOVE_CHARACTER_H_INCLUDED
#include "structure.h"

int moveCharacter(Carte *carte,CarteSDL* carteSDL );
Carte* floorDown(Carte *carte , CarteSDL* carteSDL);
Carte* floorUp(Carte *carte);
Carte* loadFloor(Carte* carte , int change );

#endif // MOVE_CHARACTER_H_INCLUDED
