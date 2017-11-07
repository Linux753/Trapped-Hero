#ifndef MANAGE_SDL_H_INCLUDED
#define MANAGE_SDL_H_INCLUDED
#include "structure.h"

int InitialiserSDL(CarteSDL *carteSDL);
CarteSDL *initialiserCarteSDL();
void quitterSDL(CarteSDL *carteSDL);
int loadIMG(CarteSDL *carteSDL , char *file , SDL_Texture** texture );

#endif // MANAGE_SDL_H_INCLUDED
