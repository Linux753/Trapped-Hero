#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include "structure.h"

int menu(CarteSDL *carteSDL , int *choice);
void demarrage(CarteSDL* sdlVar);
int ecrireTextSDL(CarteSDL* carteSDL , char* file,char* text ,int size ,  SDL_Texture** texture , SDL_Color *colorFg , SDL_Color *colorBg);
void quitterDessinerMenu(SDL_Texture *texture1);
void quitterMenu(SDL_Texture *texture1 , SDL_Texture *texture2 , Button *button1 , Button *button2);
int redessinerMenu(CarteSDL *carteSDL ,
                    SDL_Texture *menu , SDL_Texture *title ,
                    SDL_Rect *rectMenu , SDL_Rect *rectTitle ,
                    Button *play , Button *quit , Button *load);
int dessinerMenu(CarteSDL* carteSDL , SDL_Texture **menu , SDL_Rect *rectMenu ,
                Button *play , Button *quit , Button *load);
#endif // MENU_H_INCLUDED
