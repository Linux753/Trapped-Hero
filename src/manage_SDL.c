#include "../include/structure.h"
#include "../include/menu.h"
#include "../include/Afficher_carte.h"
#include "../include/inventaire.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>

SDL_Rect setRect(int w , int h , int x , int y){
    SDL_Rect rect;
    rect.x=x;
    rect.y=y;
    rect.w=w;
    rect.h=h;
    return rect;
}
SDL_Texture *copyRenderToTexture(CarteSDL *carteSDL){
    int pitch=0 , wW=0 , hW=0;
    SDL_Surface *surface;
    SDL_Texture *texture;
    Uint32 *pixels=NULL;
    SDL_GetWindowSize(carteSDL->window, &wW ,&hW);
    pitch = wW*sizeof(Uint32);
    pixels=malloc(pitch*hW);
    if(0!=SDL_RenderReadPixels(carteSDL->renderer, NULL, SDL_PIXELFORMAT_RGBA8888, pixels, pitch)){
        fprintf(stderr, "Ereur SDL_RenderReadPixels() : %s\n",SDL_GetError() );
        return NULL;
    }
    surface=SDL_CreateRGBSurfaceWithFormatFrom(pixels, wW, hW, 32, pitch, SDL_PIXELFORMAT_RGBA8888);
    if(surface==NULL){
        fprintf(stderr, "Erreur SDL_CreateRGBSurfaceWithFormatFrom() : %s\n", SDL_GetError());
        return NULL;
    }
    if(0!=SDL_SetSurfaceBlendMode(surface ,SDL_BLENDMODE_BLEND)){
        fprintf(stderr , "Error SDL_SetSurfaceBlendMode : %s" , SDL_GetError());
        return NULL;
    }
    texture=SDL_CreateTextureFromSurface(carteSDL->renderer , surface);
    if(texture==NULL){
        fprintf(stderr , "Error SDL IMG_Load : %s" , SDL_GetError());
        if(surface!=NULL){
           SDL_FreeSurface(surface);
        }
        return NULL;
    }
    if(0!=SDL_SetTextureBlendMode(texture ,SDL_BLENDMODE_BLEND)){
        fprintf(stderr , "Error SDL_SetTextureBlendMode : %s" , SDL_GetError());
        if(surface!=NULL){
           SDL_FreeSurface(surface);
        }
        if(texture!=NULL){
            SDL_DestroyTexture(texture);
        }
        return NULL;
    }
    if(surface!=NULL){
        SDL_FreeSurface(surface);
    }
    return texture;
}
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
    if(0!=SDL_SetRenderDrawBlendMode(carteSDL->renderer ,SDL_BLENDMODE_BLEND)){
            fprintf(stderr , "Error SDL_SetRenderDrawBlendMode : %s" , SDL_GetError());
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
    free(carteSDL->chemin);
    for(i=0; i<3; i++){
        if(carteSDL->mur[i]!=NULL){
            SDL_DestroyTexture(carteSDL->mur[i]);
            printf("Destruction texture nb %d\n" , i);
        }
    }
    free(carteSDL->mur);
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
    for(i=0; i>carteSDL->nbObjet; i++){
        SDL_DestroyTexture(carteSDL->listeObjet[i].texture);
    }
    if(carteSDL->renderer!=NULL){
        SDL_DestroyRenderer(carteSDL->renderer);
    }
    if(carteSDL->window!=NULL){
        SDL_DestroyWindow(carteSDL->window);
    }
    if(carteSDL->perso!=NULL){
        if(carteSDL->perso->inventaireArme!=NULL){
        free(carteSDL->perso->inventaireArme);
        }
        if(carteSDL->perso->inventaireBaton!=NULL){
        free(carteSDL->perso->inventaireBaton);
        }
        if(carteSDL->perso->inventaireArmure!=NULL){
        free(carteSDL->perso->inventaireArmure);
        }
        if(carteSDL->perso->inventairePotion!=NULL){
        free(carteSDL->perso->inventairePotion);
        }
        if(carteSDL->perso->inventaireParchemin!=NULL){
        free(carteSDL->perso->inventaireParchemin);
        }
        if(carteSDL->perso->texture!=NULL){
        SDL_DestroyTexture(carteSDL->perso->texture);
        }
        free(carteSDL->perso);
    }
    if(carteSDL->persoInventaire!=NULL){
        if(carteSDL->persoInventaire->texture!=NULL){
            SDL_DestroyTexture(carteSDL->persoInventaire->texture);
        }
        if(carteSDL->persoInventaire->textureCadre!=NULL){
            SDL_DestroyTexture(carteSDL->persoInventaire->textureCadre);
        }
        if(carteSDL->persoInventaire->selectArme!=NULL){
            SDL_DestroyTexture(carteSDL->persoInventaire->selectArme);
        }
        if(carteSDL->persoInventaire->selectArmure!=NULL){
            SDL_DestroyTexture(carteSDL->persoInventaire->selectArmure);
        }
        if(carteSDL->persoInventaire->selectBaton!=NULL){
            SDL_DestroyTexture(carteSDL->persoInventaire->selectBaton);
        }
        if(carteSDL->persoInventaire->selectParchemin!=NULL){
            SDL_DestroyTexture(carteSDL->persoInventaire->selectParchemin);
        }
        if(carteSDL->persoInventaire->selectPotion!=NULL){
            SDL_DestroyTexture(carteSDL->persoInventaire->selectPotion);
        }
        if(carteSDL->persoInventaire->textureCadreDroit!=NULL){
            SDL_DestroyTexture(carteSDL->persoInventaire->textureCadreDroit);
        }
        if(carteSDL->persoInventaire->textureCadreGauche!=NULL){
            SDL_DestroyTexture(carteSDL->persoInventaire->textureCadreGauche);
        }
        free(carteSDL->persoInventaire);
    }
    free(carteSDL->listeObjet);
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
    initialiserPersonnage(carteSDL);
    initialiserPersoInventaire(carteSDL);
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
        if(surface!=NULL){
           SDL_FreeSurface(surface);
        }
        return -1;
    }
    if(surface!=NULL){
        SDL_FreeSurface(surface);
    }
    return 0;
}
