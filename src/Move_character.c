#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "../include/structure.h"
#include "../include/Afficher_carte.h"
#include "../include/enregistrer_carte.h"
#include "../include/Generateur_carte_alea.h"
void floorDown(Carte *carte){
    int floor=0 , nbFloor=0 , numGame=0;
    char pathGame[50];
    enregistrerCarte(carte);
    floor=carte->floor+1;
    nbFloor=carte->nbFloor+1;
    numGame=carte->numGame;
    quitterGenerateur(carte);
    carte=generateurCarteAlea(100 , 100);
    carte->nbFloor=nbFloor;
    carte->floor=floor;
    carte->numGame=numGame;
    sprintf(carte->path , "carte/carte%d/carte%d.txt" , carte->numGame , carte->floor);
    sprintf(pathGame , "carte/carte%d/game.gm" , carte->numGame);
    majGame(carte , pathGame);
}
void annulerMouvement(Carte* carte , int event){
    switch(event){
        case HAUT :
            carte->posPerso+=carte->largeur;
            break;
        case BAS :
            carte->posPerso-=carte->largeur;
            break;
        case GAUCHE :
            carte->posPerso++;
            break;
        case DROITE :
            carte->posPerso--;
            break;
    }
}
void setShowTile(Carte *carte , int set){
    carte->terrain[carte->posPerso].voile=set;
    carte->terrain[carte->posPerso-1].voile=set;
    carte->terrain[carte->posPerso+1].voile=set;
    carte->terrain[carte->posPerso-carte->largeur].voile=set;
    carte->terrain[carte->posPerso+carte->largeur].voile=set;
    carte->terrain[carte->posPerso+carte->largeur+1].voile=set;
    carte->terrain[carte->posPerso+carte->largeur-1].voile=set;
    carte->terrain[carte->posPerso-carte->largeur+1].voile=set;
    carte->terrain[carte->posPerso-carte->largeur-1].voile=set;
    if(carte->terrain[carte->posPerso+1].type<MUR){
        carte->terrain[carte->posPerso+2].voile=set;
    }
    if(carte->terrain[carte->posPerso-1].type<MUR){
        carte->terrain[carte->posPerso-2].voile=set;
    }
    if(carte->terrain[carte->posPerso+carte->largeur].type<MUR){
    carte->terrain[carte->posPerso+2*carte->largeur].voile=set;
    }
    if(carte->terrain[carte->posPerso-carte->largeur].type<MUR){
    carte->terrain[carte->posPerso-2*carte->largeur].voile=set;
    }
    if(carte->terrain[carte->posPerso-carte->largeur-1].type<MUR&&carte->terrain[carte->posPerso-carte->largeur-1].voile<MUR){
        carte->terrain[carte->posPerso-2*carte->largeur-1].voile=set;
    }
    if(carte->terrain[carte->posPerso-carte->largeur+1].type<MUR&&carte->terrain[carte->posPerso-carte->largeur+1].voile<MUR){
        carte->terrain[carte->posPerso-2*carte->largeur+1].voile=set;
    }
    if(carte->terrain[carte->posPerso+carte->largeur-1].type<MUR&&carte->terrain[carte->posPerso+carte->largeur-1].voile<MUR){
        carte->terrain[carte->posPerso+2*carte->largeur-1].voile=set;
    }
    if(carte->terrain[carte->posPerso+carte->largeur+1].type<MUR&&carte->terrain[carte->posPerso+carte->largeur+1].voile<MUR){
        carte->terrain[carte->posPerso+2*carte->largeur+1].voile=set;
    }
    if(carte->terrain[carte->posPerso-1+carte->largeur].type<MUR&&carte->terrain[carte->posPerso-1+carte->largeur].voile<MUR){
        carte->terrain[carte->posPerso-2+carte->largeur].voile=set;
    }
    if(carte->terrain[carte->posPerso-1-carte->largeur].type<MUR&&carte->terrain[carte->posPerso-1-carte->largeur].voile<MUR){
        carte->terrain[carte->posPerso-2-carte->largeur].voile=set;
    }
    if(carte->terrain[carte->posPerso+1+carte->largeur].type<MUR&&carte->terrain[carte->posPerso+1+carte->largeur].voile<MUR){
        carte->terrain[carte->posPerso+2+carte->largeur].voile=set;
    }
    if(carte->terrain[carte->posPerso+1-carte->largeur].type<MUR&&carte->terrain[carte->posPerso+1-carte->largeur].voile<MUR){
        carte->terrain[carte->posPerso+2-carte->largeur].voile=set;
    }
}
int eventPerso(Carte *carte , int event){
    int out=1;
    if(carte->terrain[carte->posPerso].type==MUR||carte->terrain[carte->posPerso].type==MUR_SALLE||carte->terrain[carte->posPerso].type==MUR_CHEMIN){
        out=0;
        annulerMouvement(carte , event);
    }
    if(carte->terrain[carte->posPerso].object==COFFRE){
        out=1;
        carte->terrain[carte->posPerso].object=TREASOR_OPEN;
    }
    setShowTile(carte , SHOW);
    return out;
}
int moveCharacter(Carte *carte,CarteSDL* carteSDL){
    SDL_Event event;
    int continuer=1 , zoom=75, rafraichissement=0 , position=99999;

    setShowTile(carte , SHOW);
    position=afficherCarteZoom(carte , carteSDL , position , zoom , event.key.keysym.sym);
    while(continuer){
        if(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_KEYDOWN :
                    switch(event.key.keysym.sym){
                        case SDLK_UP :
                            if(!event.key.repeat){
                                setShowTile(carte , VISITED);
                                carte->posPerso-=carte->largeur;
                                rafraichissement=eventPerso(carte , HAUT);
                            }
                            break;
                        case SDLK_DOWN :
                            if(!event.key.repeat){
                                setShowTile(carte , VISITED);
                                carte->posPerso+=carte->largeur;
                                rafraichissement=eventPerso(carte , BAS);
                            }
                            break;
                        case SDLK_RIGHT :
                            if(!event.key.repeat){
                                setShowTile(carte , VISITED);
                                carte->posPerso++;
                                rafraichissement=eventPerso(carte , DROITE);
                            }
                            break;
                        case SDLK_LEFT :
                            if(!event.key.repeat){
                                setShowTile(carte , VISITED);
                                carte->posPerso--;
                                rafraichissement=eventPerso(carte , GAUCHE);
                            }
                            break;
                        case SDLK_s :
                            if(0!=enregistrerCarte(carte)){
                                return -1;
                            }
                            break;
                        case SDLK_KP_PLUS :
                            zoom++;
                            rafraichissement=1;
                            position=99999;
                            break;
                        case SDLK_KP_MINUS :
                            zoom--;
                            rafraichissement=1;
                            position=99999;
                            break;
                        case SDLK_q :
                            continuer=0;
                            break;
                        case SDLK_F11 :
                            if(!event.key.repeat){
                                if(SDL_GetWindowFlags(carteSDL->window)&SDL_WINDOW_FULLSCREEN_DESKTOP){
                                    if(0!=SDL_SetWindowFullscreen(carteSDL->window , 0)){
                                        fprintf(stderr , "Erreur SDL_Fulscreen : %s" , SDL_GetError());
                                    }

                                }
                                else{
                                    SDL_SetWindowFullscreen(carteSDL->window , SDL_WINDOW_FULLSCREEN_DESKTOP);
                                }
                                rafraichissement=1;
                                position=99999;
                            }
                            break;
                        case SDLK_e :
                                if(carte->terrain[carte->posPerso].object==ESCALIER_BAS){
                                    floorDown(carte);
                                    rafraichissement=1;
                                    printf("Down");
                                    position=99999;
                                }
                                fprintf(stderr , "%d\n" , carte->terrain[carte->posPerso].type);
                            break;
                    }
                    break;
                case SDL_QUIT :
                    continuer = 0;
                    break;
            }
            if(rafraichissement){//Permet de rafraichir l'écran seulement lorsque c'est necessaire
                rafraichissement=0;
                position=afficherCarteZoom(carte , carteSDL , position , zoom , event.key.keysym.sym );
            }
        }else{
            SDL_Delay(50);
        }
    }
    return 0;
}
