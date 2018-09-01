#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "../include/structure.h"
#include "../include/manage_SDL.h"
#include "../include/menu.h"
#define INTERLIGNE 5

void clearStr(char* str){
    int i=0 , lenStr=0;
    lenStr=strlen(str);
    for(i=0; i<lenStr; i++){
        str[i]='\0';
    }
}
void quitEcrireMotCarteSDL(SDL_Surface *surface , SDL_Texture *texture , TTF_Font *font){
    if(surface!=NULL){
        SDL_FreeSurface(surface);
    }
    if(texture!=NULL){
        SDL_DestroyTexture(texture);
    }
    if(font!=NULL){
        TTF_CloseFont(font);
    }
}
SDL_Texture *ecrireSDLSolid(CarteSDL *carteSDL , char* file , char* texte ,int size , SDL_Color colorFg){
    SDL_Surface *surface=NULL;
    SDL_Texture *texture=NULL;
    TTF_Font* font=NULL;
    font=TTF_OpenFont(file , size);
    if(font==NULL){
        fprintf(stderr , "Erreur TTF_OpenFont : %s" , TTF_GetError());
        return NULL;
        quitEcrireMotCarteSDL(surface, texture, font);
    }
    surface=TTF_RenderUTF8_Solid(font , texte  , colorFg );
    if(surface==NULL){
        fprintf(stderr , "Erreur TTF_RenderUTF8_Blended() : %s" , TTF_GetError());
        return NULL;
        quitEcrireMotCarteSDL(surface, texture, font);
    }
    texture=SDL_CreateTextureFromSurface(carteSDL->renderer , surface);
    if(texture==NULL){
        fprintf(stderr , "Erreur SDL_CreateTextureFromSurface() : %s" , SDL_GetError());
        return NULL;
        quitEcrireMotCarteSDL(surface, texture, font);
    }
    quitEcrireMotCarteSDL(surface, NULL, font);
    return texture;
}
void majRectSelect(CarteSDL* carteSDL){
    int y=0 , i=0 , nb=0;
    carteSDL->persoInventaire->rectArme=setRect(150, 100, 0+carteSDL->persoInventaire->affichage.x, carteSDL->persoInventaire->affichage.y);
    carteSDL->persoInventaire->rectArmure=setRect(150, 100, 150+carteSDL->persoInventaire->affichage.x, carteSDL->persoInventaire->affichage.y);
    carteSDL->persoInventaire->rectParchemin=setRect(150, 100, 300+carteSDL->persoInventaire->affichage.x, carteSDL->persoInventaire->affichage.y);
    carteSDL->persoInventaire->rectBaton=setRect(150, 100, 450+carteSDL->persoInventaire->affichage.x, carteSDL->persoInventaire->affichage.y);
    carteSDL->persoInventaire->rectPotion=setRect(150, 100, 600+carteSDL->persoInventaire->affichage.x, carteSDL->persoInventaire->affichage.y);
    for(y=0; y<4;y++){
        for(i=0; i<10;i++){
            carteSDL->persoInventaire->rectObjet[nb]=setRect(64, 64, 4+(74*i)+carteSDL->persoInventaire->affichage.x, 105+(74*y)+carteSDL->persoInventaire->affichage.y);
            nb++;
        }
    }
}
int mouseOnObject(CarteSDL *carteSDL , SDL_Point point){
    int continuer=1 , nb=0;
    while(continuer&&nb<40){
        if(SDL_TRUE==SDL_PointInRect(&point , &(carteSDL->persoInventaire->rectObjet[nb]))){
            continuer=0;
        }
        else{
            nb++;
        }
    }
    return nb;
}
void afficherObjetInventaire(CarteSDL* carteSDL , Type type){
    int* invObjet;
    int i=0 , nbW=0;
    SDL_Rect dstRect;
    dstRect.w=150;
    dstRect.h=100;
    printf("Ici on affiche des objets\n" );
    if(type==Epe){
        invObjet=carteSDL->perso->inventaireArme;
        dstRect.x=0;
        dstRect.y=0;
        SDL_RenderCopy(carteSDL->renderer, carteSDL->persoInventaire->selectArme, NULL, &dstRect);
    }
    else if(type==Armure){
        invObjet=carteSDL->perso->inventaireArmure;
        dstRect.x=150;
        dstRect.y=0;
        SDL_RenderCopy(carteSDL->renderer, carteSDL->persoInventaire->selectArmure, NULL, &dstRect);
    }
    else if(type==Parchemin){
        invObjet=carteSDL->perso->inventaireParchemin;
        dstRect.x=300;
        dstRect.y=0;
        SDL_RenderCopy(carteSDL->renderer, carteSDL->persoInventaire->selectParchemin, NULL, &dstRect);
    }
    else if(type==Baton){
        invObjet=carteSDL->perso->inventaireBaton;
        dstRect.x=450;
        dstRect.y=0;
        SDL_RenderCopy(carteSDL->renderer, carteSDL->persoInventaire->selectBaton, NULL, &dstRect);
    }
    else if(type==Potion){
        printf("Ici on veut afficher inventaire potion\n");
        invObjet=carteSDL->perso->inventairePotion;
        dstRect.x=600;
        dstRect.y=0;
        SDL_RenderCopy(carteSDL->renderer, carteSDL->persoInventaire->selectPotion, NULL, &dstRect);
    }
    dstRect.w=64;
    dstRect.h=64;
    dstRect.x=4;
    dstRect.y=105;
    while(invObjet[i]!=0){
        SDL_RenderCopy(carteSDL->renderer, carteSDL->listeObjet[invObjet[i]].texture,NULL, &dstRect);
        if(nbW==9){
            nbW=0;
            dstRect.x=4;
            dstRect.y=dstRect.y+75;
        }
        else{
            dstRect.x=dstRect.x+75;
            nbW++;
        }
        i++;
    }
}
void calculerInventaire(CarteSDL *carteSDL , Type type){
    int wW , wH;
    SDL_Rect *dstRect=&(carteSDL->persoInventaire->affichage);
    SDL_SetRenderDrawColor(carteSDL->renderer, 155 , 155 , 155, 0);
    SDL_SetRenderTarget(carteSDL->renderer, carteSDL->persoInventaire->texture);
    SDL_RenderClear(carteSDL->renderer);
    SDL_RenderCopy(carteSDL->renderer, carteSDL->persoInventaire->textureCadre, NULL, NULL);
    afficherObjetInventaire(carteSDL, type);
    SDL_SetRenderTarget(carteSDL->renderer, NULL);
    SDL_QueryTexture(carteSDL->persoInventaire->texture,NULL , NULL ,  &(dstRect->w), &(dstRect->h));
    SDL_GetWindowSize(carteSDL->window, &wW, &wH);
    dstRect->x=(wW/2)-(dstRect->w/2);
    dstRect->y=(wH/2)-(dstRect->h/2);
    carteSDL->persoInventaire->affiche=1;
}
void quitCreateWindowStatsButton(SDL_Texture* texture1 , SDL_Texture *texture2){
    if(texture1!=NULL){
        SDL_DestroyTexture(texture1);
    }
    if(texture2!=NULL){
        SDL_DestroyTexture(texture2);
    }
}
SDL_Texture* createWindowStatsButton(CarteSDL *carteSDL , char *texte , SDL_Rect *rectSelect){
    SDL_Texture *bouton=NULL , *texteTexture=NULL;
    SDL_Color colorFg , colorBg;
    SDL_Rect dstRect;
    int w=0 , h=0;
    colorFg.r=255;
    colorFg.g=255;
    colorFg.b=255;
    colorFg.a=255;
    colorBg.r=0;
    colorBg.g=0;
    colorBg.b=0;
    colorBg.a=0;
    texteTexture=ecrireSDLSolid(carteSDL, "police/pixel.ttf", texte, 40, colorFg);
    SDL_QueryTexture(texteTexture  , NULL  ,NULL,&w ,&h);
    bouton=SDL_CreateTexture(carteSDL->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w+10, h+10);
    if(bouton==NULL){
        fprintf(stderr, "Erreur SDL_CreateTexture dans createWindowStatsButton : %s\n", SDL_GetError());
        quitCreateWindowStatsButton(bouton, texteTexture);
        return NULL;
    }
    if(0!=SDL_SetTextureBlendMode(bouton, SDL_BLENDMODE_BLEND)){
        fprintf(stderr, "Erreur SDL_SetTextureBlendMode() dans createWindowStatsButton() : %s\n", SDL_GetError() );
        quitCreateWindowStatsButton(bouton, texteTexture);
        return NULL;
    }
    rectSelect->w=w+10;
    rectSelect->h=h+10;
    SDL_SetRenderTarget(carteSDL->renderer, bouton);
    dstRect=setRect(25, rectSelect->h, 0, 0);
    SDL_RenderCopy(carteSDL->renderer, carteSDL->persoInventaire->textureCadreGauche, NULL, &dstRect);
    dstRect=setRect(25, rectSelect->h, rectSelect->w-25, 0);
    SDL_RenderCopy(carteSDL->renderer, carteSDL->persoInventaire->textureCadreDroit, NULL, &dstRect);
    dstRect=setRect( rectSelect->w-50, rectSelect->h, 25, 0);
    if(dstRect.w>=1){
        SDL_SetRenderDrawColor(carteSDL->renderer,133, 6,6, 255);
        SDL_RenderFillRect(carteSDL->renderer, &dstRect);
    }
    dstRect=setRect(w,h, (rectSelect->w/2)-(w/2), (rectSelect->h/2)-(h/2));
    SDL_RenderCopy(carteSDL->renderer, texteTexture, NULL, &dstRect);
    SDL_SetRenderTarget(carteSDL->renderer, NULL);
    quitCreateWindowStatsButton(NULL, texteTexture);
    return bouton;
}

