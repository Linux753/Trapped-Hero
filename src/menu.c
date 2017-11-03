#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "../include/structure.h"
#include "../include/Afficher_carte.h"

int ecrireTextSDL(CarteSDL* carteSDL , char* file,char* text ,int size ,  SDL_Texture** texture , SDL_Color *colorFg){
    SDL_Surface *surface=NULL;
    TTF_Font*font=NULL;
    int out=0;
    font=TTF_OpenFont(file , size);
    if(font==NULL){
        fprintf(stderr , "Erreur TTF_OpenFont : %s" , TTF_GetError());
        out=-1;
        goto QuitEcrireTextSDL;
    }
    surface=TTF_RenderUTF8_Blended(font , text  , *colorFg );
    if(surface==NULL){
        fprintf(stderr , "Erreur TTF_RenderUTF8_Blended() : %s" , TTF_GetError());
        out=-1;
        goto QuitEcrireTextSDL;
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
    ecrireTextSDL(sdlVar , "police/OpenSans-Regular.ttf" , "Created by Linux with :", 80  , &textSDL , &colorFg  );
    SDL_QueryTexture(textSDL , NULL , NULL , &rectTextSDL.w , &rectTextSDL.h);
    rectTextSDL.x=(w/2)-(rectTextSDL.w/2);
    rectTextSDL.y=((rectImage1.y)/2)-rectTextSDL.h;
    ecrireTextSDL(sdlVar , "police/OpenSans-Regular.ttf" , "Special thanks to Mr Dator for the compilation on windows", 40  , &specialThank , &colorFg  );
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
/*The following functions are not used*/
int initialiserMenuSprite(CarteSDL *carteSDL ,
    SDL_Texture **mage1 , SDL_Texture **mage2 ,
    SDL_Texture **archer1 , SDL_Texture **archer2 ,
    SDL_Texture **warrior1 , SDL_Texture **warrior2 ,
    int w , int h){
    *mage1=SDL_CreateTexture(carteSDL->renderer , SDL_PIXELFORMAT_RGBA8888 , SDL_TEXTUREACCESS_TARGET , w , h);
    if(*mage1==NULL){
        fprintf(stderr , "Erreur SDL_CreateTexture() : %s" , SDL_GetError());
        return -1;
    }
    if(0!=SDL_SetTextureBlendMode(*mage1 , SDL_BLENDMODE_BLEND)){
        fprintf(stderr , "Erreur 1 SDL_SetTextureBlendMode() : %s" , SDL_GetError());
        return -1;
    }
    *mage2=SDL_CreateTexture(carteSDL->renderer , SDL_PIXELFORMAT_RGBA8888 , SDL_TEXTUREACCESS_TARGET , w , h);
    if(*mage2==NULL){
        fprintf(stderr , "Erreur 2 SDL_CreateTexture() : %s" , SDL_GetError());
        return -1;
    }
    if(0!=SDL_SetTextureBlendMode(*mage2 , SDL_BLENDMODE_BLEND)){
        fprintf(stderr , "Erreur 3 SDL_SetTextureBlendMode() : %s" , SDL_GetError());
        return -1;
    }
    *archer1=SDL_CreateTexture(carteSDL->renderer , SDL_PIXELFORMAT_RGBA8888 , SDL_TEXTUREACCESS_TARGET , w , h);
    if(*archer1==NULL){
        fprintf(stderr , "Erreur 4 SDL_CreateTexture() : %s" , SDL_GetError());
        return -1;
    }
    if(0!=SDL_SetTextureBlendMode(*archer1 , SDL_BLENDMODE_BLEND)){
        fprintf(stderr , "Erreur 5 SDL_SetTextureBlendMode() : %s" , SDL_GetError());
        return -1;
    }
    *archer2=SDL_CreateTexture(carteSDL->renderer , SDL_PIXELFORMAT_RGBA8888 , SDL_TEXTUREACCESS_TARGET , w , h);
    if(*archer2==NULL){
        fprintf(stderr , "Erreur 6 SDL_CreateTexture() : %s" , SDL_GetError());
        return -1;
    }
    if(0!=SDL_SetTextureBlendMode(*archer2 , SDL_BLENDMODE_BLEND)){
        fprintf(stderr , "Erreur 7 SDL_SetTextureBlendMode() : %s" , SDL_GetError());
        return -1;
    }
    *warrior1=SDL_CreateTexture(carteSDL->renderer , SDL_PIXELFORMAT_RGBA8888 , SDL_TEXTUREACCESS_TARGET , w , h);
    if(*warrior1==NULL){
        fprintf(stderr , "Erreur 8 SDL_CreateTexture() : %s" , SDL_GetError());
        return -1;
    }
    if(0!=SDL_SetTextureBlendMode(*warrior1 , SDL_BLENDMODE_BLEND)){
        fprintf(stderr , "Erreur 9 SDL_SetTextureBlendMode() : %s" , SDL_GetError());
        return -1;
    }
    *warrior2=SDL_CreateTexture(carteSDL->renderer , SDL_PIXELFORMAT_RGBA8888 , SDL_TEXTUREACCESS_TARGET , w , h);
    if(*warrior2==NULL){
        fprintf(stderr , "Erreur 10 SDL_CreateTexture() : %s" , SDL_GetError());
        return -1;
    }
    if(0!=SDL_SetTextureBlendMode(*warrior2 , SDL_BLENDMODE_BLEND)){
        fprintf(stderr , "Erreur 11 SDL_SetTextureBlendMode() : %s" , SDL_GetError());
        return -1;
    }
    return 0;
}
int chargerSpriteMenu(CarteSDL *carteSDL ,
    SDL_Texture *mage1 , SDL_Texture *mage2 ,
    SDL_Texture *archer1 , SDL_Texture *archer2 ,
    SDL_Texture *warrior1 , SDL_Texture *warrior2 ,
    SDL_Texture *image , int hSprite , int wSprite){
    if(0!=chargerTileOrSprite(carteSDL , image , &mage1 , 2 , 0 , wSprite , hSprite)){
        fprintf(stderr , "\nErreur loading sprite\n");
        return -1;
    }
    if(0!=chargerTileOrSprite(carteSDL , image , &mage2 , 2 , 1 , wSprite , hSprite)){
        fprintf(stderr , "\nErreur loading sprite\n");
        return -1;
    }
    if(0!=chargerTileOrSprite(carteSDL , image , &archer1 , 1 , 0 , wSprite , hSprite)){
        fprintf(stderr , "\nErreur loading sprite\n");
        return -1;
    }
    if(0!=chargerTileOrSprite(carteSDL , image , &archer2 , 1 , 1 , wSprite , hSprite)){
        fprintf(stderr , "\nErreur loading sprite\n");
        return -1;
    }
    if(0!=chargerTileOrSprite(carteSDL , image , &warrior1 , 0 , 0 , wSprite , hSprite)){
        fprintf(stderr , "\nErreur loading sprite\n");
        return -1;
    }
    if(0!=chargerTileOrSprite(carteSDL , image , &warrior2 , 0 , 1 , wSprite , hSprite)){
        fprintf(stderr , "\nErreur loading sprite\n");
        return -1;
    }
    return 0;
}
void menuQuit(SDL_Texture *texture1 , SDL_Texture *texture2 ,SDL_Texture *texture3 ,SDL_Texture *texture4 , SDL_Texture *texture5 , SDL_Texture *texture6 , SDL_Texture *texture7){
    if(texture1!=NULL){
        SDL_DestroyTexture(texture1);
    }
    if(texture2!=NULL){
        SDL_DestroyTexture(texture2);
    }
    if(texture3!=NULL){
        SDL_DestroyTexture(texture3);
    }
    if(texture4!=NULL){
        SDL_DestroyTexture(texture4);
    }
    if(texture5!=NULL){
        SDL_DestroyTexture(texture5);
    }
    if(texture6!=NULL){
        SDL_DestroyTexture(texture6);
    }
    if(texture7!=NULL){
        SDL_DestroyTexture(texture7);
    }
}
int afficherSpriteMenu(CarteSDL* carteSDL ,
    SDL_Texture *mage ,SDL_Texture *archer , SDL_Texture *warrior ,
    int wSprite , int hSprite){
    int wWindow=0 , hWindow=0;
    SDL_Rect dstRect;
    SDL_SetRenderDrawColor(carteSDL->renderer  , 38 , 38 , 38 , 0);
    SDL_RenderClear(carteSDL->renderer);
    SDL_GetWindowSize(carteSDL->window , &wWindow , &hWindow);
    dstRect.w=(wWindow/3)-40;
    dstRect.h=hSprite*(dstRect.w/wSprite);
    dstRect.x=0;
    dstRect.y=50;
    if(0!=SDL_RenderCopy(carteSDL->renderer , mage , NULL , &dstRect)){
        fprintf(stderr , "Erreur SDL_RenderCopy() : %s" , SDL_GetError());
        return -1;
    }
    dstRect.x=dstRect.x+dstRect.w;
    if(0!=SDL_RenderCopy(carteSDL->renderer , archer , NULL , &dstRect)){
        fprintf(stderr , "Erreur SDL_RenderCopy() : %s" , SDL_GetError());
        return -1;
    }
    dstRect.x=dstRect.x+dstRect.w;
    if(0!=SDL_RenderCopy(carteSDL->renderer , warrior , NULL , &dstRect)){
        fprintf(stderr , "Erreur SDL_RenderCopy() : %s" , SDL_GetError());
        return -1;
    }
    SDL_RenderPresent(carteSDL->renderer);
    return 0;
    }
int menu(CarteSDL *carteSDL){
    int wSprite=0 , hSprite=0 ,hImageSprite=0 , wImageSprite=0  , tempsActuel=SDL_GetTicks() , tempsOrigine=0 , tempsAncien=0 , continuer=1;
    SDL_Event event;
    SDL_Texture *sprite=NULL , *mage1=NULL , *mage2=NULL , *archer1=NULL , *archer2=NULL , *warrior1=NULL , *warrior2=NULL;
    printf("w=%d , h=%d", wSprite , hSprite);
    if(0!=loadIMG(carteSDL , "image/menuSprite.png" , &sprite)){
        fprintf(stderr , "\nErreur de chargement de l'image\n");
        menuQuit(sprite , mage1 , mage2 , archer1 , archer2 , warrior1 , warrior2);
        return -1;
    }
    SDL_QueryTexture(sprite , NULL , NULL , &wImageSprite , &hImageSprite);
    wSprite=wImageSprite/3;
    hSprite=hImageSprite/2;
    if(0!=initialiserMenuSprite(carteSDL , &mage1 , &mage2 , &archer1 , &archer2 , &warrior1 , &warrior2 , wSprite , hSprite)){
        fprintf(stderr , "\nErreur création des texture\n");
        menuQuit(sprite , mage1 , mage2 , archer1 , archer2 , warrior1 , warrior2);
        return -1;
    }
    if(0!=chargerSpriteMenu(carteSDL , mage1 , mage2  , archer1 , archer2 , warrior1 , warrior2 , sprite , hSprite , wSprite)){
        fprintf(stderr , "\nErreur chargement des texture\n");
        menuQuit(sprite , mage1 , mage2 , archer1 , archer2 , warrior1 , warrior2);
        return -1;
    }
    tempsOrigine=SDL_GetTicks();
    while(continuer){
        if(tempsActuel-tempsAncien>500&&tempsActuel-tempsAncien<800){
            afficherSpriteMenu(carteSDL ,mage1 , archer1 , warrior1 , wSprite , hSprite );
        }
        else if(tempsActuel-tempsAncien>1000){
            tempsAncien=tempsActuel;
            afficherSpriteMenu(carteSDL ,mage2 , archer2 , warrior2 , wSprite , hSprite);
        }
        if(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_KEYDOWN :
                    switch(event.key.keysym.sym){
                        case SDLK_KP_ENTER :
                            continuer=0;
                            break;
                        case SDLK_RETURN :
                            continuer=0;
                            break;
                    }
                    break;
            }
        }else{
            SDL_Delay(500);
        }
        tempsActuel=SDL_GetTicks();
    }
    return 0;
}
