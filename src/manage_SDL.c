#include "../include/structure.h"
#include "../include/menu.h"
#include "../include/Afficher_carte.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>

int InitialiserSDL(CarteSDL *carteSDL){
    if(0!=TTF_Init()){
        fprintf(stderr , "Erreur SDL_Init : %s" , SDL_GetError());
        return -1;
    }
    if(0!=SDL_Init(SDL_INIT_VIDEO)){
        fprintf(stderr , "Erreur SDL_Init : %s" , SDL_GetError());
        return -1;
    }
    carteSDL->window = SDL_CreateWindow("Trapped Hero" , SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED , 900 , 900 , SDL_WINDOW_SHOWN|SDL_WINDOW_FULLSCREEN_DESKTOP);
    if(carteSDL->window==NULL){
        fprintf(stderr , "Erreur SDL_CreateWindow : %s" , SDL_GetError());
        return -1;
    }
    carteSDL->renderer=SDL_CreateRenderer(carteSDL->window , -1 , SDL_RENDERER_ACCELERATED);
    if(carteSDL->renderer==NULL){
        fprintf(stderr , "Erreur SDL_CreateRenderer : %s" , SDL_GetError());
        return -1;
    }
    carteSDL->mur=malloc(sizeof(SDL_Texture*)*3);
    carteSDL->chemin=malloc(sizeof(SDL_Texture*)*3);
    return 0;
}

void quitterSDL(CarteSDL *carteSDL){
    int i=0;
    if(carteSDL->vide!=NULL){
        SDL_DestroyTexture(carteSDL->vide);
    }
    for(i=0; i<3; i++){
        if(carteSDL->chemin[i]!=NULL){
        SDL_DestroyTexture(carteSDL->chemin[i]);
        printf("Destruction texture nb %d\n" , i);
        }
    }
    for(i=0; i<3; i++){
        if(carteSDL->mur[i]!=NULL){
            SDL_DestroyTexture(carteSDL->mur[i]);
            printf("Destruction texture nb %d\n" , i);
        }
    }
    if(carteSDL->porte!=NULL){
        SDL_DestroyTexture(carteSDL->porte);
    }
    if(carteSDL->escalierHaut!=NULL){
        SDL_DestroyTexture(carteSDL->escalierHaut);
    }
    if(carteSDL->escalierBas!=NULL){
        SDL_DestroyTexture(carteSDL->escalierBas);
    }
    if(carteSDL->treasor!=NULL){
        SDL_DestroyTexture(carteSDL->treasor);
    }
    if(carteSDL->treasorOpen!=NULL){
        SDL_DestroyTexture(carteSDL->treasorOpen);
    }
    if(carteSDL->personnage!=NULL){
        SDL_DestroyTexture(carteSDL->personnage);
    }
    if(carteSDL->renderer!=NULL){
        SDL_DestroyRenderer(carteSDL->renderer);
    }
    if(carteSDL->window!=NULL){
        SDL_DestroyWindow(carteSDL->window);
    }
    TTF_Quit();
    SDL_Quit();
    free(carteSDL);
}

CarteSDL *initialiserCarteSDL(){
    CarteSDL *carteSDL=malloc(sizeof(CarteSDL));
    if(0!=InitialiserSDL(carteSDL)){
        quitterSDL(carteSDL);
        fprintf(stderr , "Error SDL finish the print of the map");
        return NULL;
    }
    demarrage(carteSDL);
    if(0!=loadTileset(carteSDL)){
        quitterSDL(carteSDL);
        fprintf(stderr , "Error SDL finish the print of the map");
        return NULL;
    }
    return carteSDL;
}

int loadIMG(CarteSDL *carteSDL , char *file , SDL_Texture** texture ){
    SDL_Surface *surface=NULL;
    surface=IMG_Load(file);
    if(surface==NULL){
        fprintf(stderr , "Error SDL IMG_Load : %s" , SDL_GetError());
        return -1;
    }
    if(0!=SDL_SetSurfaceBlendMode(surface ,SDL_BLENDMODE_BLEND)){
        fprintf(stderr , "Error SDL_SetSurfaceBlendMode : %s" , SDL_GetError());
        return -1;
    }
    *texture=SDL_CreateTextureFromSurface(carteSDL->renderer , surface);
    if(*texture==NULL){
        fprintf(stderr , "Error SDL IMG_Load : %s" , SDL_GetError());
        if(surface!=NULL){
           SDL_FreeSurface(surface);
        }
        return -1;
    }
    if(0!=SDL_SetTextureBlendMode(*texture ,SDL_BLENDMODE_BLEND)){
        fprintf(stderr , "Error SDL_SetTextureBlendMode : %s" , SDL_GetError());
        return -1;
    }
    if(surface!=NULL){
        SDL_FreeSurface(surface);
    }
    return 0;
}
