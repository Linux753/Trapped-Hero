#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/structure.h"
#include "../include/menu.h"

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
int chargerTileOrSprite(CarteSDL *carteSDL , SDL_Texture *image ,
    SDL_Texture **sprite , int x , int y , int sizeTileW , int sizeTileH){
    SDL_Rect srcRect;
    if(0!=SDL_SetRenderTarget(carteSDL->renderer  , *sprite)){
        fprintf(stderr , "Erreur SDL_SetRenderTarget : %s" , SDL_GetError());
        return -1;
    }
    srcRect.h=sizeTileH;
    srcRect.w=sizeTileW;
    srcRect.x=sizeTileW*x;
    srcRect.y=sizeTileH*y;
    SDL_RenderClear(carteSDL->renderer);
    SDL_RenderCopy(carteSDL->renderer , image , &srcRect , NULL);
    if(0!=SDL_SetRenderTarget(carteSDL->renderer  , NULL)){
        fprintf(stderr , "Erreur SDL_SetRenderTarget : %s" , SDL_GetError());
        return -1;
    }
    return 0;
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
    carteSDL->window = SDL_CreateWindow("Generateur carte" , SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED , 900 , 900 , SDL_WINDOW_SHOWN|SDL_WINDOW_FULLSCREEN_DESKTOP);
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
    if(carteSDL->vide!=NULL){
        SDL_DestroyTexture(carteSDL->vide);
    }
    if(carteSDL->chemin!=NULL){
        SDL_DestroyTexture(carteSDL->chemin);
    }
    if(carteSDL->porte!=NULL){
        SDL_DestroyTexture(carteSDL->porte);
    }
    if(carteSDL->mur!=NULL){
        SDL_DestroyTexture(carteSDL->mur);
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
int initialiserTile(CarteSDL *carteSDL , int w , int h){
    int out=0;
    carteSDL->mur[0]=SDL_CreateTexture(carteSDL->renderer , SDL_PIXELFORMAT_RGBA8888 , SDL_TEXTUREACCESS_TARGET , w , h);
    if(carteSDL->mur[0]==NULL){
        fprintf(stderr , "Erreur SDL_CreateTexture : %s" , SDL_GetError());
        out=-1;
    }
    if(0!=SDL_SetTextureBlendMode(carteSDL->mur[0] ,SDL_BLENDMODE_BLEND)){
        fprintf(stderr , "Error SDL_SetTextureBlendMode : %s" , SDL_GetError());
        out=-1;
    }
    carteSDL->mur[1]=SDL_CreateTexture(carteSDL->renderer , SDL_PIXELFORMAT_RGBA8888 , SDL_TEXTUREACCESS_TARGET , w , h);
    if(carteSDL->mur[1]==NULL){
        fprintf(stderr , "Erreur SDL_CreateTexture : %s" , SDL_GetError());
        out=-1;
    }
    if(0!=SDL_SetTextureBlendMode(carteSDL->mur[1] ,SDL_BLENDMODE_BLEND)){
        fprintf(stderr , "Error SDL_SetTextureBlendMode : %s" , SDL_GetError());
        out=-1;
    }
    carteSDL->mur[2]=SDL_CreateTexture(carteSDL->renderer , SDL_PIXELFORMAT_RGBA8888 , SDL_TEXTUREACCESS_TARGET , w , h);
    if(carteSDL->mur[2]==NULL){
        fprintf(stderr , "Erreur SDL_CreateTexture : %s" , SDL_GetError());
        out=-1;
    }
    if(0!=SDL_SetTextureBlendMode(carteSDL->mur[2] ,SDL_BLENDMODE_BLEND)){
        fprintf(stderr , "Error SDL_SetTextureBlendMode : %s" , SDL_GetError());
        out=-1;
    }
    carteSDL->chemin[0]=SDL_CreateTexture(carteSDL->renderer , SDL_PIXELFORMAT_RGBA8888 , SDL_TEXTUREACCESS_TARGET , w , h);
    if(carteSDL->chemin[0]==NULL){
        fprintf(stderr , "Erreur SDL_CreateTexture : %s" , SDL_GetError());
        out=-1;
    }
    if(0!=SDL_SetTextureBlendMode(carteSDL->chemin[0] ,SDL_BLENDMODE_BLEND)){
        fprintf(stderr , "Error SDL_SetTextureBlendMode : %s" , SDL_GetError());
        out=-1;
    }
    carteSDL->chemin[1]=SDL_CreateTexture(carteSDL->renderer , SDL_PIXELFORMAT_RGBA8888 , SDL_TEXTUREACCESS_TARGET , w , h);
    if(carteSDL->chemin[1]==NULL){
        fprintf(stderr , "Erreur SDL_CreateTexture : %s" , SDL_GetError());
        out=-1;
    }
    if(0!=SDL_SetTextureBlendMode(carteSDL->chemin[1] ,SDL_BLENDMODE_BLEND)){
        fprintf(stderr , "Error SDL_SetTextureBlendMode : %s" , SDL_GetError());
        out=-1;
    }
    carteSDL->chemin[2]=SDL_CreateTexture(carteSDL->renderer , SDL_PIXELFORMAT_RGBA8888 , SDL_TEXTUREACCESS_TARGET , w , h);
    if(carteSDL->chemin[2]==NULL){
        fprintf(stderr , "Erreur SDL_CreateTexture : %s" , SDL_GetError());
        out=-1;
    }
    if(0!=SDL_SetTextureBlendMode(carteSDL->chemin[2] ,SDL_BLENDMODE_BLEND)){
        fprintf(stderr , "Error SDL_SetTextureBlendMode : %s" , SDL_GetError());
        out=-1;
    }
    carteSDL->porte=SDL_CreateTexture(carteSDL->renderer , SDL_PIXELFORMAT_RGBA8888 , SDL_TEXTUREACCESS_TARGET , w , h );
    if(carteSDL->porte==NULL){
        fprintf(stderr , "Erreur SDL_CreateTexture : %s" , SDL_GetError());
        out=-1;
    }
    if(0!=SDL_SetTextureBlendMode(carteSDL->porte ,SDL_BLENDMODE_BLEND)){
        fprintf(stderr , "Error SDL_SetTextureBlendMode : %s" , SDL_GetError());
        out=-1;
    }
    carteSDL->vide=SDL_CreateTexture(carteSDL->renderer , SDL_PIXELFORMAT_RGBA8888 , SDL_TEXTUREACCESS_TARGET , w , h);
    if(carteSDL->vide==NULL){
        fprintf(stderr , "Erreur SDL_CreateTexture : %s" , SDL_GetError());
        out=-1;
    }
    if(0!=SDL_SetTextureBlendMode(carteSDL->vide ,SDL_BLENDMODE_BLEND)){
        fprintf(stderr , "Error SDL_SetTextureBlendMode : %s" , SDL_GetError());
        out=-1;
    }
    carteSDL->escalierBas=SDL_CreateTexture(carteSDL->renderer , SDL_PIXELFORMAT_RGBA8888 , SDL_TEXTUREACCESS_TARGET , w , h);
    if(carteSDL->escalierBas==NULL){
        fprintf(stderr , "Erreur SDL_CreateTexture : %s" , SDL_GetError());
        out=-1;
    }
    if(0!=SDL_SetTextureBlendMode(carteSDL->escalierBas,SDL_BLENDMODE_BLEND)){
        fprintf(stderr , "Error SDL_SetTextureBlendMode : %s" , SDL_GetError());
        out=-1;
    }
    carteSDL->escalierHaut=SDL_CreateTexture(carteSDL->renderer , SDL_PIXELFORMAT_RGBA8888 , SDL_TEXTUREACCESS_TARGET , w , h);
    if(carteSDL->escalierHaut==NULL){
        fprintf(stderr , "Erreur SDL_CreateTexture : %s" , SDL_GetError());
        out=-1;
    }
    if(0!=SDL_SetTextureBlendMode(carteSDL->escalierHaut ,SDL_BLENDMODE_BLEND)){
        fprintf(stderr , "Error SDL_SetTextureBlendMode : %s" , SDL_GetError());
        out=-1;
    }
    carteSDL->treasor=SDL_CreateTexture(carteSDL->renderer , SDL_PIXELFORMAT_RGBA8888 , SDL_TEXTUREACCESS_TARGET , w , h);
    if(carteSDL->treasor==NULL){
        fprintf(stderr , "Erreur SDL_CreateTexture : %s" , SDL_GetError());
        out=-1;
    }
    if(0!=SDL_SetTextureBlendMode(carteSDL->treasor ,SDL_BLENDMODE_BLEND)){
        fprintf(stderr , "Error SDL_SetTextureBlendMode : %s" , SDL_GetError());
        out=-1;
    }
    carteSDL->treasorOpen=SDL_CreateTexture(carteSDL->renderer , SDL_PIXELFORMAT_RGBA8888 , SDL_TEXTUREACCESS_TARGET , w , h);
    if(carteSDL->treasorOpen==NULL){
        fprintf(stderr , "Erreur SDL_CreateTexture : %s" , SDL_GetError());
        out=-1;
    }
    if(0!=SDL_SetTextureBlendMode(carteSDL->treasorOpen ,SDL_BLENDMODE_BLEND)){
        fprintf(stderr , "Error SDL_SetTextureBlendMode : %s" , SDL_GetError());
        out=-1;
    }
    return out;
}
int initialiserMonster(CarteSDL *carteSDL , int w ,int  h){
    int out=0;
    carteSDL->personnage=SDL_CreateTexture(carteSDL->renderer , SDL_PIXELFORMAT_RGBA8888 , SDL_TEXTUREACCESS_TARGET , w , h);
    if(carteSDL->personnage==NULL){
        fprintf(stderr , "Erreur SDL_CreateTexture : %s" , SDL_GetError());
        out=-1;
    }
    if(0!=SDL_SetTextureBlendMode(carteSDL->personnage ,SDL_BLENDMODE_BLEND)){
        fprintf(stderr , "Error SDL_SetTextureBlendMode : %s" , SDL_GetError());
        out=-1;
    }
    return out;
}
int loadTileset(CarteSDL *carteSDL){
    SDL_Texture *tileset=NULL , *monster=NULL;
    SDL_Rect srcRect={0 , 0 , 0 , 0};
    int wTileset=0  , hTileset=0 , sizeTileW=0 ,sizeTileH=0 ,wMonster=0  , hMonster=0 , sizeMonsterW=0 ,sizeMonsterH=0  , out=0;
    if(0!=loadIMG(carteSDL , "image/tileset.png" , &tileset)){
        out=-1;
        goto loadTilesetQuit;
    }
    SDL_QueryTexture(tileset , NULL , NULL  , &wTileset , &hTileset);
    sizeTileW=wTileset/6;
    sizeTileH=hTileset/2;
    if(0!=loadIMG(carteSDL , "image/monsters.png" , &monster)){
        out=-1;
        goto loadTilesetQuit;
    }
    SDL_QueryTexture(monster , NULL , NULL  , &wMonster , &hMonster);
    sizeMonsterW=wMonster/1;
    sizeMonsterH=hMonster/1;
    if(0!=initialiserTile(carteSDL , sizeTileW , sizeTileH)){
        out=-1;
        goto loadTilesetQuit;
    }
    if(0!=initialiserMonster(carteSDL , sizeMonsterW , sizeMonsterH)){
        out=-1;
        goto loadTilesetQuit;
    }
    /*Loading wall tile*/
    if(0!=chargerTileOrSprite(carteSDL , tileset , &(carteSDL->mur[0])  ,0 , 1 , sizeTileW , sizeTileH)){
        fprintf(stderr , "\nErreur chargement image\n");
        out=-1;
        goto loadTilesetQuit;
    }
    if(0!=chargerTileOrSprite(carteSDL , tileset , &(carteSDL->mur[1])  ,1 , 1 , sizeTileW , sizeTileH)){
        fprintf(stderr , "\nErreur chargement image\n");
        out=-1;
        goto loadTilesetQuit;
    }
    if(0!=chargerTileOrSprite(carteSDL , tileset , &(carteSDL->mur[2])  ,2 , 1 , sizeTileW , sizeTileH)){
        fprintf(stderr , "\nErreur chargement image\n");
        out=-1;
        goto loadTilesetQuit;
    }
    /*Loading chemin tile*/
    if(0!=chargerTileOrSprite(carteSDL , tileset , &(carteSDL->chemin[0]) , 3 , 1 , sizeTileW , sizeTileH)){
        fprintf(stderr , "\nErreur chargement image\n");
        out=-1;
        goto loadTilesetQuit;
    }
    if(0!=chargerTileOrSprite(carteSDL , tileset , &(carteSDL->chemin[1]) , 4 , 1 , sizeTileW , sizeTileH)){
        fprintf(stderr , "\nErreur chargement image\n");
        out=-1;
        goto loadTilesetQuit;
    }
    if(0!=chargerTileOrSprite(carteSDL , tileset , &(carteSDL->chemin[2]) , 5 , 1 , sizeTileW , sizeTileH)){
        fprintf(stderr , "\nErreur chargement image\n");
        out=-1;
        goto loadTilesetQuit;
    }
    /*Loading porte tile*/
    if(0!=chargerTileOrSprite(carteSDL , tileset , &(carteSDL->porte) , 5 , 0 , sizeTileW , sizeTileH)){
        fprintf(stderr , "\nErreur chargement image\n");
        out=-1;
        goto loadTilesetQuit;
    }
    /*Loading vide tile*/
    if(0!=chargerTileOrSprite(carteSDL , tileset , &(carteSDL->vide) , 0 , 0 , sizeTileW , sizeTileH)){
        fprintf(stderr , "\nErreur chargement image\n");
        out=-1;
        goto loadTilesetQuit;
    }
    /*Loading scale down*/
    if(0!=chargerTileOrSprite(carteSDL , tileset , &(carteSDL->escalierBas) , 3 , 0 , sizeTileW , sizeTileH)){
        fprintf(stderr , "\nErreur chargement image\n");
        out=-1;
        goto loadTilesetQuit;
    }
    /*Loading scale up*/
    if(0!=chargerTileOrSprite(carteSDL , tileset , &(carteSDL->escalierHaut) , 4 , 0 , sizeTileW , sizeTileH)){
        fprintf(stderr , "\nErreur chargement image\n");
        out=-1;
        goto loadTilesetQuit;
    }
    /*Loading treasor*/
    if(0!=chargerTileOrSprite(carteSDL , tileset , &(carteSDL->treasor) , 1 , 0 , sizeTileW , sizeTileH)){
        fprintf(stderr , "\nErreur chargement image\n");
        out=-1;
        goto loadTilesetQuit;
    }
    /*Loading treasorOpen*/
    if(0!=chargerTileOrSprite(carteSDL , tileset , &(carteSDL->treasorOpen) , 2 , 0 , sizeTileW , sizeTileH)){
        fprintf(stderr , "\nErreur chargement image\n");
        out=-1;
        goto loadTilesetQuit;
    }
    /*Loading personnage*/
    if(0!=chargerTileOrSprite(carteSDL , monster , &(carteSDL->personnage) , 0 , 0 , sizeMonsterW , sizeMonsterH)){
        fprintf(stderr , "\nErreur chargement image\n");
        out=-1;
        goto loadTilesetQuit;
    }
    /*Quit and free the alloc*/
    loadTilesetQuit :
    if(tileset!=NULL){
        SDL_DestroyTexture(tileset);
    }
    if(monster!=NULL){
        SDL_DestroyTexture(monster);
    }
    return out;
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
int afficherCarte(Carte *carte , CarteSDL *carteSDL){
   // printf("afficherCarte");
    SDL_Rect rect;
    int i=0 , compteur=0 , y=0;
    SDL_SetRenderDrawColor(carteSDL->renderer , 0 , 0 , 0 , 0);
    SDL_RenderClear(carteSDL->renderer);
    for(i=0; i<=(carte->hauteur*carte->largeur)-1; i++){
        rect.y=y;
        rect.x=compteur*9;
        rect.w=9;
        rect.h=9;
        switch(carte->terrain[i].type){
            case VIDE :
                SDL_RenderCopy(carteSDL->renderer , carteSDL->vide , NULL  , &rect );
                //printf("  ");
                break;
            case CHEMIN :
                SDL_RenderCopy(carteSDL->renderer , carteSDL->chemin , NULL  , &rect );
                //printf("@ " );
                break;
            case MUR:
                SDL_RenderCopy(carteSDL->renderer , carteSDL->mur , NULL  , &rect );
                //printf("[]" );
                break;
            //case ESCALIER:
              //  SDL_SetRenderDrawColor(renderer , 206 , 206 , 206 , 0);
                ////printf("E ");
                //break;
            case MUR_SALLE :
                SDL_RenderCopy(carteSDL->renderer , carteSDL->mur , NULL  , &rect );
                //printf("##");
                break;
            case SOL_SALLE :
                SDL_RenderCopy(carteSDL->renderer , carteSDL->chemin , NULL  , &rect );
                //printf("..");
                break;
            case PORTE :
                if(carte->terrain[i].orientation==HORIZONTALE){
                    //printf("__");
                    SDL_RenderCopy(carteSDL->renderer , carteSDL->porte , NULL  , &rect );
                }
                else if(carte->terrain[i].orientation==VERTICALE){
                    //printf("| ");
                    SDL_RenderCopy(carteSDL->renderer , carteSDL->porte , NULL  , &rect );
                }
                break;
            case MUR_CHEMIN :
                SDL_RenderCopy(carteSDL->renderer , carteSDL->mur , NULL  , &rect );
                //printf("+ ");
                break;
        }
        switch(carte->terrain[i].object){
            case ESCALIER_HAUT :
                SDL_RenderCopy(carteSDL->renderer , carteSDL->escalierHaut , NULL  , &rect );
                //printf("+ ");
                break;
            case ESCALIER_BAS :
                SDL_RenderCopy(carteSDL->renderer , carteSDL->escalierBas , NULL  , &rect );
                //printf("+ ");
                break;
        }
        if(compteur==(carte->largeur-1)){
            compteur=0;
            //printf("\n");
            y=y+9;
        }else{
            compteur++;
        }
    }
    SDL_RenderPresent(carteSDL->renderer);
    for(i=0;i<=50;i++){
        SDL_RenderPresent(carteSDL->renderer);
        SDL_Delay(500);
    }
    return 0;
}
int reajusterCadrage(Carte *carte ,int position ,  int windowH,int  windowW , int tileNbW ,int tileNbH ){
    int i=0 , continuer=1;
    while(carte->largeur*carte->hauteur<position+carte->largeur*tileNbH){
        position=position-carte->largeur;
        //position=position-((position+carte->largeur*tileNbH)-((carte->largeur*carte->hauteur)-1));
    }
    if((position+1)%carte->largeur!=0){
        i=position+1;
        while(i<position+tileNbW&&continuer==1){
            if(carte->terrain[i].type==MUR){
                position=position-(tileNbW-i);
                //i--;
                continuer=0;
                printf("On a reculé de : %d\n" , position-(tileNbW-i));
            }
            i++;
        }
      //  printf("Valeur de pos modul carte->largeur: %d" , position+1%carte->largeur);
    }
    else{
        printf("\nRecul total\nAutre info pour le passsage : %d\n\n" , tileNbW);
        position=position-tileNbW;
    }
    return position;
}
int afficherCarteZoom(Carte *carte , CarteSDL *carteSDL , int position , int taille  , SDL_Keycode event){
    int positionTheorique=0,  windowH=0, windowW=0 , tileNbW=0 , tileNbH=0 , i=position , y=0 , compteurW=0 , compteurH=0 ;
    SDL_Rect rect={0 , 0 , 0 , 0};
    SDL_GetWindowSize(carteSDL->window , &windowW , &windowH);
    //printf("%d\n" , carte->posPerso);
    SDL_SetRenderDrawColor(carteSDL->renderer , 255 , 255 , 255 , 255);
    SDL_RenderClear(carteSDL->renderer );
    tileNbH=windowH/taille;
    tileNbW=windowW/taille;
    if(position==99999){
        position=carte->posPerso-(tileNbW/2+((tileNbH/2)*carte->largeur));
        //position=reajusterCadrage(carte , position , windowH , windowW , tileNbW , tileNbH);
    }
    positionTheorique=position+(tileNbW/2+((tileNbH/2)*carte->largeur));
    if((position%carte->largeur==0)||(position+(tileNbH*carte->largeur)>carte->largeur*(carte->hauteur-1))||(position<carte->largeur)||((position+tileNbW+1)%carte->largeur==0)){
        if(position+(tileNbH*carte->largeur)>carte->largeur*(carte->hauteur-1)){
            if(carte->posPerso<positionTheorique+(positionTheorique%carte->largeur)){
                position-=carte->largeur;
            }
            else if(carte->posPerso%carte->largeur>(positionTheorique+1)%carte->largeur){
                position++;
            }
            else if(carte->posPerso%carte->largeur<(positionTheorique-1)%carte->largeur){
                position--;
            }
        }
        if(position<carte->largeur){
            if(carte->posPerso>positionTheorique+(positionTheorique%carte->largeur)){
                position+=carte->largeur;
            }
            else if(carte->posPerso%carte->largeur<(positionTheorique-1)%carte->largeur){
                position--;
            }
            else if(carte->posPerso%carte->largeur>(positionTheorique+1)%carte->largeur){
                position++;
            }
        }
        if((position+tileNbW+1)%carte->largeur==0){
            if(carte->posPerso%carte->largeur<positionTheorique%carte->largeur){
                position--;
            }
            else if(carte->posPerso<positionTheorique-(carte->largeur+(positionTheorique%carte->largeur))){
                position-=carte->largeur;
            }
            else if(carte->posPerso>positionTheorique+(carte->largeur+(positionTheorique%carte->largeur))){
                position+=carte->largeur;
            }
        }
        if(position%carte->largeur==0){
            if(carte->posPerso%carte->largeur>positionTheorique%carte->largeur){
                position++;
            }
            else if(carte->posPerso<positionTheorique-(carte->largeur+(positionTheorique%carte->largeur))){
                position-=carte->largeur;
            }
            else if(carte->posPerso>positionTheorique+(carte->largeur+(positionTheorique%carte->largeur))){
                position+=carte->largeur;
            }
        }
    }
    else if((carte->posPerso>positionTheorique+1&&carte->posPerso!=positionTheorique+carte->largeur)
    ||(carte->posPerso<positionTheorique-1&&carte->posPerso!=positionTheorique-carte->largeur)){
    //printf("ICI2n");
        switch(event){
            case SDLK_UP :
                   if(position>carte->largeur){
                    position-=carte->largeur;
                   }
                break;
            case SDLK_DOWN :
                   if(position+(tileNbH*carte->largeur)<(carte->largeur*(carte->hauteur-1))){
                    position+=carte->largeur;
                   }
                break;
            case SDLK_RIGHT :
                    if((position+tileNbW+1)%carte->largeur!=0){
                    position++;
                   }
                break;
            case SDLK_LEFT :
                  if(position%carte->largeur!=0){
                    position--;
                  }
                break;
        }
    }
    i=position;
        while(compteurH<tileNbH+1){
        rect.y=y;
        rect.x=compteurW*taille;
        rect.w=taille;
        rect.h=taille;
        switch(carte->terrain[i].type){
            case VIDE :
                SDL_RenderCopy(carteSDL->renderer , carteSDL->vide , NULL  , &rect );
                //printf("  ");
                break;
            case CHEMIN :
                SDL_RenderCopy(carteSDL->renderer , carteSDL->chemin[carte->terrain[i].numeroTile] , NULL  , &rect );
                //printf("@ " );
                break;
            case MUR:
                SDL_RenderCopy(carteSDL->renderer , carteSDL->mur[carte->terrain[i].numeroTile] , NULL  , &rect );
                //printf("[]" );
                break;
            case MUR_SALLE :
                SDL_RenderCopy(carteSDL->renderer , carteSDL->mur[carte->terrain[i].numeroTile] , NULL  , &rect );
                //printf("##");
                break;
            case SOL_SALLE :
                SDL_RenderCopy(carteSDL->renderer , carteSDL->chemin[carte->terrain[i].numeroTile] , NULL  , &rect );
                //printf("..");
                break;
            case PORTE :
                SDL_RenderCopy(carteSDL->renderer , carteSDL->chemin , NULL  , &rect );
                if(carte->terrain[i].orientation==HORIZONTALE){
                    //printf("__");
                    SDL_RenderCopy(carteSDL->renderer , carteSDL->porte , NULL  , &rect );
                }
                else if(carte->terrain[i].orientation==VERTICALE){
                    //printf("| ");
                    SDL_RenderCopy(carteSDL->renderer , carteSDL->porte , NULL  , &rect );
                }
                break;
            case MUR_CHEMIN :
                SDL_RenderCopy(carteSDL->renderer , carteSDL->mur[carte->terrain[i].numeroTile] , NULL  , &rect );
                //printf("+ ");
                break;
        }
        switch(carte->terrain[i].object){
            case ESCALIER_HAUT :
                SDL_RenderCopy(carteSDL->renderer , carteSDL->escalierHaut , NULL  , &rect );
                //printf("+ ");
                break;
            case ESCALIER_BAS :
                SDL_RenderCopy(carteSDL->renderer , carteSDL->escalierBas , NULL  , &rect );
                //printf("+ ");
                break;
            case COFFRE :
                SDL_RenderCopy(carteSDL->renderer , carteSDL->treasor , NULL  , &rect );
                //printf("+ ");
                break;
            case TREASOR_OPEN :
                SDL_RenderCopy(carteSDL->renderer , carteSDL->treasorOpen , NULL  , &rect );
                //printf("+ ");
                break;
        }
        if(i==carte->posPerso){
            SDL_RenderCopy(carteSDL->renderer , carteSDL->personnage , NULL  , &rect );
        }
        if(compteurW==tileNbW){
            compteurW=0;
            y=y+taille;
            compteurH++;
            i=position+carte->largeur*compteurH;
            //printf("Valeur %d  " , position+carte->largeur*compteurH);
        }else{
            i++;
            compteurW++;
        }
        if(i>=carte->largeur*carte->hauteur){
            //printf("Erreur debordement\n");
        }
    }
    SDL_RenderPresent(carteSDL->renderer);
    return position;
}