char *createTextWithSize(CarteSDL *carteSDL ,char *text , int tailleMax , int *num , int *wPhrase , int *hPhrase){
    int numAncien=0, numNouveau=0 , continuer=1 , i=0 , continuer2=1 , nb , w=0 , wMot=0 , hMot=0;
    char *mot=NULL , *phrase=NULL;
    TTF_Font* font;
    printf("In createTextWithSize()\n");
    font=TTF_OpenFont("police/pixel4.ttf", 30);
    if(font==NULL){
        fprintf(stderr , "Erreur TTF_OpenFont : %s" , TTF_GetError());
        if(mot!=NULL){
            free(mot);
        }
        if(phrase!=NULL){
            free(phrase);
        }
        return NULL;
    }
    printf("In createTextWithSize() font open\n");
    mot=malloc(40*sizeof(char));
    phrase=malloc(tailleMax*sizeof(char));
    for(i=0 ; i<tailleMax; i++){
        phrase[i]='\0';
    }
    printf("In createTextWithSize() phrase initialized\n");
    while(continuer){
        printf("In createTextWithSize() boucle while\n");
        numAncien=numNouveau;
        for(i=0 ; i<40; i++){
            mot[i]='\0';
        }
        while(text[numNouveau]!=' '&&continuer2==1){
            printf("In createTextWithSize() boucle while 2 %d %c\n" , numNouveau ,text[numNouveau]);
            if(text[numNouveau]=='\0'){
                continuer2=0;
                continuer=0;
                printf("Ici continuer2 =0\n" );
            }
            numNouveau++;
        }
        numNouveau++;
        nb=numNouveau-numAncien;
        for(i=0;i<nb;i++){
            mot[i]=text[i+numAncien];
        }
        TTF_SizeText(font, mot, &wMot,&hMot);
        printf("w+wMot = %d tailleMax = %d\n", w+wMot , tailleMax);
        if(w+(wMot)<tailleMax){
            sprintf(phrase, "%s%s" , phrase , mot);
            printf("In createTextWithSize() condition if %s\n" , phrase);
            w=w+(wMot);
        }
        else{
            continuer2=1;
            continuer=0;
            printf("In createTextWithSize() quit fonction normal end\n");
        }
    }
    TTF_SizeText(font, phrase, wPhrase,hPhrase);
    if(mot!=NULL){
        free(mot);
    }
    if(continuer2==0){
        *num=-1;
    }
    else{
        *num=*num+numAncien;
    }
    printf("Out createTextWithSize()\n");
    return phrase;
}
void quitWriteSpecificObject(SDL_Texture* texture1 , SDL_Texture *texture2 , SDL_Texture *texture3  , SDL_Texture** textureTab){
    int i=0;
    if(texture1!=NULL){
        SDL_DestroyTexture(texture1);
    }
    if(texture2!=NULL){
        SDL_DestroyTexture(texture2);
    }
    if(texture3!=NULL){
        SDL_DestroyTexture(texture3);
    }
    if(textureTab!=NULL){
        for(i=0;i<8;i++){
            if(textureTab[i]!=NULL){
                SDL_DestroyTexture(textureTab[i]);
            }
        }
        free(textureTab);
    }
}
SDL_Texture* writeSpecificObject(CarteSDL* carteSDL , int objet){
    SDL_Texture *textureGauche=NULL, *textureDroite=NULL , *texture=NULL , **textureStats=NULL;
    SDL_Rect rectTexture , dstRect , rectStats[8] ;
    SDL_Color colorFg={0 , 0 , 0 , 255};
    int wMax=0 , hMax=0  , hStats=0, wStats=0, size=30 , i=0;
    char stats[64];
    textureStats=malloc(sizeof(SDL_Texture*)*8);
    for(i=0; i<8;i++){
        clearStr(stats);
        switch (i) {
            case 0:
                sprintf(stats, "Poids : %f" , carteSDL->listeObjet[objet].poids);
                break;
            case 1:
                sprintf(stats, "Resistance : %d" , carteSDL->listeObjet[objet].resistance);
                break;
            case 2:
                sprintf(stats, "R. magie : %d" , carteSDL->listeObjet[objet].resistanceMagique);
                break;
            case 3:
                sprintf(stats, "Attaque : %d/%d" , carteSDL->listeObjet[objet].attaque , carteSDL->listeObjet[objet].attaqueMax);
                break;
            case 4:
                switch ((carteSDL->listeObjet[objet].typeAttaque)) {
                    case Nulle:
                        sprintf(stats, "Attaque t. : -");
                        break;
                    case Arcane:
                        sprintf(stats, "Attaque t. : Arcane");
                        break;
                    case Tranchant:
                        sprintf(stats, "Attaque t. : Tranchant");
                        break;
                    case Froid :
                        sprintf(stats, "Attaque t. : Froid");
                        break;
                    case Feu :
                        sprintf(stats, "Attaque t. : Feu");
                        break;
                    case Perforant:
                        sprintf(stats, "Attaque t. : Perforant");
                        break;
                    case Contendant:
                        sprintf(stats, "Attaque t. : Contendant");
                        break;
                }
                break;
            case 5:
                switch (carteSDL->listeObjet[objet].caracteristiqueCritique) {
                    case 1:
                        sprintf(stats, "Precision : %d" , carteSDL->listeObjet[objet].precision);
                        break;
                    case 2:
                        sprintf(stats, "Habilete : %d" , carteSDL->listeObjet[objet].habilete);
                        break;
                    case 3:
                        sprintf(stats, "Magie : %d" , carteSDL->listeObjet[objet].magie);
                        break;
                }
                break;
            case 6:
                sprintf(stats, "Probabilite : %d" , carteSDL->listeObjet[objet].probabilite);
                break;
            case 7:
                sprintf(stats, "Protection : %d" , carteSDL->listeObjet[objet].protection);
                break;
        }
        textureStats[i]=ecrireSDLSolid(carteSDL, "police/pixel4.ttf", stats, size, colorFg);
        SDL_QueryTexture(textureStats[i], NULL, NULL, &wStats, &hStats);
        rectStats[i]=setRect(wStats, hStats, 0, 0);
        if(wStats>wMax){
            wMax=wStats;
        }
        if(hStats>hMax){
            hMax=hStats;
        }
    }
    printf("ICI voici la valeur de wMax : %d\n",wMax );
    rectTexture=setRect(wMax, (hMax+INTERLIGNE)*4, 0, 0);
    textureDroite=SDL_CreateTexture(carteSDL->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, rectTexture.w, rectTexture.h);
    if(textureDroite==NULL){
        fprintf(stderr, "Erreur SDL_CreateTexture() : %s\n",SDL_GetError() );
        quitWriteSpecificObject(texture, textureDroite, textureGauche, textureStats);
        return NULL;
    }
    if(0!=SDL_SetTextureBlendMode(textureDroite, SDL_BLENDMODE_BLEND)){
        fprintf(stderr, "Erreur SDL_SetTextureBlendMode() : %s\n", SDL_GetError());
        quitWriteSpecificObject(texture, textureDroite, textureGauche, textureStats);
        return NULL;
    }
    textureGauche=SDL_CreateTexture(carteSDL->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, rectTexture.w, rectTexture.h);
    if(textureGauche==NULL){
        fprintf(stderr, "Erreur SDL_CreateTexture() : %s\n",SDL_GetError() );
        quitWriteSpecificObject(texture, textureDroite, textureGauche, textureStats);
        return NULL;
    }
    if(0!=SDL_SetTextureBlendMode(textureGauche, SDL_BLENDMODE_BLEND)){
        fprintf(stderr, "Erreur SDL_SetTextureBlendMode() : %s\n", SDL_GetError());
        quitWriteSpecificObject(texture, textureDroite, textureGauche, textureStats);
        return NULL;
    }
    SDL_SetRenderTarget(carteSDL->renderer, textureGauche);
    for(i=0;i<4;i++){
        rectStats[i]=setRect(rectStats[i].w, rectStats[i].h, 0, (hMax+INTERLIGNE)*i);
        SDL_RenderCopy(carteSDL->renderer, textureStats[i], NULL, &(rectStats[i]));
    }
    SDL_SetRenderTarget(carteSDL->renderer, NULL);
    SDL_SetRenderTarget(carteSDL->renderer, textureDroite);
    for(i=4;i<8;i++){
        rectStats[i]=setRect(rectStats[i].w, rectStats[i].h, 0, (hMax+INTERLIGNE)*(i-4));
        SDL_RenderCopy(carteSDL->renderer, textureStats[i], NULL, &(rectStats[i]));
    }
    SDL_SetRenderTarget(carteSDL->renderer, NULL);
    texture=SDL_CreateTexture(carteSDL->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, (wMax*2)+10, (hMax+INTERLIGNE)*4);
    if(texture==NULL){
        fprintf(stderr, "Erreur SDL_CreateTexture() : %s\n",SDL_GetError());
        quitWriteSpecificObject(texture, textureDroite, textureGauche, textureStats);
        return NULL;
    }
    if(0!=SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND)){
        fprintf(stderr, "Erreur SDL_SetTextureBlendMode() : %s\n", SDL_GetError());
        quitWriteSpecificObject(texture, textureDroite, textureGauche, textureStats);
        return NULL;
    }

    SDL_SetRenderTarget(carteSDL->renderer, texture);
    dstRect=setRect(rectTexture.w,rectTexture.h, 0,0);
    SDL_RenderCopy(carteSDL->renderer, textureGauche, NULL, &dstRect);
    dstRect=setRect(rectTexture.w,rectTexture.h, wMax+10,0);
    SDL_RenderCopy(carteSDL->renderer, textureDroite, NULL, &dstRect);
    SDL_SetRenderTarget(carteSDL->renderer, NULL);
    quitWriteSpecificObject(NULL, textureDroite, textureGauche, textureStats);
    return texture;
}
void quitCreateStatsText(SDL_Texture *texture1 , SDL_Texture* texture2  , ListeChar* liste1 , ListeChar* liste2){
    int continuer=1;
    while(continuer){
        liste2=liste1->suivant;
        free(liste1->texte);
        free(liste1);
        if(liste2==NULL){
            continuer=0;
        }
        liste1=liste2;
    }
    if(texture1!=NULL){
        SDL_DestroyTexture(texture1);
    }
    if(texture2!=NULL){
        SDL_DestroyTexture(texture2);
    }
}
SDL_Texture *createStatsText(CarteSDL* carteSDL , int objet , int w){
    printf("In createStatsText()\n");
    ListeChar *premier=malloc(sizeof(ListeChar)) , *listePhrase=NULL;
    SDL_Texture *texture=NULL , *textureTexte=NULL , *textureStatsGauche=NULL , *textureStatsDroite=NULL;
    SDL_Color colorFg={0 , 0 , 0 , 255};
    SDL_Rect dstRect , rectTexture;
    int continuer=1 , num=0 , wPhrase=0 , wMax=0 , hPhrase=0 , hMax=0  , nb=0 , i=0;
    listePhrase=premier;
    listePhrase->suivant=NULL;
    while(continuer){
        listePhrase->texte=createTextWithSize(carteSDL, &(carteSDL->listeObjet[objet].description[num]),w, &num , &wPhrase , &hPhrase);
        if(listePhrase->texte==NULL){
            fprintf(stderr, "Erreur createTextWithSize()\n");
            quitCreateStatsText(texture, textureTexte, premier ,listePhrase);
            return NULL;
        }
        listePhrase->w=wPhrase;
        listePhrase->h=hPhrase;
        if(num==-1){
            printf("Ici c'est finit\n");
            continuer=0;
        }
        else{
            listePhrase->suivant=malloc(sizeof(ListeChar));
            listePhrase=listePhrase->suivant;
            listePhrase->suivant=NULL;
        }
        if(wPhrase>wMax){
            wMax=wPhrase;
        }
        if(hPhrase>hMax){
            hMax=hPhrase;
        }
        nb++;
    }
    rectTexture.w=w;
    rectTexture.h=((hMax+5)*nb)+5;

    texture=SDL_CreateTexture(carteSDL->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, rectTexture.w,rectTexture.h);
    if(texture==NULL){
        fprintf(stderr, "Erreur SDL_CreateTexture() : %s\n", SDL_GetError());
        quitCreateStatsText(texture, textureTexte, premier ,listePhrase);
        return NULL;
    }
    if(0!=SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND)){
        fprintf(stderr, "Erreur SDL_CreateTexture() : %s\n", SDL_GetError());
        quitCreateStatsText(texture, textureTexte, premier ,listePhrase);
        return NULL;
    }
    SDL_SetRenderTarget(carteSDL->renderer, texture);
    SDL_SetRenderDrawColor(carteSDL->renderer, 0, 0, 0, 0);
    SDL_RenderClear(carteSDL->renderer);
    listePhrase=premier;
    for(i=0;i<nb;i++){
        textureTexte=ecrireSDLSolid(carteSDL, "police/pixel4.ttf", listePhrase->texte, 30, colorFg);
        if(textureTexte==NULL){
            fprintf(stderr, "Erreur ecrireSDLSolid()\n");
            quitCreateStatsText(texture, textureTexte, premier ,listePhrase);
            return NULL;
        }
        dstRect=setRect(listePhrase->w, listePhrase->h,0,i*(hMax+5));
        printf("On a écrit : %s aux co y: %d w: %d h: %d\n", listePhrase->texte , dstRect.y  , dstRect.w  , dstRect.h);
        SDL_RenderCopy(carteSDL->renderer, textureTexte, NULL, &dstRect);
        SDL_DestroyTexture(textureTexte);
        textureTexte=NULL;
        listePhrase=listePhrase->suivant;
    }
    SDL_SetRenderTarget(carteSDL->renderer, NULL);
    quitCreateStatsText(NULL, textureTexte, premier ,listePhrase);
    return texture;
}
void calculerPositionAbsolueBouton(SDL_Rect* rectRelatif , SDL_Rect* rect1 , SDL_Rect* rect2 , SDL_Rect* rect3){
    *rect1=setRect(rect1->w, rect1->h, rectRelatif->x+rect1->x, rectRelatif->y+rect1->y);
    *rect2=setRect(rect2->w, rect2->h, rectRelatif->x+rect2->x, rectRelatif->y+rect2->y);
    *rect3=setRect(rect3->w, rect3->h, rectRelatif->x+rect3->x, rectRelatif->y+rect3->y);
}
void quitWindowStatsObject(SDL_Texture* texture1 , SDL_Texture* texture2 , SDL_Texture* texture3 , SDL_Texture* texture4 , SDL_Texture* texture5 , SDL_Texture* texture6 , SDL_Texture* texture7 , SDL_Texture* texture8 , SDL_Texture* texture9 , SDL_Texture* texture10){
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
    if(texture8!=NULL){
        SDL_DestroyTexture(texture8);
    }
    if(texture9!=NULL){
        SDL_DestroyTexture(texture8);
    }
    if(texture10!=NULL){
        SDL_DestroyTexture(texture8);
    }
}
int windowStatsObject(CarteSDL* carteSDL ,int objetSelect , int* listeSelect , char* choix1 , char* choix2 , char* choix3 ){
    SDL_Texture *texture=NULL , *bouton1=NULL , *bouton2=NULL , *bouton3=NULL , *textureTexte=NULL , *textureStats=NULL ,  *textureTitre=NULL , *textureCorner=NULL , *textureBorder=NULL , *textureTop=NULL;
    SDL_Rect rectTexture , rectBouton1 , rectBouton2 , rectBouton3 , rectTextureTexte , rectStats , rectTitre , rectIcone , rectCorner , rectBorder , rectTop , rectFond;
    SDL_Event event;
    SDL_Color colorFg={0 , 0 , 0 , 255};
    SDL_Point mousePos;
    int continuer=1 , rafraichissement=1 , w=0 , h=0 , select=0;
    loadIMG(carteSDL, "image/wObjectCorner.png", &textureCorner);
    if(textureCorner==NULL){
        fprintf(stderr, "Erreur loadIMG()\n");
        quitWindowStatsObject(texture, bouton1, bouton2, bouton3 , textureTexte , textureStats , textureTitre , textureCorner , textureBorder , textureTop);
        return -1;
    }
    rectCorner=setRect(6, 6, 0, 0);
    loadIMG(carteSDL, "image/wObjectBorder.png", &textureBorder);
    if(textureBorder==NULL){
        fprintf(stderr, "Erreur loadIMG()\n");
        quitWindowStatsObject(texture, bouton1, bouton2, bouton3 , textureTexte , textureStats , textureTitre , textureCorner , textureBorder , textureTop);
        return -1;
    }
    loadIMG(carteSDL, "image/wObjectTop.png", &textureTop);
    if(textureTop==NULL){
        fprintf(stderr, "Erreur loadIMG()\n");
        quitWindowStatsObject(texture, bouton1, bouton2, bouton3 , textureTexte , textureStats , textureTitre , textureCorner , textureBorder , textureTop);
        return -1;
    }
    bouton1=createWindowStatsButton(carteSDL, choix1, &rectBouton1);
    if(bouton1==NULL){
        fprintf(stderr, "Erreur createWindowStatsButton()\n");
        quitWindowStatsObject(texture, bouton1, bouton2, bouton3 , textureTexte , textureStats , textureTitre , textureCorner , textureBorder , textureTop);
        return -1;
    }
    bouton2=createWindowStatsButton(carteSDL, choix2, &rectBouton2);
    if(bouton2==NULL){
        fprintf(stderr, "Erreur createWindowStatsButton()\n");
        quitWindowStatsObject(texture, bouton1, bouton2, bouton3 , textureTexte , textureStats , textureTitre , textureCorner , textureBorder , textureTop);
        return -1;
    }
    bouton3=createWindowStatsButton(carteSDL, choix3, &rectBouton3);
    if(bouton3==NULL){
        fprintf(stderr, "Erreur createWindowStatsButton()\n");
        quitWindowStatsObject(texture, bouton1, bouton2, bouton3 , textureTexte , textureStats , textureTitre , textureCorner , textureBorder , textureTop);
        return -1;
    }
    SDL_GetWindowSize(carteSDL->window, &w, &h);

    textureTitre=ecrireSDLSolid(carteSDL, "police/pixel4.ttf", carteSDL->listeObjet[listeSelect[objetSelect]].nom, 80, colorFg);
    if(textureTitre==NULL){
        fprintf(stderr, "Erreur ecrireSDLSolid()\n");
        quitWindowStatsObject(texture, bouton1, bouton2, bouton3 , textureTexte , textureStats , textureTitre , textureCorner , textureBorder , textureTop);
        return -1;
    }
    SDL_QueryTexture(textureTitre, NULL, NULL, &rectTitre.w,&rectTitre.h);

    textureStats=writeSpecificObject(carteSDL, listeSelect[objetSelect]);
    SDL_QueryTexture(textureStats, NULL, NULL, &(rectStats.w),&(rectStats.h));

    rectIcone.h=64;
    rectIcone=setRect(64, 64, 10, 10+((rectTitre.h/2)-(rectIcone.h/2)));
    rectTitre.x=rectIcone.w+rectIcone.x+10+rectCorner.w;
    rectTitre.y=10;
    rectTexture.w=rectTitre.x+rectTitre.w+30;
    rectBouton1.x=10+rectCorner.w;
    rectBouton2.x=rectBouton1.x+rectBouton1.w+10;
    rectBouton3.x=rectBouton2.x+rectBouton2.w+10;
    if(rectBouton3.x+rectBouton3.w+5>rectTexture.w){
        rectTexture.w=rectBouton3.x+rectBouton3.w+10;
    }
    if(rectTexture.w<rectStats.w){
        rectTexture.w=rectStats.w;
    }
    textureTexte=createStatsText(carteSDL, listeSelect[objetSelect], rectTexture.w);
    SDL_QueryTexture(textureTexte, NULL, NULL, &(rectTextureTexte.w),&(rectTextureTexte.h));
    rectTexture.h=rectBouton1.h+rectTextureTexte.h+rectStats.h+rectTitre.h+50;
    rectTexture.h=rectTexture.h+(2*rectCorner.h);
    rectTexture.w=rectTexture.w+(2*rectCorner.w);
    rectTextureTexte.y=rectTitre.h+20;
    rectTextureTexte.x=rectCorner.w;

    rectIcone.x=((rectTexture.w-(rectIcone.w+rectTitre.w+10))/2)+rectCorner.w;
    rectTitre.x=rectIcone.w+rectIcone.x+10;
    rectStats=setRect(rectStats.w,rectStats.h, (rectTexture.w/2)-(rectStats.w/2), rectTextureTexte.h+rectTitre.h+30);
    rectBouton1.x=((rectTexture.w-(rectBouton1.w+rectBouton2.w+rectBouton3.w+(2*10)))/2)+rectCorner.w;
    rectBouton2.x=rectBouton1.x+rectBouton1.w+10;
    rectBouton3.x=rectBouton2.x+rectBouton2.w+10;
    rectBouton1.y=rectStats.h+rectTextureTexte.h+rectTitre.h+40;
    rectBouton2.y=rectStats.h+rectTextureTexte.h+rectTitre.h+40;
    rectBouton3.y=rectStats.h+rectTextureTexte.h+rectTitre.h+40;

    rectTexture.x=(w/2)-(rectTexture.w/2);
    rectTexture.y=(h/2)-(rectTexture.h/2);
    texture=SDL_CreateTexture(carteSDL->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, rectTexture.w, rectTexture.h);
    if(texture==NULL){
        fprintf(stderr, "Erreur SDL_CreateTexture : %s\n", SDL_GetError());
        quitWindowStatsObject(texture, bouton1, bouton2, bouton3 , textureTexte , textureStats , textureTitre , textureCorner , textureBorder , textureTop);
        return -1;
    }
    if(0!=SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND)){
        fprintf(stderr, "Erreur SDL_SetTextureBlendMode() : %s\n", SDL_GetError() );
        quitWindowStatsObject(texture, bouton1, bouton2, bouton3 , textureTexte , textureStats , textureTitre , textureCorner , textureBorder , textureTop);
        return -1;
    }
    SDL_SetRenderTarget(carteSDL->renderer, texture);
    SDL_SetRenderDrawColor(carteSDL->renderer, 170, 170, 170, 0);
    SDL_RenderClear(carteSDL->renderer);
    SDL_SetRenderDrawColor(carteSDL->renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(carteSDL->renderer, &rectTexture);
    rectCorner=setRect(6, 6, 0, 0);
    SDL_RenderCopy(carteSDL->renderer, textureCorner, NULL, &rectCorner);
    rectCorner.y=rectTexture.h-rectCorner.h;
    SDL_RenderCopy(carteSDL->renderer, textureCorner, NULL, &rectCorner);
    rectCorner.x=rectTexture.w-rectCorner.w;
    SDL_RenderCopy(carteSDL->renderer, textureCorner, NULL, &rectCorner);
    rectCorner.y=0;
    SDL_RenderCopy(carteSDL->renderer, textureCorner, NULL, &rectCorner);
    rectBorder=setRect(3, rectTexture.h-(2*rectCorner.h), 3 , rectCorner.h);
    SDL_RenderCopy(carteSDL->renderer, textureBorder, NULL, &rectBorder);
    rectBorder.x=rectTexture.w-rectCorner.w;
    SDL_RenderCopy(carteSDL->renderer, textureBorder, NULL, &rectBorder);
    rectTop=setRect(rectTexture.w-(2*rectCorner.w), 3, rectCorner.w, 3);
    SDL_RenderCopy(carteSDL->renderer, textureTop, NULL, &rectTop);
    rectTop.y=rectTexture.h-rectCorner.h;
    SDL_RenderCopy(carteSDL->renderer, textureTop, NULL, &rectTop);
    rectFond=setRect(rectTexture.w-(2*rectCorner.w), rectTexture.h-(2*rectCorner.h), rectCorner.w,rectCorner.h);
    SDL_SetRenderDrawColor(carteSDL->renderer, 170, 170, 170, 255);
    SDL_RenderFillRect(carteSDL->renderer, &rectFond);
    SDL_RenderCopy(carteSDL->renderer, textureTitre, NULL, &rectTitre);
    SDL_RenderCopy(carteSDL->renderer, carteSDL->listeObjet[listeSelect[objetSelect]].texture, NULL, &rectIcone);
    SDL_RenderCopy(carteSDL->renderer, bouton1, NULL, &rectBouton1);
    SDL_RenderCopy(carteSDL->renderer, bouton2, NULL, &rectBouton2);
    SDL_RenderCopy(carteSDL->renderer, bouton3, NULL, &rectBouton3);
    SDL_RenderCopy(carteSDL->renderer, textureTexte, NULL, &rectTextureTexte);
    SDL_RenderCopy(carteSDL->renderer, textureStats, NULL, &rectStats);
    SDL_SetRenderTarget(carteSDL->renderer, NULL);

    SDL_GetMouseState(&mousePos.x, &mousePos.y);
    calculerPositionAbsolueBouton(&rectTexture, &rectBouton1,&rectBouton2,&rectBouton3);

    while(continuer){
        if(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_KEYUP:
                    switch(event.key.keysym.sym){
                        case SDLK_i :
                            continuer=0;
                            break;
                    }
                    break;
                case SDL_MOUSEMOTION :
                    SDL_GetMouseState(&mousePos.x, &mousePos.y);
                    break;
                case SDL_MOUSEBUTTONDOWN :
                    switch(event.button.button){
                        case SDL_BUTTON_LEFT :
                            if(SDL_TRUE==SDL_PointInRect(&mousePos, &rectBouton1)){
                                continuer=0;
                                select=1;
                            }
                            else if(SDL_TRUE==SDL_PointInRect(&mousePos, &rectBouton2)){
                                continuer=0;
                                select=2;
                            }
                            else if(SDL_TRUE==SDL_PointInRect(&mousePos, &rectBouton3)){
                                continuer=0;
                                select=3;
                            }
                            break;
                    }
                    break;
                case SDL_QUIT :
                    continuer = 0;
                    break;
            }
        }
        else{
            SDL_Delay(50);
        }
        if(rafraichissement){
            SDL_RenderClear(carteSDL->renderer);
            SDL_RenderCopy(carteSDL->renderer, carteSDL->persoInventaire->textureFond,NULL, NULL);
            SDL_RenderCopy(carteSDL->renderer, carteSDL->persoInventaire->texture, NULL, &(carteSDL->persoInventaire->affichage));
            SDL_RenderCopy(carteSDL->renderer, texture, NULL, &rectTexture);
            SDL_RenderPresent(carteSDL->renderer);
            rafraichissement=0;
        }
    }
    quitWindowStatsObject(texture, bouton1, bouton2, bouton3 , textureTexte , textureStats , textureTitre , textureCorner , textureBorder , textureTop);
    return select;
}
void afficherInventaire(CarteSDL *carteSDL){
    int i=0;
    int *listeSelect;
    int continuer = 1 ,rafraichissement=1 , nombreSelect , select=0;
    Type typeSelect=Epe;
    SDL_Event event;
    SDL_Point mousePos;
    calculerInventaire(carteSDL  , Epe);
    majRectSelect(carteSDL);
    while(continuer){
        if(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_KEYUP:
                    switch(event.key.keysym.sym){
                        case SDLK_i :
                            continuer=0;
                            break;
                    }
                    break;
                case SDL_MOUSEMOTION :
                    SDL_GetMouseState(&mousePos.x, &mousePos.y);
                    break;
                case SDL_MOUSEBUTTONDOWN :
                    switch(event.button.button){
                        case SDL_BUTTON_LEFT :
                            if(SDL_TRUE==SDL_PointInRect(&mousePos, &(carteSDL->persoInventaire->rectArme))){
                                calculerInventaire(carteSDL, Epe);
                                typeSelect=Epe;
                                rafraichissement=1;
                            }
                            else if(SDL_TRUE==SDL_PointInRect(&mousePos, &(carteSDL->persoInventaire->rectArmure))){
                                calculerInventaire(carteSDL, Armure);
                                typeSelect=Armure;
                                rafraichissement=1;
                            }
                            else if(SDL_TRUE==SDL_PointInRect(&mousePos, &(carteSDL->persoInventaire->rectParchemin))){
                                calculerInventaire(carteSDL, Parchemin);
                                typeSelect=Parchemin;
                                rafraichissement=1;
                            }
                            else if(SDL_TRUE==SDL_PointInRect(&mousePos, &(carteSDL->persoInventaire->rectBaton))){
                                calculerInventaire(carteSDL, Baton);
                                typeSelect=Baton;
                                rafraichissement=1;
                            }
                            else if(SDL_TRUE==SDL_PointInRect(&mousePos, &(carteSDL->persoInventaire->rectPotion))){
                                calculerInventaire(carteSDL, Potion);
                                typeSelect=Potion;
                                rafraichissement=1;
                                printf("ICI %d %d\n" , carteSDL->persoInventaire->rectPotion.x , carteSDL->persoInventaire->rectPotion.y);
                            }
                            else{
                                nombreSelect=mouseOnObject(carteSDL, mousePos);
                                if(nombreSelect<40){
                                    switch(typeSelect){
                                        case Epe:
                                            listeSelect=carteSDL->perso->inventaireArme;
                                            break;
                                        case Armure:
                                            listeSelect=carteSDL->perso->inventaireArmure;
                                            break;
                                        case Parchemin:
                                            listeSelect=carteSDL->perso->inventaireParchemin;
                                            break;
                                        case Baton:
                                            listeSelect=carteSDL->perso->inventaireBaton;
                                            break;
                                        case Potion:
                                            listeSelect=carteSDL->perso->inventairePotion;
                                            break;
                                    }
                                    if(listeSelect[nombreSelect]!=0){
                                        printf("On a cliqué sur %s\n", carteSDL->listeObjet[listeSelect[nombreSelect]].nom);
                                        select=windowStatsObject(carteSDL, nombreSelect, listeSelect,"Use" , "Throw", "Close");
                                        if(select==-1){
                                            fprintf(stderr, "Erreur windowStatsObject()\n" );
                                        }
                                        else if(select==1){
                                            printf("On a cliqué sur Use\n");
                                        }
                                        else if(select==2){
                                            printf("On a cliqué sur Throw\n");
                                        }
                                        else if(select==1){
                                            printf("On a cliqué sur Close\n");
                                        }
                                        rafraichissement=1;
                                    }
                                }
                            }
                            printf("Bouton gauche appuyé : %d , %d \n" , mousePos.x , mousePos.y);
                            printf("ICI %d %d\n" , carteSDL->persoInventaire->rectPotion.x , carteSDL->persoInventaire->rectPotion.y);
                            break;
                    }
                    break;
                case SDL_QUIT :
                    continuer = 0;
                    break;
            }
        }
        else{
            SDL_Delay(50);
        }
        if(rafraichissement==1){//Permet de rafraichir l'écran seulement lorsque c'est necessaire
            rafraichissement=0;
            SDL_RenderClear(carteSDL->renderer);
            SDL_RenderCopy(carteSDL->renderer, carteSDL->persoInventaire->textureFond,NULL, NULL);
            SDL_RenderCopy(carteSDL->renderer, carteSDL->persoInventaire->texture, NULL, &(carteSDL->persoInventaire->affichage));
            SDL_RenderPresent(carteSDL->renderer);
        }
    }
    if(carteSDL->persoInventaire->textureFond!=NULL){
        SDL_DestroyTexture(carteSDL->persoInventaire->textureFond);
    }
    carteSDL->persoInventaire->affiche=0;
}

