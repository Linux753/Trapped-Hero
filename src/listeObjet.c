#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "../include/structure.h"
#include "../include/manage_SDL.h"
int calculerProbabilite(Objet *objet , Carte* carte , int numMax){
    int probabilite=0;
    printf("Ouais et me voila dans la fonction\n");
    if(carte->floor<objet->niveau){
        objet->numMin=0;
        printf("Et c'est lorsque les objet sont trop puissant\n" );
        printf("Ceci est leur etage : %d\n",objet->niveau );
        objet->numMax=0;
        return numMax;
    }
    else if(carte->floor>objet->niveau+objet->nbEtage){
        printf("Etage : %d\n", carte->floor);
        probabilite=objet->rarete-(carte->floor-(objet->niveau+(objet->nbEtage/2)))*(carte->floor-(objet->niveau+(objet->nbEtage/2)));
        printf("%d\n", probabilite );
        objet->numMin=numMax+1;
        objet->numMax=objet->numMin+probabilite*10;
        if(objet->numMax-objet->numMin<2){
            objet->numMax=objet->numMin+2;
        }
        numMax=objet->numMax;
        return numMax;
    }
    else{
        objet->numMin=numMax+1;
        objet->numMax=objet->numMin+objet->rarete;
        numMax=objet->numMax;
        printf("Ici le nummax de l'objet : %d\n",objet->numMax );
        return numMax;
    }
}
int chargerTexture(CarteSDL *carteSDL , SDL_Texture *image , Objet *objet){
    SDL_Rect srcRect;
    objet->texture=SDL_CreateTexture(carteSDL->renderer , SDL_PIXELFORMAT_RGBA8888 , SDL_TEXTUREACCESS_TARGET , 64 , 64 );
    if(objet->texture==NULL){
        fprintf(stderr , "Erreur SDL_CreateTexture : %s" , SDL_GetError());
        return -1;
    }
    if(0!=SDL_SetTextureBlendMode(objet->texture ,SDL_BLENDMODE_BLEND)){
        fprintf(stderr , "Error SDL_SetTextureBlendMode : %s" , SDL_GetError());
        return -1;
    }
    if(0!=SDL_SetRenderTarget(carteSDL->renderer  , objet->texture)){
        fprintf(stderr , "Erreur SDL_SetRenderTarget : %s" , SDL_GetError());
        return -1;
    }
    srcRect.h=64;
    srcRect.w=64;
    srcRect.x=64*objet->x;
    srcRect.y=64*objet->y;
    printf("x : %d\ny : %d\n",objet->x , objet->y );
    SDL_SetRenderDrawColor(carteSDL->renderer , 255 , 255 , 255 , 0);
    SDL_RenderClear(carteSDL->renderer);
    if(0!=SDL_RenderCopy(carteSDL->renderer , image , &srcRect , NULL)){
        printf("Erreur de copie d'une portion de l'image sur la texture de l'objet\n");
    }
    if(0!=SDL_SetRenderTarget(carteSDL->renderer  , NULL)){
        fprintf(stderr , "Erreur SDL_SetRenderTarget : %s" , SDL_GetError());
        return -1;
    }
    printf("Texture de %s créée\n", objet->nom);
    return 0;
}
int creerListe(CarteSDL *carteSDL){
    FILE* file=NULL;
    SDL_Texture *tileset=NULL;
    int i=0;
    Objet* nouveau;
    float poids;
    int type;
    int typeAttaque;
    int resistance;
    int resistanceMagique;
    int attaque;
    int attaqueMax;
    int caracteristiqueCritique;
    int precision;
    int habilete;
    int magie;
    char nom[50];
    char description[5000];
    int probabilite;
    int rarete;
    int niveau;
    int nbEtage;
    int x=0;
    int y=0;
    int w=0 , h=0;
    int protection=0;
    carteSDL->numMax=0;
    file=fopen("carte/objetCarte/listeObjet.liste" , "r");
    if(file==NULL){
        printf("Et voila t bete\n" );
    }
    fscanf(file ,"[%d][%d][%d]\n" , &(carteSDL->nbObjet) , &w , &h);
    carteSDL->listeObjet=malloc(sizeof(Objet)*carteSDL->nbObjet);
    if(0!=loadIMG(carteSDL , "image/objectTileset.png" , &tileset)){
        fprintf(stderr, "Erreur Chargement image\n" );
        return -1;
    }
    for(i=0; i<carteSDL->nbObjet; i++){
        fscanf(file, "[%[^\]]s" , nom);
        fscanf(file ,"][%[^\]]s" , description);
        printf("%s\n",description );
        printf("%d" , nbEtage);
        fscanf(file , "][%d][%d][%f][%d][%d][%d][%d][%d][%d][%d][%d][%d][%d][%d]",&type , &typeAttaque , &poids , &resistance , &resistanceMagique, &attaque , &attaqueMax , &caracteristiqueCritique , &precision , &habilete , &magie , &probabilite , &niveau , &rarete);
        fscanf(file ,"[%d][%d][%d][%d]\n" , &nbEtage, &x , &y , &protection);
        printf("Ici valeur y : %d\n",y );
        nouveau=&(carteSDL->listeObjet[i]);
        switch(type){
            case 1:
                nouveau->type=Rien;
                break;
            case 2:
                nouveau->type=Or;
                break;
            case 3:
                nouveau->type=Epe;
                break;
            case 4:
                nouveau->type=Armure;
                break;
            case 5:
                nouveau->type=Arc;
                break;
            case 6:
                nouveau->type=Baton;
                break;
            case 7:
                nouveau->type=BatonMagique;
                break;
            case 8:
                nouveau->type=Parchemin;
                break;
            case 9:
                nouveau->type=Potion;
                break;
            case 10:
                nouveau->type=Porte;
                break;
            case 11:
                nouveau->type=EscalierBas;
                break;
            case 12:
                nouveau->type=Tresor;
                break;
            case 13:
                nouveau->type=Fleche;
                break;
        }
        switch (typeAttaque) {
            case 1:
                nouveau->typeAttaque=Nulle;
                break;
            case 2:
                nouveau->typeAttaque=Arcane;
                break;
            case 3:
                nouveau->typeAttaque=Tranchant;
                break;
            case 4:
                nouveau->typeAttaque=Froid;
                break;
            case 5:
                nouveau->typeAttaque=Feu;
                break;
            case 6:
                nouveau->typeAttaque=Perforant;
                break;
            case 7:
                nouveau->typeAttaque=Contendant;
                break;
        }
        nouveau->poids=poids;
        nouveau->resistance=resistance;
        nouveau->resistanceOriginale=resistance;
        nouveau->resistanceMagique=resistanceMagique;
        sprintf(nouveau->nom , nom);
        sprintf(nouveau->description , description);
        nouveau->attaque=attaque;
        nouveau->attaqueMax=attaqueMax;
        nouveau->caracteristiqueCritique=caracteristiqueCritique;
        nouveau->precision=precision;
        nouveau->habilete=habilete;
        nouveau->magie=magie;
        nouveau->probabilite=probabilite;
        nouveau->rarete=rarete;
        nouveau->niveau=niveau;
        nouveau->nbEtage=nbEtage;
        nouveau->x=x;
        nouveau->y=y;
        nouveau->protection=protection;
        if(0!=chargerTexture(carteSDL , tileset , nouveau)){
            fprintf(stderr, "Erreur chargerTexture()\n" );
            return -1;
        }
    }
    return 0;
}
