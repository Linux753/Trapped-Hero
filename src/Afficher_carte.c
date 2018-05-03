#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/structure.h"
#include "../include/manage_SDL.h"
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
int initialiserTile(CarteSDL *carteSDL , int w , int h){
    int out=0 , i=0;
    for(i=0; i<3; i++){
        carteSDL->mur[i]=SDL_CreateTexture(carteSDL->renderer , SDL_PIXELFORMAT_RGBA8888 , SDL_TEXTUREACCESS_TARGET , w , h);
        if(carteSDL->mur[i]==NULL){
            fprintf(stderr , "Erreur SDL_CreateTexture : %s" , SDL_GetError());
            out=-1;
        }
        if(0!=SDL_SetTextureBlendMode(carteSDL->mur[i] ,SDL_BLENDMODE_BLEND)){
            fprintf(stderr , "Error SDL_SetTextureBlendMode : %s" , SDL_GetError());
            out=-1;
        }
    }
    for(i=0; i<3; i++){
        carteSDL->chemin[i]=SDL_CreateTexture(carteSDL->renderer , SDL_PIXELFORMAT_RGBA8888 , SDL_TEXTUREACCESS_TARGET , w , h);
        if(carteSDL->chemin[i]==NULL){
            fprintf(stderr , "Erreur SDL_CreateTexture : %s" , SDL_GetError());
            out=-1;
        }
        if(0!=SDL_SetTextureBlendMode(carteSDL->chemin[i] ,SDL_BLENDMODE_BLEND)){
            fprintf(stderr , "Error SDL_SetTextureBlendMode : %s" , SDL_GetError());
            out=-1;
        }
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
    int wTileset=0  , hTileset=0 , sizeTileW=0 ,sizeTileH=0 ,wMonster=0  , hMonster=0 , sizeMonsterW=0 ,sizeMonsterH=0  , out=0 , i=0;
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
    for(i=0; i<3; i++){
        if(0!=chargerTileOrSprite(carteSDL , tileset , &(carteSDL->mur[i])  ,i , 1 , sizeTileW , sizeTileH)){
            fprintf(stderr , "\nErreur chargement image\n");
            out=-1;
            goto loadTilesetQuit;
        }
    }
    /*Loading chemin tile*/
    for(i=0; i<3; i++){
        if(0!=chargerTileOrSprite(carteSDL , tileset , &(carteSDL->chemin[i]) , i+3 , 1 , sizeTileW , sizeTileH)){
            fprintf(stderr , "\nErreur chargement image\n");
            out=-1;
            goto loadTilesetQuit;
        }
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
    SDL_Texture *texture=NULL;
    SDL_GetWindowSize(carteSDL->window , &windowW , &windowH);
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
        SDL_SetRenderDrawColor(carteSDL->renderer , 38 , 38 , 38 , 100);
        while(compteurH<tileNbH+1){
        rect.y=y;
        rect.x=compteurW*taille;
        rect.w=taille;
        rect.h=taille;
        //Loading tile
        if(carte->terrain[i].voile==HIDDEN){
            SDL_RenderCopy(carteSDL->renderer , carteSDL->vide , NULL  , &rect );
        }
        else{
            switch(carte->terrain[i].type){
                case VIDE :
                    texture=carteSDL->vide;
                    break;
                case CHEMIN :
                    texture=carteSDL->chemin[carte->terrain[i].numeroTile];
                    break;
                case MUR:
                    texture=carteSDL->mur[carte->terrain[i].numeroTile];
                    break;
                case MUR_SALLE :
                    texture=carteSDL->mur[carte->terrain[i].numeroTile];
                    break;
                case SOL_SALLE :
                    texture=carteSDL->chemin[carte->terrain[i].numeroTile];
                    break;
                case PORTE :
                    texture=carteSDL->porte;
                    break;
                case MUR_CHEMIN :
                    texture=carteSDL->mur[carte->terrain[i].numeroTile];
                    break;
            }
            //Now copy the texture of tile on the renderer
            if(texture!=NULL){
                SDL_RenderCopy(carteSDL->renderer , texture , NULL  , &rect );
                texture=NULL;
            }
            //Loading object
            switch(carte->terrain[i].object){
                case ESCALIER_HAUT :
                    texture=carteSDL->escalierHaut;
                    break;
                case ESCALIER_BAS :
                    texture=carteSDL->escalierBas;
                    break;
                case COFFRE :
                    texture=carteSDL->treasor;
                    break;
                case TREASOR_OPEN :
                    texture=carteSDL->treasorOpen;
                    break;
            }
            //Now copy the texture of object on the renderer
            if(texture!=NULL){
                SDL_RenderCopy(carteSDL->renderer , texture , NULL  , &rect );
                texture=NULL;
            }
            if(i==carte->posPerso){
                SDL_RenderCopy(carteSDL->renderer , carteSDL->personnage , NULL  , &rect );
            }else if(carte->terrain[i].voile==VISITED){
                SDL_RenderFillRect(carteSDL->renderer , &rect);
            }
        }
        if(compteurW==tileNbW){
            compteurW=0;
            y=y+taille;
            compteurH++;
            i=position+carte->largeur*compteurH;
        }else{
            i++;
            compteurW++;
        }
        if(i>=carte->largeur*carte->hauteur){
            printf("Erreur debordement\n");
        }
    }
    SDL_RenderPresent(carteSDL->renderer);
    return position;
}
