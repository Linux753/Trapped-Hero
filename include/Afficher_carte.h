#ifndef AFFICHER_CARTE_H_INCLUDED
#define AFFICHER_CARTE_H_INCLUDED

int loadIMG(CarteSDL *carteSDL ,char *file , SDL_Texture **texture);
int InitialiserSDL(CarteSDL *carteSDL);
void quitterSDL(CarteSDL *carteSDL);
int initialiserTile(CarteSDL *carteSDL , int w , int h);
int loadTileset(CarteSDL *carteSDL);
int afficherCarte(Carte *carte , CarteSDL *carteSDL);
CarteSDL *initialiserCarteSDL();
int reajusterCadrage(Carte *carte ,int position ,
    int windowH,int  windowW , int tileNbW ,int tileNbH );
int afficherCarteZoom(Carte *carte , CarteSDL *carteSDL ,
    int position , int taille  , SDL_Keycode event);
int initialiserMonster(CarteSDL *carteSDL , int w ,int h);
int chargerTileOrSprite(CarteSDL *carteSDL , SDL_Texture *image ,
    SDL_Texture **sprite , int x , int y , int w , int h);
#endif // AFFICHER_CARTE_H_INCLUDED