int takeObject(CarteSDL* carteSDL , Carte* carte, int objet  , int position){//Return the object on the floor or noting (-1)
    Type type;
    int i=0;
    type=carteSDL->listeObjet[objet].type;
    if(carteSDL->perso->masseObjet+carteSDL->listeObjet[objet].poids<=carteSDL->perso->poidsMax&&carteSDL->perso->nbObjets<50&&objet>1){
      if(type==Epe||type==Arc||type==Massue||type==Fleche){
          while(carteSDL->perso->inventaireArme[i]!=0){
              i++;
          }
          carteSDL->perso->inventaireArme[i]=objet;
      }
      if(type==Baton||type==BatonMagique){
          while(carteSDL->perso->inventaireBaton[i]!=0){
              i++;
          }
          carteSDL->perso->inventaireBaton[i]=objet;
      }
      if(type==Armure||type==Bouclier){
          while(carteSDL->perso->inventaireArmure[i]!=0){
              i++;
          }
          carteSDL->perso->inventaireArmure[i]=objet;
      }
      if(type==Potion){
          while(carteSDL->perso->inventairePotion[i]!=0){
              i++;
          }
          carteSDL->perso->inventairePotion[i]=objet;
      }
      if(type==Parchemin){
          while(carteSDL->perso->inventaireParchemin[i]!=0){
              i++;
          }
          carteSDL->perso->inventaireParchemin[i]=objet;
      }
      carte->terrain[position].objet=-1;
      carteSDL->perso->masseObjet=carteSDL->perso->masseObjet+carteSDL->listeObjet[objet].poids;
      carteSDL->perso->nbObjets++;
      return -1;
    }
    else{
      return objet;
    }
}
int initialiserPersoInventaire(CarteSDL* carteSDL){
        carteSDL->persoInventaire=malloc(sizeof(Inventaire));
        if(carteSDL->persoInventaire==NULL){
            fprintf(stderr, "Erreur allocation mémoire\n");
            return -1;
        }
        carteSDL->persoInventaire->texture=SDL_CreateTexture(carteSDL->renderer , SDL_PIXELFORMAT_RGBA8888 , SDL_TEXTUREACCESS_TARGET , 750 , 481);
        if(carteSDL->persoInventaire->texture==NULL){
            fprintf(stderr, "Erreur création texture de l'inventaire\n");
            return -1;
        }
        if(0!=SDL_SetTextureBlendMode(carteSDL->persoInventaire->texture ,SDL_BLENDMODE_BLEND)){
            fprintf(stderr , "Error SDL_SetTextureBlendMode : %s" , SDL_GetError());
            return -1;
        }
        if(0!=loadIMG(carteSDL, "image/inv.png", &(carteSDL->persoInventaire->textureCadre))){
            fprintf(stderr, "Erreur création texture du cadre de l'inventaire\n");
            return -1;
        }
        if(0!=loadIMG(carteSDL, "image/selectArme.png", &(carteSDL->persoInventaire->selectArme))){
            fprintf(stderr, "Erreur création texture du cadre de l'inventaire\n");
            return -1;
        }
        carteSDL->persoInventaire->rectArme=setRect(150, 100, 0, 0);
        if(0!=loadIMG(carteSDL, "image/selectArmure.png", &(carteSDL->persoInventaire->selectArmure))){
            fprintf(stderr, "Erreur création texture du cadre de l'inventaire\n");
            return -1;
        }
        carteSDL->persoInventaire->rectArmure=setRect(150, 100, 150, 0);
        if(0!=loadIMG(carteSDL, "image/selectBaton.png", &(carteSDL->persoInventaire->selectBaton))){
            fprintf(stderr, "Erreur création texture du cadre de l'inventaire\n");
            return -1;
        }
        carteSDL->persoInventaire->rectBaton=setRect(150, 100, 450, 0);
        if(0!=loadIMG(carteSDL, "image/selectParchemin.png", &(carteSDL->persoInventaire->selectParchemin))){
            fprintf(stderr, "Erreur création texture du cadre de l'inventaire\n");
            return -1;
        }
        carteSDL->persoInventaire->rectParchemin=setRect(150, 100, 300, 0);
        if(0!=loadIMG(carteSDL, "image/selectPotion.png", &(carteSDL->persoInventaire->selectPotion))){
            fprintf(stderr, "Erreur création texture du cadre de l'inventaire\n");
            return -1;
        }
        if(loadIMG(carteSDL, "image/cadreDroit.png", &(carteSDL->persoInventaire->textureCadreDroit))!=0){
            fprintf(stderr, "Erreur loadIMG()\n" );
            return -1;
        }
        if(loadIMG(carteSDL, "image/cadreGauche.png", &(carteSDL->persoInventaire->textureCadreGauche))!=0){
            fprintf(stderr, "Erreur loadIMG()\n" );
            return -1;
        }
        carteSDL->persoInventaire->rectPotion=setRect(150, 100, 600, 0);
        carteSDL->persoInventaire->affiche=0;
        carteSDL->persoInventaire->select=0;
    return 0;
}
int initialiserPersonnage(CarteSDL* carteSDL){
    int i=0;
    carteSDL->perso=malloc(sizeof(Personnage));
    carteSDL->perso->inventaireArme=malloc(sizeof(int)*50);
    if(carteSDL->perso->inventaireArme==NULL){
        return -1;
    }
    for(i=0;i<50;i++){
        carteSDL->perso->inventaireArme[i]=0;
    }
    carteSDL->perso->inventaireBaton=malloc(sizeof(int)*50);
    if(carteSDL->perso->inventaireBaton==NULL){
        return -1;
    }
    for(i=0;i<50;i++){
        carteSDL->perso->inventaireBaton[i]=0;
    }
    carteSDL->perso->inventaireArmure=malloc(sizeof(int)*50);
    if(carteSDL->perso->inventaireArmure==NULL){
        return -1;
    }
    for(i=0;i<50;i++){
        carteSDL->perso->inventaireArmure[i]=0;
    }
    carteSDL->perso->inventairePotion=malloc(sizeof(int)*50);
    if(carteSDL->perso->inventairePotion==NULL){
        return -1;
    }
    for(i=0;i<50;i++){
        carteSDL->perso->inventairePotion[i]=0;
    }
    carteSDL->perso->inventaireParchemin=malloc(sizeof(int)*50);
    if(carteSDL->perso->inventaireParchemin==NULL){
        return -1;
    }
    for(i=0;i<50;i++){
        carteSDL->perso->inventaireParchemin[i]=0;
    }
    carteSDL->perso->masseObjet=0;
    carteSDL->perso->vie=0;
    carteSDL->perso->force=0;
    carteSDL->perso->habilete=0;
    carteSDL->perso->precision=0;
    carteSDL->perso->magie=0;
    carteSDL->perso->agilite=0;
    carteSDL->perso->nbObjets=0;
    carteSDL->perso->poidsMax=50;
    carteSDL->perso->texture=carteSDL->personnage;
    return 0;
}
