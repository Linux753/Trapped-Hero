#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include "structure.h"

int menu(CarteSDL *carteSDL);
void demarrage(CarteSDL* sdlVar);
int ecrireTextSDL(CarteSDL* carteSDL , char* file,char* text ,int size ,  SDL_Texture** texture , SDL_Color *colorFg , SDL_Color *colorBg);
void quitterDessinerMenu(SDL_Texture *texture1);
void quitterMenu(SDL_Texture *texture1 , SDL_Texture *texture2 , SDL_Texture *texture3 , SDL_Texture *texture4);
int redessinerMenu(CarteSDL *carteSDL ,
                    SDL_Texture *menu , SDL_Texture *title ,
                    SDL_Rect *rectMenu , SDL_Rect *rectTitle ,
                    SDL_Rect *rectQuitter , SDL_Rect *rectJouer ,
                    SDL_Texture *quitter , SDL_Texture *jouer );
int dessinerMenu(CarteSDL* carteSDL , SDL_Texture **menu , SDL_Rect *rectMenu ,
                SDL_Rect *rectQuitter , SDL_Rect *rectJouer ,
                SDL_Texture **quitter , SDL_Texture **jouer);
#endif // MENU_H_INCLUDED
