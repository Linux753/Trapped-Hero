#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "../include/structure.h"
#include "../include/Afficher_carte.h"

int ecrireTextSDL(CarteSDL* carteSDL , char* file,char* text ,int size ,  SDL_Texture** texture , SDL_Color *colorFg , SDL_Color *colorBg){
    SDL_Surface *surface=NULL;
    TTF_Font*font=NULL;
    int out=0;
    font=TTF_OpenFont(file , size);
    if(font==NULL){
        fprintf(stderr , "Erreur TTF_OpenFont : %s" , TTF_GetError());
        out=-1;
        goto QuitEcrireTextSDL;
    }
    if(colorBg==NULL){
        surface=TTF_RenderUTF8_Blended(font , text  , *colorFg );
        if(surface==NULL){
            fprintf(stderr , "Erreur TTF_RenderUTF8_Blended() : %s" , TTF_GetError());
            out=-1;
            goto QuitEcrireTextSDL;
        }
    }
    else{
        surface=TTF_RenderUTF8_Shaded(font , text , *colorFg , *colorBg);
        if(surface==NULL){
            fprintf(stderr , "Erreur TTF_RenderUTF8_Shaded() : %s" , TTF_GetError());
            out=-1;
            goto QuitEcrireTextSDL;
        }
    }
    *texture=SDL_CreateTextureFromSurface(carteSDL->renderer , surface);
    if(*texture==NULL){
        fprintf(stderr , "Erreur SDL_CreateTextureFromSurface() : %s" , SDL_GetError());
        out=-1;
        goto QuitEcrireTextSDL;
    }
    QuitEcrireTextSDL :
    if(font!=NULL){
        TTF_CloseFont(font);
    }
    if(surface!=NULL){
        SDL_FreeSurface(surface);
    }
    return out;
}
void demarrage(CarteSDL* sdlVar){
    SDL_Texture *imageSDL=NULL , *textSDL=NULL , *specialThank=NULL;
    int h=0 , w=0;
    SDL_Rect rectImage1 , rectTextSDL , rectSpecialThank;
    SDL_Color colorFg={255 , 255 , 255 , 255};
    loadIMG(sdlVar , "image/logoSDL.png" , &imageSDL);
    SDL_QueryTexture(imageSDL , NULL , NULL , &rectImage1.w , &rectImage1.h);
    SDL_GetWindowSize(sdlVar->window , &w , &h);
    //rectImage1.w=rectImage1.w*2;
    //rectImage1.h=rectImage1.h*2;
    rectImage1.x=(w/2)-(rectImage1.w/2);
    rectImage1.y=(h/2)-(rectImage1.h/2);
    ecrireTextSDL(sdlVar , "police/OpenSans-Regular.ttf" , "Created by Linux with :", 80  , &textSDL , &colorFg , NULL );
    SDL_QueryTexture(textSDL , NULL , NULL , &rectTextSDL.w , &rectTextSDL.h);
    rectTextSDL.x=(w/2)-(rectTextSDL.w/2);
    rectTextSDL.y=((rectImage1.y)/2)-rectTextSDL.h;
    ecrireTextSDL(sdlVar , "police/OpenSans-Regular.ttf" , "Special thanks to Mr Dator for the compilation on windows", 40  , &specialThank , &colorFg , NULL );
    SDL_QueryTexture(specialThank , NULL , NULL , &rectSpecialThank.w , &rectSpecialThank.h);
    rectSpecialThank.x=(w/2)-(rectSpecialThank.w/2);
    rectSpecialThank.y=h-(h/10);
    SDL_SetRenderDrawColor(sdlVar->renderer , 38 , 38 , 38 , 0);
    SDL_RenderClear(sdlVar->renderer);
    SDL_RenderCopy(sdlVar->renderer , imageSDL , NULL , &rectImage1);
    SDL_RenderCopy(sdlVar->renderer , textSDL , NULL , &rectTextSDL);
    SDL_RenderCopy(sdlVar->renderer , specialThank , NULL , &rectSpecialThank);
    SDL_RenderPresent(sdlVar->renderer);
    SDL_Delay(2000);
    SDL_DestroyTexture(imageSDL);
    SDL_DestroyTexture(textSDL);
    SDL_DestroyTexture(specialThank);
}
void quitterDessinerMenu(SDL_Texture *texture1 , SDL_Texture *texture2){
    if(texture1!=NULL){
        SDL_DestroyTexture(texture1);
    }
    if(texture2!=NULL){
        SDL_DestroyTexture(texture2);
    }
}
int dessinerMenu(CarteSDL* carteSDL , SDL_Texture **menu , SDL_Rect *rectMenu){
    SDL_Texture *quitter=NULL , *jouer=NULL;
    SDL_Color colorfg={0 , 0 , 0 , 255} , colorbg={0 , 0 , 255 , 255};
    SDL_Rect rectQuitter={0 , 0 , 0 , 0} , rectJouer={0 , 0 , 0 , 0};
    *menu=SDL_CreateTexture(carteSDL->renderer  , SDL_PIXELFORMAT_RGBA8888 , SDL_TEXTUREACCESS_TARGET , rectMenu->w , rectMenu->h);
    if(menu==NULL){
        fprintf(stderr , "Erreur SDL_CreateTexture : %s" , SDL_GetError());
        quitterDessinerMenu(quitter , jouer);
        return -1;
    }
    if(0!=SDL_SetRenderTarget(carteSDL->renderer , *menu)){
        fprintf(stderr , "Erreur SDL_SetRenderTarget : %s" , SDL_GetError());
        quitterDessinerMenu(quitter , jouer);
        return -1;
    }
    SDL_SetRenderDrawColor(carteSDL->renderer , 88 , 41 , 0 , 255);
    SDL_RenderFillRect(carteSDL->renderer , NULL);
    if(0!=ecrireTextSDL(carteSDL , "police/OpenSans-Regular.ttf" , "Quitter" , 50 , &quitter , &colorfg , NULL)){
        fprintf(stderr , "\nErreur SDL ttf");
        quitterDessinerMenu(quitter , jouer);
        return -1;
    }
    SDL_QueryTexture(quitter , NULL , NULL , &rectQuitter.w , &rectQuitter.h);
    rectQuitter.x=rectMenu->w/3-rectQuitter.w/2;
    rectQuitter.y=rectMenu->h/2-rectQuitter.h/2;
    if(0!=ecrireTextSDL(carteSDL , "police/OpenSans-Regular.ttf" , "Jouer" , 50 , &jouer , &colorfg , NULL)){
        fprintf(stderr , "\nErreur SDL ttf");
        quitterDessinerMenu(quitter , jouer);
        return -1;
    }
    SDL_QueryTexture(jouer , NULL , NULL , &rectJouer.w , &rectJouer.h);
    rectJouer.x=(rectMenu->w/3)*2-rectJouer.w/2;
    rectJouer.y=rectMenu->h/2-rectJouer.h/2;
    SDL_RenderCopy(carteSDL->renderer , quitter , NULL , &rectQuitter);
    SDL_RenderCopy(carteSDL->renderer , jouer , NULL , &rectJouer);
    SDL_SetRenderTarget(carteSDL->renderer , NULL);
    SDL_RenderCopy(carteSDL->renderer , *menu , NULL , rectMenu);
    return 0;
}
void quitterMenu(SDL_Texture *texture1 , SDL_Texture *texture2){
    if(texture1!=NULL){
        SDL_DestroyTexture(texture1);
    }
    if(texture2!=NULL){
        SDL_DestroyTexture(texture2);
    }
}
int menu(CarteSDL *carteSDL){
    SDL_Texture *title=NULL , *menu=NULL;
    SDL_Color fontColor={255 , 255 , 255 , 255};
    SDL_Rect dstRect={0 , 0 , 0 , 0} , rectMenu={0 , 0 , 0 , 0};
    int w=0 , h=0;
    if(0!=ecrireTextSDL(carteSDL , "police/OpenSans-Regular.ttf" , "Trapped Hero" , 200 , &title , &fontColor , NULL)){
        fprintf(stderr , "\nErreur SDL_ttf\n");
        quitterMenu(title , menu);
        return -1;
    }
    SDL_GetWindowSize(carteSDL->window , &w , &h);
    rectMenu.x=0;
    rectMenu.y=h-200;
    rectMenu.w=w;
    rectMenu.h=200;
    SDL_SetRenderDrawColor(carteSDL->renderer , 38 , 38 , 38 , 38);
    SDL_RenderClear(carteSDL->renderer);
    SDL_QueryTexture(title , NULL , NULL , &dstRect.w , &dstRect.h);
    dstRect.x=(w/2)-(dstRect.w/2);
    dstRect.y=((h-rectMenu.h)/2)-(dstRect.h/2);
    SDL_RenderCopy(carteSDL->renderer  , title , NULL , &dstRect);
    if(0!=dessinerMenu(carteSDL , &menu , &rectMenu)){
        fprintf(stderr , "\nError print menu");
        quitterMenu(title , menu);
        return -1;
    }
    SDL_RenderPresent(carteSDL->renderer);
    SDL_Delay(5000);
    quitterMenu(title , menu);
    return 0;
}
