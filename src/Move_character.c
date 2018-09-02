#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "../include/structure.h"
#include "../include/Afficher_carte.h"
#include "../include/enregistrer_carte.h"
#include "../include/Generateur_carte_alea.h"
#include "../include/Generateur_object.h"
#include "../include/inventaire.h"
#include "../include/manage_SDL.h"
#define UP -1
#define DOWN +1

Carte* loadFloor(Carte* carte , CarteSDL* carteSDL, int change ){
    int  numGame=0;
    char pathGame[50];
    enregistrerCarte(carte);
    carte->floor=carte->floor+(1*change);
    numGame=carte->numGame;
    sprintf(pathGame , "carte/carte%d/game.gm" , carte->numGame);
    sprintf(carte->path , "carte/carte%d/carte%d.txt" , carte->numGame , carte->floor);
    majGame(carte, pathGame);
    quitterGenerateur(carte);
    carte=loadGame(numGame , carteSDL);
    return carte;
}
Carte* floorDown(Carte* carte , CarteSDL *carteSDL){
    int floor=0 , nbFloor=0 , numGame=0;
    char pathGame[50];
    if(carte->nbFloor>carte->floor){
        carte=loadFloor(carte ,carteSDL, DOWN );
        return carte;
    }
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
    generateObject(carte , carteSDL);
    majGame(carte , pathGame);
    return carte;
}
Carte* floorUp(Carte* carte , CarteSDL *carteSDL){
    carte= loadFloor(carte  , carteSDL , UP);
    return carte;
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
int eventPerso(CarteSDL* carteSDL , Carte *carte , int event){
    int out=1;
    if(carte->terrain[carte->posPerso].type==MUR||carte->terrain[carte->posPerso].type==MUR_SALLE||carte->terrain[carte->posPerso].type==MUR_CHEMIN){
        out=0;
        annulerMouvement(carte , event);
    }
    if(carte->terrain[carte->posPerso].tresor!=-1&&carte->terrain[carte->posPerso].tresor!=-2){
        out=1;
        carte->terrain[carte->posPerso].objet=carte->terrain[carte->posPerso].tresor;
        carte->terrain[carte->posPerso].tresor=-2;
    }
    else if(carte->terrain[carte->posPerso].tresor==-2&&carte->terrain[carte->posPerso].objet!=-1){
        carte->terrain[carte->posPerso].objet=takeObject(carteSDL , carte , carte->terrain[carte->posPerso].objet , carte->posPerso);
        printf("Ici on a pris les objets\n" );
        out=1;
    }
    setShowTile(carte , SHOW);
    return out;
}
int moveCharacter(Carte *carte,CarteSDL* carteSDL){
    SDL_Event event;
    int continuer=1 , zoom=75, rafraichissement=1 , position=99999 , takeScreen=0;

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
                                rafraichissement=eventPerso(carteSDL , carte , HAUT);
                            }
                            break;
                        case SDLK_DOWN :
                            if(!event.key.repeat){
                                setShowTile(carte , VISITED);
                                carte->posPerso+=carte->largeur;
                                rafraichissement=eventPerso(carteSDL , carte , BAS);
                            }
                            break;
                        case SDLK_RIGHT :
                            if(!event.key.repeat){
                                setShowTile(carte , VISITED);
                                carte->posPerso++;
                                rafraichissement=eventPerso(carteSDL , carte , DROITE);
                            }
                            break;
                        case SDLK_LEFT :
                            if(!event.key.repeat){
                                setShowTile(carte , VISITED);
                                carte->posPerso--;
                                rafraichissement=eventPerso(carteSDL , carte , GAUCHE);
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
                        case SDLK_i :
                            takeScreen=1;
                            rafraichissement=1;
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
                                if(carte->terrain[carte->posPerso].objet==0){
                                    carte=floorDown(carte , carteSDL);
                                    setShowTile(carte , VISITED);
                                    rafraichissement=1;
                                    position=99999;
                                }
                                else if(carte->terrain[carte->posPerso].objet==1 && carte->floor>1){
                                    carte=floorUp(carte , carteSDL);
                                    rafraichissement=1;
                                    position=99999;
                                }
                                fprintf(stderr , "\n%d\n" , carte->nbFloor);
                            break;
                    }
                    break;
                case SDL_KEYUP :
                    switch(event.key.keysym.sym){
                        case SDLK_i :
                            takeScreen=0;
                            afficherInventaire(carteSDL);
                            rafraichissement=1;
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
                if(takeScreen){
                    carteSDL->persoInventaire->textureFond=copyRenderToTexture(carteSDL);
                }
                SDL_RenderPresent(carteSDL->renderer);
            }
        }
        else{
            SDL_Delay(50);
        }
    }
    return 0;
}
