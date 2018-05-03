#include <stdio.h>
#include <stdlib.h>
#include "../include/structure.h"

void quitterEnregistrerCarte(FILE *file){
    if(file!=NULL){
        fclose(file);
    }
}
void quitterInitGame(FILE *file){
    if(file!=NULL){
        fclose(file);
    }
}
int majGame(Carte* carte , char* pathGame){
    FILE *file=NULL;
    file=fopen(pathGame , "w+");
    if(file==NULL){
        fprintf(stderr , "Erreur open file %s" , pathGame);
        quitterInitGame(file);
        return -1;
    }
    fprintf(file , "nbFloor[%d] actualFloor[[%s]" , carte->nbFloor , carte->path);
    fprintf(file , "[%d]]" , carte->floor);
    quitterInitGame(file);
    return 0;
}
int initGame(Carte *carte){
    FILE *file=NULL;
    int nbFloor=0 , i=0;
    char pathGame[50] , pathMap[50];
    sprintf(carte->path , "carte/carte%d/carte1.txt" , carte->numGame);
    carte->nbFloor=1;
    carte->floor=1;
    sprintf(pathGame , "carte/carte%d/game.gm" , carte->numGame);
    file=fopen(pathGame , "r");
    if(file==NULL){
        fprintf(stderr , "Erreur open file %s" , pathGame);
        quitterInitGame(file);
        return -1;
    }
    fscanf(file , "nbFloor[%d]" , &nbFloor);
    for(i=1; i<=nbFloor; i++){
        sprintf(pathMap , "carte/carte%d/carte%d.txt" , carte->numGame , i);
        remove(pathMap);
    }
    quitterInitGame(file);
    majGame(carte , pathGame);
    return 0;
}
void quitterLoadGame(Carte *carte , FILE *file){
    if(file!=NULL){
        fclose(file);
    }
    if(carte!=NULL){
        free(carte);
    }
}
Carte* loadGame(int choice){
    FILE *file=NULL;
    Carte *carte=NULL;
    char path[50];
    carte=malloc(sizeof(Carte));
    if(carte==NULL){
        fprintf(stderr , "Erreur allocation mémoire\n");
        quitterLoadGame(carte , file);
        return NULL;
    }
    carte->numGame=choice;
    sprintf(path , "carte/carte%d/game.gm" , carte->numGame);
    file=fopen(path , "r");
    if(file==NULL){
        fprintf(stderr , "Erreur load file %s" , path);
        quitterLoadGame(carte , file);
        return NULL;
    }
    fscanf(file , "nbFloor[%d] actualFloor[[%[^\]]s" , &(carte->nbFloor) ,&(carte->path));
    fscanf(file , "][%d]]" , &(carte->floor));
    fprintf(stderr , "%s\n" , carte->path);
    lireCarte(carte);
    quitterLoadGame(NULL , file);
    fprintf(stderr , "%d" , carte->terrain[carte->posPerso].voile);
    fprintf(stderr , "%d\n" , carte);
    return carte;
}

int enregistrerCarte(Carte *carte){
    FILE *file=NULL;
    int i=0;
    file=fopen(carte->path , "w+");
    if(file==NULL){
        fprintf(stderr , "Erreur ouverture fichier\n");
        quitterEnregistrerCarte(file);
        return -1;
    }
    fprintf(file , "vide[0] l[%d] h[%d] nbSalle[%d] compteur[%d] nbBlackListRoom[%d] posPerso[%d]\n" , carte->largeur , carte->hauteur , carte->nbSalle , carte->compteur , carte->nbBlackListRoom , carte->posPerso);
    fprintf(file , "position");
    for(i=0; i<carte->compteur; i++){
        fprintf(file , "[%d]" , carte->position[i]);
    }
    fprintf(file , "\nblackListRoom");
    for(i=0; i<carte->nbBlackListRoom; i++){
        fprintf(file , "[%d]" , carte->blackListRoom[i]);
    }
    fprintf(file , "\nterrain");
    for(i=0; i<carte->largeur*carte->hauteur; i++){
        fprintf(file , "[[%d][%d][%d][%d][%d]]" , carte->terrain[i].type , carte->terrain[i].numeroSalle  , carte->terrain[i].object , carte->terrain[i].numeroTile , carte->terrain[i].voile);
    }
    quitterEnregistrerCarte(file);
    return 0;
}

void quitterLireCarte(Carte *carte , FILE *file){
    if(carte!=NULL){
        if(carte->terrain!=NULL){
            free(carte->terrain);
        }
        if(carte->position!=NULL){
            free(carte->position);
        }
        if(carte->blackListRoom!=NULL){
            free(carte->blackListRoom);
        }
    }
    if(file!=NULL){
        fclose(file);
    }
}

int lireCarte(Carte *carte){
    FILE *file=NULL;
    int i=0 , vide=0;
    file=fopen( carte->path ,"r");
    if(file==NULL){
        fprintf(stderr , "Erreur ouverture fichierICI\n");
        quitterLireCarte(carte , file);
        return NULL;
    }
    if(EOF==fscanf(file , "vide[%d]" , &vide )){
        carte=generateurCarteAlea(100 , 100);
    }
    else if(vide==1){
        carte=generateurCarteAlea(100 , 100);
    }
    else{
        fscanf(file , " l[%d] h[%d] nbSalle[%d] compteur[%d] nbBlackListRoom[%d] posPerso[%d]\n" , &carte->largeur , &carte->hauteur , &carte->nbSalle , &carte->compteur , &carte->nbBlackListRoom , &carte->posPerso);
        carte->terrain = malloc(sizeof(Terrain)*(carte->largeur*carte->hauteur));
        if(carte->terrain==NULL){
            fprintf(stderr , "Erreur allouage de mémoire\n");
            quitterLireCarte(carte , file);
            return -1;
        }
        carte->position=NULL;
        carte->position=malloc(sizeof(int)*carte->largeur*carte->hauteur);
        if(carte->position==NULL){
            fprintf(stderr , "Erreur allouage de mémoire\n");
            quitterLireCarte(carte , file);
            return -1;
        }
        carte->blackListRoom=NULL;
        carte->blackListRoom=malloc((sizeof(int)*(carte->largeur/5)));
        if(carte->blackListRoom==NULL){
            fprintf(stderr , "Erreur allouage de mémoire\n");
            quitterLireCarte(carte , file);
            return -1;
        }
        fscanf(file , "position");
        for(i=0; i<carte->compteur; i++){
            fscanf(file , "[%d]" , &carte->position[i]);
        }
        fscanf(file , "\nblackListRoom");
        for(i=0; i<carte->nbBlackListRoom; i++){
            fscanf(file , "[%d]" , &carte->blackListRoom[i]);
        }
        fscanf(file , "\nterrain");
        for(i=0; i<carte->largeur*carte->hauteur; i++){
            fscanf(file , "[[%d][%d][%d][%d][%d]]" , &carte->terrain[i].type , &carte->terrain[i].numeroSalle , &carte->terrain[i].object , &carte->terrain[i].numeroTile , &carte->terrain[i].voile);
        }
    }
    sprintf(carte->path ,  "carte/carte%d/carte1.txt" , carte->numGame);
    quitterLireCarte(NULL , file);
    return 0;
}
