#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include "structure.h"

int menu(CarteSDL *carteSDL);
void demarrage(CarteSDL* sdlVar);
int ecrireTextSDL(CarteSDL* carteSDL , char* file,char* text ,int size ,  SDL_Texture** texture , SDL_Color *colorFg , SDL_Color *colorBg);
void quitterDessinerMenu(SDL_Texture *texture1);
void quitterMenu(SDL_Texture *texture1 , SDL_Texture *texture2);
#endif // MENU_H_INCLUDED
