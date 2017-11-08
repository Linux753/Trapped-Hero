#include <stdio.h>
#include <stdlib.h>
#include "../include/structure.h"

void quitterEnregistrerCarte(FILE *file){
    if(file!=NULL){
        fclose(file);
    }
}

int enregistrerCarte(Carte *carte){
    FILE *file=NULL;
    int i=0;
    file=fopen("carte/carte1.txt" , "w+");
    if(file==NULL){
        fprintf(stderr , "Erreur ouverture fichier\n");
        quitterEnregistrerCarte(file);
        return -1;
    }
    fprintf(file , "l[%d] h[%d] nbSalle[%d] compteur[%d] nbBlackListRoom[%d] posPerso[%d]\n" , carte->largeur , carte->hauteur , carte->nbSalle , carte->compteur , carte->nbBlackListRoom , carte->posPerso);
    fprintf(file , "position");
    for(i=0; i<carte->compteur; i++){
        fprintf(file , "[%d]" , carte->position[i]);
    }
    fprintf(file , "\nblackListRoom");
    for(i=0; i<carte->nbBlackListRoom; i++){
        fprintf(file , "[%d]" , carte->blackListRoom[i]);
    }
//    if(carte->nbBlackListRoom==0){
//        fprintf(file , "[NULL]");
//    }
    fprintf(file , "\nterrain");
    for(i=0; i<carte->largeur*carte->hauteur; i++){
        fprintf(file , "[type[%d] numeroSalle[%d] orientation[%d] object[%d] numeroTile[%d]]" , carte->terrain[i].type , carte->terrain[i].numeroSalle , carte->terrain[i].orientation , carte->terrain[i].object , carte->terrain[i].numeroTile);
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
        if(carte!=NULL){
            free(carte);
        }
    }
    if(file!=NULL){
        fclose(file);
    }
}

Carte* lireCarte(){
    Carte *carte=NULL;
    FILE *file;
    int i=0;
    carte=malloc(sizeof(Carte));
    if(carte==NULL){
        fprintf(stderr , "Erreur ouverture fichier\n");
        quitterLireCarte(carte , file);
        return NULL;
    }
    file=fopen("carte/carte1.txt" ,"r");
    if(file==NULL){
        fprintf(stderr , "Erreur ouverture fichier\n");
        quitterLireCarte(carte , file);
        return NULL;
    }
    fscanf(file , "l[%d] h[%d] nbSalle[%d] compteur[%d] nbBlackListRoom[%d] posPerso[%d]\n" , &carte->largeur , &carte->hauteur , &carte->nbSalle , &carte->compteur , &carte->nbBlackListRoom , &carte->posPerso);
    carte->terrain = malloc(sizeof(Terrain)*(carte->largeur*carte->hauteur));
    if(carte->terrain==NULL){
        fprintf(stderr , "Erreur allouage de mémoire\n");
        quitterLireCarte(carte , file);
        return NULL;
    }
    carte->position=NULL;
    carte->position=malloc(sizeof(int)*carte->largeur*carte->hauteur);
    if(carte->position==NULL){
        fprintf(stderr , "Erreur allouage de mémoire\n");
        quitterLireCarte(carte , file);
        return NULL;
    }
    carte->blackListRoom=NULL;
    carte->blackListRoom=malloc((sizeof(int)*(carte->largeur/5)));
    if(carte->blackListRoom==NULL){
        fprintf(stderr , "Erreur allouage de mémoire\n");
        quitterLireCarte(carte , file);
        return NULL;
    }
//    fseek(file , 8 , SEEK_CUR);
    fscanf(file , "position");
    for(i=0; i<carte->compteur; i++){
        fscanf(file , "[%d]" , &carte->position[i]);
    }
//    fseek(file , 14 , SEEK_CUR);
    fscanf(file , "\nblackListRoom");
    for(i=0; i<carte->nbBlackListRoom; i++){
        fscanf(file , "[%d]" , &carte->blackListRoom[i]);
    }
//    fseek(file , 8 , SEEK_CUR);
    fscanf(file , "\nterrain");
    for(i=0; i<carte->largeur*carte->hauteur; i++){
        fscanf(file , "[type[%d] numeroSalle[%d] orientation[%d] object[%d] numeroTile[%d]]" , &carte->terrain[i].type , &carte->terrain[i].numeroSalle , &carte->terrain[i].orientation , &carte->terrain[i].object , &carte->terrain[i].numeroTile);
    }
    quitterLireCarte(NULL , file);
    return carte;
}
