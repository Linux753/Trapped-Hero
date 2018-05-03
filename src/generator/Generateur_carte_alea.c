#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../../include/Generateur_chemin.h"
#include "../../include/Generateur_carte_alea.h"
#include "../../include/Generateur_salle_alea.h"
#include "../../include/structure.h"
#include "../../include/Generateur_object.h"
#include "../../include/manage_SDL.h"
#include <SDL2/SDL.h>

void initialiserCarte(Carte *carte){
    //printf("initialiserCarte");
    int i=0 , nbAlea=0;
    int compteur = 0;
    for(i=0;i<=((carte->largeur*carte->hauteur)-1);i++){
        if(compteur==(carte->largeur-1)){
            carte->terrain[i].type=MUR;
            compteur++;
        }
        else if(compteur==carte->largeur){
            carte->terrain[i].type=MUR;
            compteur=1;
        }
        else if(i>=0 && i<=(carte->largeur-1)){
            carte->terrain[i].type=MUR;
            compteur++;
        }
        else if(i>=(((carte->largeur*carte->hauteur)-1)-carte->largeur)&&i<=((carte->largeur*carte->hauteur)-1)){
            carte->terrain[i].type=MUR;
            compteur++;
        }
        else{
            compteur++;
            carte->terrain[i].type=VIDE;
        }
        carte->terrain[i].numeroSalle=0;

        carte->terrain[i].object=0;
        nbAlea=rand_a_b(1 , 101);
        if(nbAlea==98){
            carte->terrain[i].numeroTile=1;
        }
        else if(nbAlea==94){
            carte->terrain[i].numeroTile=2;
        }
        else{
            carte->terrain[i].numeroTile=0;
        }
        carte->terrain[i].voile=HIDDEN;
    }
    carte->compteur=0;
    carte->nbBlackListRoom=0;
}
int verifierBlackListRoom(Carte *carte , int position){
    int i=0;
    for(i=0;i<carte->nbBlackListRoom;i++){
        if(carte->terrain[position].numeroSalle==carte->blackListRoom[i]){
            return 1;
        }
    }
    return 0;
}
void recenserRoom(Carte* carte){
    int i=0 , sauvegarde=0 , numero=0 , sauvegardeNumero=0 , doubleSauvegarde=0;
    for(i=0;i<carte->largeur*carte->hauteur;i++){
        if(carte->terrain[i].type==SOL_SALLE||carte->terrain[i].type==CHEMIN){
            if(carte->terrain[i].numeroSalle!=0){
                if(verifierBlackListRoom(carte , i)==0){
                    carte->position[carte->compteur]=i;
                    carte->compteur++;
                }
            }
        }
    }
    numero=rand_a_b(0 , carte->compteur);
    sauvegarde=carte->position[numero];
    sauvegardeNumero=numero;
    for(i=0;i<carte->compteur*2;i++){
        numero=rand_a_b(0 , carte->compteur);
        doubleSauvegarde=carte->position[numero];
        carte->position[numero]=sauvegarde;
        sauvegarde=doubleSauvegarde;
    }
    carte->position[sauvegardeNumero]=sauvegarde;
    carte->compteur--;
}
Carte* generateurCarteAlea(int largeur , int hauteur ){
        //printf("generateurcarteAlea");
        Carte *carte=NULL;
        carte=malloc(sizeof(Carte));
        carte->terrain = malloc(sizeof(Terrain)*(largeur*hauteur));
        if(carte->terrain==NULL){
            printf("Erreur d'allouage de mémoire");
            exit(1);
        }
        carte->position=NULL;
        carte->position=malloc(sizeof(int)*largeur*hauteur);
        if(carte->position==NULL){
            printf("Erreur d'allouage de mémoire 2");
            exit(1);
        }
        carte->blackListRoom=NULL;
        carte->blackListRoom=malloc((sizeof(int)*(largeur/5)));
        if(carte->blackListRoom==NULL){
            printf("Erreur d'allouage de mémoire 1");
            exit(1);
        }
        carte->largeur=largeur;
        carte->hauteur = hauteur;
        initialiserCarte(carte);
        genererSalleAlea(carte);
        fermerSalle(carte);
        dessinerPorte(carte);
        recenserRoom(carte);
        generateObject(carte);
        return carte;
}
void quitterGenerateur(Carte *carte){
    //printf("quitterGenerateur");
    free(carte->terrain);
    carte->terrain=NULL;
    free(carte->position);
    carte->position=NULL;
    free(carte->blackListRoom);
    carte->blackListRoom=NULL;
    free(carte);
}
void quitterJeu(Carte *carte , CarteSDL *carteSDL){
    if(carte!=NULL){
        quitterGenerateur(carte);
    }
    quitterSDL(carteSDL);
}
